# BATIK BUDDY - BATIK MUZIUM ROBOT GUIDE

Aplikasi interaktif iPad Mini yang dihubungkan dengan robot LEGO SPIKE Prime sebagai pemandu pelawat MuzIUM Batik.

## 📱 Alur Kerja Paparan (UI Flow)
1. **Sleep Mode (Paparan 1):** Robot dan skrin berada dalam mod sedia.
2. **Wakeup & Greetings (Paparan 2):** Skrin disentuh → Robot bangkit dan menyapa: *"Hi, I'm Batik Buddy, your Batik Museum guide!"*
3. **Pemilihan Bahasa:** Pilihan *Bahasa Melayu* atau *English*.
4. **Mod Utama:** Imbasan AR, Studio Canting Digital, & Peta Muzium.

## 🔌 Integrasi Perkakasan
- **Tablet:** iPad Mini (iOS / SwiftUI @ Flutter)
- **Robot:** LEGO SPIKE Prime (MicroPython via Bluetooth LE / BLE)
- **Sensor:** Touch Sensor / Distance Sensor & Matriks LED $5 \times 5$

## 📁 Struktur Repositori
```text
├── ipad-app/          # Kod aplikasi SwiftUI / Flutter
└── spike-prime/       # Kod kawalan MicroPython untuk LEGO SPIKE Prime
