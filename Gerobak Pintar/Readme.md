# Gerobak Pintar (Smart Cart Load Monitoring System)

Sistem kontrol otomatisasi berbasis Arduino Nano untuk memonitor beban muatan pada gerobak secara *real-time*. Sistem ini dilengkapi dengan sensor load cell presisi tinggi dan memberikan umpan balik visual serta audio secara otomatis berdasarkan ambang batas berat yang telah ditentukan.

## Fitur Utama
- **Real-Time Load Sensing:** Membaca beban muatan menggunakan Load Cell dan ADC HX711 24-bit.
- **Data Smoothing:** Mengambil rata-rata 15 sampel (*sampling*) untuk meredam fluktuasi (*noise*) dan getaran mekanis.
- **Non-Volatile Zero Tracking (Hardcoded Offset):** Menggunakan nilai *offset* statis agar titik nol (0 Kg) tidak ter-reset meskipun sistem dimatikan dan dinyalakan kembali dalam keadaan bermuatan penuh.
- **Intelligent Status Indicator:** Tiga tingkat peringatan otomatis menggunakan modul relay (Active LOW) untuk mengontrol lampu indikator 12V.

## Komponen Perangkat Keras
- Mikrokontroler: Arduino Nano + Nano Terminal Adapter[cite: 2]
- Sensor Berat: Load Cell tipe Bar + Modul Penguat HX711[cite: 2]
- Display: Layar LCD 16x2 dengan Modul I2C[cite: 2]
- Aktuator: Modul Relay 4-Channel 5VDC (Active LOW)[cite: 2]
- Indikator: 3 Unit Pilot Lamp 12V (Hijau, Kuning, Merah + Buzzer)[cite: 2]
- Catu Daya: Aki 12V DC, Saklar Rocker 4-Pin, Step-Down DC-DC Buck Converter (Set 5V)[cite: 2]

## Pemetaan Pin (Wiring Diagram)

| Komponen Asal | Pin Asal    | Komponen Tujuan | Pin Tujuan | Fungsi                             |
| :------------ | :---------- | :-------------- | :--------- | :--------------------------------- |
| **HX711**     | DT (Data)   | Arduino Nano    | D2         | Komunikasi Data[cite: 2]           |
| **HX711**     | SCK (Clock) | Arduino Nano    | D3         | Komunikasi Clock[cite: 2]          |
| **Layar LCD** | SDA         | Arduino Nano    | A4         | Data I2C[cite: 2]                  |
| **Layar LCD** | SCL         | Arduino Nano    | A5         | Clock I2C[cite: 2]                 |
| **Relay 5V**  | IN1         | Arduino Nano    | D5         | Pilot Lamp Hijau[cite: 2]          |
| **Relay 5V**  | IN2         | Arduino Nano    | D6         | Pilot Lamp Kuning[cite: 2]         |
| **Relay 5V**  | IN3         | Arduino Nano    | D7         | Pilot Lamp Merah + Buzzer[cite: 2] |

*Catatan Distribusi Daya: Suplai VCC 5V dan Ground untuk sensor, relay, dan LCD diambil secara terpusat dari Modul Step-Down DC-DC yang terhubung ke Nano Extender[cite: 2]. Arus tinggi 12V untuk lampu diputus-sambungkan melalui terminal COM dan NO pada saklar mekanis Relay[cite: 2].*

## Ambang Batas Beban (Load Thresholds)
Sistem ini menggunakan logika *Active LOW* (menuliskan `LOW` untuk menyalakan relay) dengan parameter batas berikut:
1. **< 150.0 Kg:** Status `AMAN` (Lampu Hijau Menyala).
2. **150.0 - 350.0 Kg:** Status `WASPADA` (Lampu Kuning Menyala).
3. **> 350.0 Kg:** Status `BERAT!` (Lampu Merah dan Buzzer Menyala).

## Instalasi dan Penggunaan
1. Unduh dan instal [Arduino IDE](https://www.arduino.cc/en/software).
2. Tambahkan *library* berikut melalui *Library Manager* di Arduino IDE:
   - `HX711_ADC` oleh Olav Kallhovd (atau library HX711 standar)
   - `LiquidCrystal I2C` oleh Frank de Brabander
3. Buka file `Gerobak_Pintar.ino`.
4. Sesuaikan nilai `angka_kalibrasi` dan `angka_offset` pada kode dengan hasil kalibrasi perangkat keras fisik Anda.
5. *Upload* program ke Arduino Nano (Pastikan *Board* diset ke "Arduino Nano" dan *Processor* "ATmega328P / ATmega328P Old Bootloader").

---
*Dibuat untuk proyek otomatisasi mekanis tingkat terapan.*