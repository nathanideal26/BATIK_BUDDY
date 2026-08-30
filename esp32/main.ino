#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;

// Status Aliran Robot
int currentTargetStation = 1;
bool isMoving = false;

// Pin Motor Driver (Contoh L298N / TB6612 / L9110S)
const int ENA = 14;
const int IN1 = 27;
const int IN2 = 26;
const int IN3 = 25;
const int IN4 = 33;
const int ENB = 32;

// Pin Sensor Garisan / Sensor Stesen (Contoh IR / Tag RFID / Sensor Warna)
const int SENSOR_LEFT = 19;
const int SENSOR_RIGHT = 18;
const int SENSOR_STATION_STOP = 21; // Sensor yang mengesan titik henti stesen

void stopRobot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  isMoving = false;
  Serial.println("Robot Berhenti.");
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 180); // Kelajuan motor (0 - 255)
  analogWrite(ENB, 180);
  isMoving = true;
}

void lineFollowLogic() {
  if (!isMoving) return;

  int leftVal = digitalRead(SENSOR_LEFT);
  int rightVal = digitalRead(SENSOR_RIGHT);
  int stationStop = digitalRead(SENSOR_STATION_STOP);

  // Jika dikesan titik henti stesen
  if (stationStop == LOW) { // Mengikut konfigurasi sensor (LOW = dikesan)
    stopRobot();
    
    // Hantar notifikasi BLE ke Tablet bahawa robot sudah sampai di stesen
    String msg = "ARRIVED_STATION_" + String(currentTargetStation);
    if (deviceConnected && pCharacteristic != NULL) {
      pCharacteristic->setValue(msg.c_str());
      pCharacteristic->notify();
      Serial.println("Sampai! Notifikasi dihantar: " + msg);
    }
    return;
  }

  // Logik asas Line Tracking
  if (leftVal == HIGH && rightVal == HIGH) {
    moveForward();
  } else if (leftVal == LOW && rightVal == HIGH) {
    // Belok Kiri
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else if (leftVal == HIGH && rightVal == LOW) {
    // Belok Kanan
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
}

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
      Serial.println("Tablet disambung ke ESP32.");
    }
    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
      stopRobot();
      pServer->getAdvertising()->start();
      Serial.println("Tablet terputus.");
    }
};

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      String rxValue = pCharacteristic->getValue().c_str();
      if (rxValue.length() > 0) {
        Serial.print("Arahan diterima dari Tablet: ");
        Serial.println(rxValue);

        // Arahan bermula gerak ke stesen spesifik
        if (rxValue == "GOTO_STATION_1") {
          currentTargetStation = 1;
          moveForward();
        } else if (rxValue == "GOTO_STATION_2") {
          currentTargetStation = 2;
          moveForward();
        } else if (rxValue == "GOTO_STATION_3") {
          currentTargetStation = 3;
          moveForward();
        } else if (rxValue == "GOTO_STATION_4") {
          currentTargetStation = 4;
          moveForward();
        } else if (rxValue == "GOTO_STATION_5") {
          currentTargetStation = 5;
          moveForward();
        } else if (rxValue == "MOVE_NEXT") {
          if (currentTargetStation < 5) {
            currentTargetStation++;
            moveForward();
          } else {
            // Kembali ke Home
            currentTargetStation = 1;
            stopRobot();
          }
        } else if (rxValue == "STOP") {
          stopRobot();
        }
      }
    }
};

void setup() {
  Serial.begin(115200);

  // Set Pin Output Motor
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Set Pin Input Sensor
  pinMode(SENSOR_LEFT, INPUT);
  pinMode(SENSOR_RIGHT, INPUT);
  pinMode(SENSOR_STATION_STOP, INPUT);

  // Inisialisasi BLE
  BLEDevice::init("BATIK_BUDDY_ESP32");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY
                    );

  pCharacteristic->addDescriptor(new BLE2902());
  pCharacteristic->setCallbacks(new MyCallbacks());
  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  BLEDevice::startAdvertising();

  stopRobot();
  Serial.println("BATIK BUDDY ESP32 BLE Sedia!");
}

void loop() {
  lineFollowLogic();
  delay(10);
}
