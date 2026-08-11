import hub
import utime

# Inisialisasi Perkakasan LEGO SPIKE Prime
display = hub.display
light_matrix = hub.port.A  # Hub LED atau aksesori luaran jika ada

def show_sleep_face():
    # Muka Tidur (Mata Terpejam)
    sleep_img = hub.Image("00000:00000:09090:00000:00000")
    display.show(sleep_img)

def show_wakeup_face():
    # Muka Bangun / Gembira
    display.show(hub.Image.HAPPY)

def show_speaking_anim():
    # Animasi Robot Bercakap / Berkelip
    for _ in range(3):
        display.show(hub.Image.SURPRISED)
        utime.sleep(0.3)
        display.show(hub.Image.HAPPY)
        utime.sleep(0.3)

# Status Asal: Sleep Mode
current_state = "SLEEP"
show_sleep_face()

print("Batik Buddy SPIKE Prime Ready. Awaiting iPad Mini Command...")

# Gelung Utama (Main Loop)
while True:
    # Contoh penerimaan arahan melalui Bluetooth atau Isyarat Sentuhan
    # (Apabila disambungkan dengan iPad Mini via BLE)
    
    # 1. Mengendali arahan WAKEUP
    if current_state == "WAKEUP":
        show_wakeup_face()
        utime.sleep(1)
        show_speaking_anim()
        current_state = "IDLE"
        
    # 2. Sentiasa kekal dalam mod sedia jika tidak dipanggil
    utime.sleep(0.1)
