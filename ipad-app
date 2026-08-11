import SwiftUI
import CoreBluetooth

struct ContentView: View {
    // Status Aplikasi & Bahasa
    @State private var appState: AppState = .sleep
    @State private var selectedLanguage: Language? = nil
    @State private var isSpikeConnected: Bool = true // Status Sambungan BLE SPIKE Prime
    
    enum AppState {
        case sleep
        case wakeup
        case languageSelect
        case mainDashboard
    }
    
    enum Language: String {
        case malay = "Bahasa Melayu"
        case english = "English"
    }
    
    var body: some View {
        ZStack {
            // Latar Belakang Khas Batik / Gelap
            Color(red: 0.07, green: 0.09, blue: 0.15)
                .ignoresSafeArea()
            
            VStack {
                // Bar Status Sambungan SPIKE Prime (Bahagian Atas)
                HStack {
                    HStack(spacing: 6) {
                        Circle()
                            .fill(isSpikeConnected ? Color.green : Color.red)
                            .frame(width: 10, height: 10)
                        Text(isSpikeConnected ? "LEGO SPIKE Prime: Connected" : "SPIKE Prime: Disconnected")
                            .font(.system(size: 12, weight: .medium, design: .monospaced))
                            .foregroundColor(.white.opacity(0.8))
                    }
                    .padding(.horizontal, 12)
                    .padding(.vertical, 6)
                    .background(Color.white.opacity(0.1))
                    .cornerRadius(20)
                    
                    Spacer()
                }
                .padding()

                Spacer()

                // KANDUNGAN UTAMA MENGIKUT STATUS
                switch appState {
                case .sleep:
                    sleepView
                case .wakeup:
                    wakeupView
                case .languageSelect:
                    languageSelectView
                case .mainDashboard:
                    mainDashboardView
                }
                
                Spacer()
            }
        }
    }

    // MARK: - PAPARAN 1: SLEEP MODE
    var sleepView: some View {
        VStack(spacing: 25) {
            ZStack {
                Circle()
                    .fill(Color.blue.opacity(0.15))
                    .frame(width: 180, height: 180)
                
                Image(systemName: "moon.stars.fill")
                    .font(.system(size: 80))
                    .foregroundColor(.cyan)
            }
            
            Text("BATIK BUDDY")
                .font(.system(size: 32, weight: .bold, design: .rounded))
                .foregroundColor(.white)
            
            Text("Robot dalam Mod Sedia / Sleep Mode")
                .font(.subheadline)
                .foregroundColor(.gray)
            
            Text("👉 Sentuh skrin untuk mengejutkan Novus")
                .font(.callout)
                .foregroundColor(.cyan)
                .padding(.top, 10)
        }
        .contentShape(Rectangle())
        .onTapGesture {
            withAnimation(.spring()) {
                appState = .wakeup
            }
        }
    }

    // MARK: - PAPARAN 2: WAKEUP & GREETING
    var wakeupView: some View {
        VStack(spacing: 25) {
            ZStack {
                Circle()
                    .fill(Color.green.opacity(0.2))
                    .frame(width: 160, height: 160)
                
                Image(systemName: "cpu.fill")
                    .font(.system(size: 75))
                    .foregroundColor(.green)
            }
            
            VStack(spacing: 12) {
                Text("“Hi! I'm Batik Buddy, your Batik Museum guide.”")
                    .font(.system(size: 24, weight: .semibold, design: .rounded))
                    .multilineTextAlignment(.center)
                    .foregroundColor(.white)
                    .padding(.horizontal, 40)
                
                Text("Novus sedia membantu anda meneroka Muzium Batik.")
                    .font(.body)
                    .foregroundColor(.gray)
            }
            
            Button(action: {
                withAnimation {
                    appState = .languageSelect
                }
            }) {
                HStack {
                    Text("Teruskan / Continue")
                        .fontWeight(.bold)
                    Image(systemName: "arrow.right")
                }
                .padding(.horizontal, 30)
                .padding(.vertical, 15)
                .background(Color.blue)
                .foregroundColor(.white)
                .cornerRadius(15)
            }
            .padding(.top, 15)
        }
    }

    // MARK: - PAPARAN 3: PILIHAN BAHASA
    var languageSelectView: some View {
        VStack(spacing: 30) {
            Text("Sila Pilih Bahasa / Select Language")
                .font(.system(size: 26, weight: .bold))
                .foregroundColor(.white)
            
            HStack(spacing: 25) {
                // Option: Bahasa Melayu
                Button(action: {
                    selectedLanguage = .malay
                    withAnimation { appState = .mainDashboard }
                }) {
                    VStack(spacing: 12) {
                        Text("🇲🇾")
                            .font(.system(size: 50))
                        Text("Bahasa Melayu")
                            .font(.headline)
                            .foregroundColor(.white)
                    }
                    .frame(width: 180, height: 140)
                    .background(Color.white.opacity(0.1))
                    .overlay(
                        RoundedRectangle(cornerRadius: 16)
                            .stroke(selectedLanguage == .malay ? Color.green : Color.clear, lineWidth: 3)
                    )
                    .cornerRadius(16)
                }

                // Option: English
                Button(action: {
                    selectedLanguage = .english
                    withAnimation { appState = .mainDashboard }
                }) {
                    VStack(spacing: 12) {
                        Text("🇬🇧")
                            .font(.system(size: 50))
                        Text("English")
                            .font(.headline)
                            .foregroundColor(.white)
                    }
                    .frame(width: 180, height: 140)
                    .background(Color.white.opacity(0.1))
                    .overlay(
                        RoundedRectangle(cornerRadius: 16)
                            .stroke(selectedLanguage == .english ? Color.green : Color.clear, lineWidth: 3)
                    )
                    .cornerRadius(16)
                }
            }
        }
    }

    // MARK: - PAPARAN 4: DASHBOARD UTAMA
    var mainDashboardView: some View {
        VStack(spacing: 20) {
            Text("Selamat Datang ke Muzium Batik!")
                .font(.title)
                .bold()
                .foregroundColor(.white)
            
            Text("Bahasa Dipilih: \(selectedLanguage?.rawValue ?? "")")
                .foregroundColor(.green)
            
            Button("Kembali ke Mod Tidur") {
                withAnimation {
                    appState = .sleep
                }
            }
            .foregroundColor(.red)
            .padding(.top, 20)
        }
    }
}
