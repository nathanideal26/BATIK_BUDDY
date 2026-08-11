import Foundation
import CoreBluetooth

class BLEManager: NSObject, ObservableObject, CBCentralManagerDelegate, CBPeripheralDelegate {
    var centralManager: CBCentralManager!
    @Published var isConnected = false
    @Published var spikePeripheral: CBPeripheral?
    var txCharacteristic: CBCharacteristic?
    
    override init() {
        super.init()
        centralManager = CBCentralManager(delegate: self, queue: nil)
    }
    
    func centralManagerDidUpdateState(_ central: CBCentralManager) {
        if central.state == .poweredOn {
            centralManager.scanForPeripherals(withServices: nil, options: nil)
        }
    }
    
    func centralManager(_ central: CBCentralManager, didDiscover peripheral: CBPeripheral, advertisementData: [String : Any], rssi RSSI: NSNumber) {
        if let name = peripheral.name, name.contains("SPIKE") || name.contains("LEGO") {
            self.spikePeripheral = peripheral
            self.spikePeripheral?.delegate = self
            self.centralManager.stopScan()
            self.centralManager.connect(peripheral, options: nil)
        }
    }
    
    func centralManager(_ central: CBCentralManager, didConnect peripheral: CBPeripheral) {
        DispatchQueue.main.async {
            self.isConnected = true
        }
        peripheral.discoverServices(nil)
    }
    
    func centralManager(_ central: CBCentralManager, didDisconnectPeripheral peripheral: CBPeripheral, error: Error?) {
        DispatchQueue.main.async {
            self.isConnected = false
        }
        centralManager.scanForPeripherals(withServices: nil, options: nil)
    }
    
    func sendCommand(_ command: String) {
        guard let peripheral = spikePeripheral, let tx = txCharacteristic else { return }
        if let data = command.data(using: .utf8) {
            peripheral.writeValue(data, for: tx, type: .withoutResponse)
        }
    }
}
