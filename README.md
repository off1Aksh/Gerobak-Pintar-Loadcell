# Gerobak Pintar - Smart Cart Load Monitoring System

Sistem kontrol otomatisasi berbasis Arduino Nano yang dirancang untuk memonitor beban muatan pada gerobak komersial atau industri secara waktu nyata (real-time). Proyek ini berfokus pada akurasi pembacaan data sensor, mitigasi noise mekanis, dan manajemen daya, menjadikannya solusi yang tangguh untuk lingkungan operasional fisik.

## Fitur Teknis Utama
* **Pemrosesan Sinyal Presisi:** Menggunakan modul ADC HX711 24-bit untuk membaca fluktuasi tegangan diferensial dari sensor beban dengan tingkat presisi tinggi.
* **Mitigasi Noise (Data Smoothing):** Menerapkan algoritma pengambilan rata-rata dari 15 sampel data (sampling) secara terus-menerus untuk meredam lonjakan nilai (spike) yang disebabkan oleh getaran mekanis atau interferensi elektromagnetik pada perangkat keras.
* **Non-Volatile Zero Tracking:** Mengimplementasikan nilai kalibrasi dan nilai offset statis (hardcoded) ke dalam memori program. Hal ini mencegah sistem melakukan reset titik nol (tare) secara otomatis saat terjadi pemutusan daya dadakan (brownout) atau saat sistem dihidupkan ulang dalam keadaan bermuatan penuh.
* **Manajemen Daya Terpisah:** Memisahkan jalur daya logika (5V) dari modul mikrokontroler dengan jalur daya beban (12V) menggunakan isolasi optocoupler pada modul relay, sehingga mencegah lonjakan arus balik yang dapat merusak mikrokontroler.

## Spesifikasi Perangkat Keras
* **Mikrokontroler:** Arduino Nano (ATmega328P) dilengkapi dengan Shield Nano Terminal Adapter untuk koneksi perkabelan yang solid.
* **Sensor Beban:** Load Cell tipe Bar.
* **Pengondisi Sinyal:** Modul Penguat HX711 ADC 24-bit.
* **Antarmuka Pengguna (UI):** Layar LCD 16x2 dengan Modul Komunikasi Antarmuka I2C.
* **Aktuator:** Modul Relay 4-Channel 5VDC dengan logika Active LOW.
* **Sistem Peringatan:** 3 Unit Pilot Lamp 12V (Hijau, Kuning, Merah dengan Buzzer terintegrasi).
* **Manajemen Catu Daya:** Baterai/Aki Kendaraan 12V DC, Saklar Rocker 4-Pin (DPST), dan Modul Penurun Tegangan (Step-Down DC-to-DC Buck Converter) yang disetel pada output 5V.

## Pemetaan Pin (Wiring Diagram)
| Komponen Asal | Pin Asal | Komponen Tujuan | Pin Tujuan | Fungsi Jalur |
| :--- | :--- | :--- | :--- | :--- |
| Modul HX711 | DT (Data) | Arduino Nano | D2 | Jalur Komunikasi Data HX711[cite: 2] |
| Modul HX711 | SCK (Clock) | Arduino Nano | D3 | Jalur Komunikasi Clock HX711[cite: 2] |
| Layar LCD I2C | SDA | Arduino Nano | A4 | Jalur Komunikasi Data I2C[cite: 2] |
| Layar LCD I2C | SCL | Arduino Nano | A5 | Jalur Komunikasi Clock I2C[cite: 2] |
| Modul Relay 5V | IN1 | Arduino Nano | D5 | Pemicu Relay 1 (Pilot Lamp Hijau)[cite: 2] |
| Modul Relay 5V | IN2 | Arduino Nano | D6 | Pemicu Relay 2 (Pilot Lamp Kuning)[cite: 2] |
| Modul Relay 5V | IN3 | Arduino Nano | D7 | Pemicu Relay 3 (Pilot Lamp Merah + Buzzer)[cite: 2] |

## Logika Kontrol dan Ambang Batas Beban
Pengendalian aktuator menggunakan konfigurasi Active LOW, di mana pemberian sinyal `LOW` akan mengaktifkan kumparan relay. Sistem mengevaluasi pembacaan berat dan mengeksekusi kondisi berikut secara presisi:
1. **Beban < 150.0 Kg:** Sistem berada pada status normal. Mikrokontroler mengirimkan sinyal `LOW` ke Relay IN1 untuk menyalakan Pilot Lamp Hijau, dan sinyal `HIGH` ke relay lainnya[cite: 2].
2. **Beban 150.0 Kg - 350.0 Kg:** Sistem memasuki status waspada. Sinyal `LOW` dipindahkan ke Relay IN2 untuk menyalakan Pilot Lamp Kuning[cite: 2].
3. **Beban > 350.0 Kg:** Sistem mendeteksi beban berlebih kritis. Sinyal `LOW` dialihkan ke Relay IN3, mengaktifkan Pilot Lamp Merah secara bersamaan dengan Buzzer peringatan audio[cite: 2].

## Metodologi Kalibrasi dan Stabilitas Sistem
Nilai kalibrasi pada sistem ini diperoleh melalui proses pengukuran empiris dengan beban referensi standar. Nilai hambatan pada kabel sensor diverifikasi menggunakan ohmmeter untuk mengidentifikasi jalur eksitasi dan sinyal secara akurat, mengatasi inkonsistensi standar warna kabel pabrikan. Arsitektur kode dirancang untuk menginisialisasi semua pin relay pada kondisi `HIGH` sebelum modul utama diaktifkan. Algoritma inisialisasi ini merupakan langkah mitigasi krusial untuk mencegah penarikan arus masif (brownout) saat sistem melakukan booting awal.

---
**Pengembang:** Akasha Bin Ali | M. Zakky Ikhsanudin
*Proyek implementasi sistem kontrol otomatisasi perangkat keras - Mahasiswa Teknologi Rekayasa Komputer.*
