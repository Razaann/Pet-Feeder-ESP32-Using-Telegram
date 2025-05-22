#include <Wire.h>
#include <RTClib.h>
#include <ESP32Servo.h>
#include "HX711.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// Konfigurasi WiFi dan Telegram
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* botToken = "7973828596:AAEs6CKyd277c0jjzeHZVUzIG_pgfcSe7_M"; // Ganti sesuai token bot
const char* chatId = "1087541114"; // Ganti sesuai chatID

WiFiClientSecure client;
UniversalTelegramBot bot(botToken, client);

void sendTelegramMessage(String message) {
  bot.sendMessage(chatId, message, "Markdown");
}

// Objek RTC
RTC_DS1307 rtc;

// Objek Servo
Servo servoMotor;
const int servoPin = 5;

// Objek HX711
#define DT 13
#define SCK 12
HX711 scale;

// Faktor kalibrasi (sesuaikan dengan load cell Anda)
float calibration_factor = 420.0;

void setup() {
  Serial.begin(9600);
  Serial.println("Serial Monitor aktif");

  // Koneksi ke WiFi
  Serial.print("Menghubungkan ke WiFi");
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi terhubung!");


  // Inisialisasi RTC
  Wire.begin();
  if (!rtc.begin()) {
    Serial.println("RTC tidak terdeteksi!");
    while (1);
  }

  // Inisialisasi Servo
  servoMotor.attach(servoPin);
  servoMotor.write(0); // Posisi awal

  // Inisialisasi HX711
  scale.begin(DT, SCK);
  scale.set_scale(calibration_factor);
  scale.tare(); // Mengatur titik nol

  Serial.println("Sistem siap.");

  sendTelegramMessage("Cat Feeder telah menyala.");
}

void loop() {
  DateTime now = rtc.now();
  int jam = now.hour();
  int menit = now.minute();
  int detik = now.second();

  // Tampilkan waktu saat ini
  Serial.print("Waktu: ");
  Serial.print(jam);
  Serial.print(":");
  Serial.print(menit);
  Serial.print(":");
  Serial.println(detik);

  // Jadwal pemberian makan
  if ((jam == 6 && menit == 1 && detik == 1) || (jam == 12 && menit == 1 && detik == 1) || (jam == 18 && menit == 1 && detik == 1)) {
    kasihPakan();
  }

  delay(1000); // Tunggu 1 detik
}

void kasihPakan() {
  Serial.println("Memberikan makan...");
  servoMotor.write(180); // Putar servo
  delay(3000);           // Tunggu 3 detik
  servoMotor.write(0);   // Kembali ke posisi awal
  delay(1000);           // Tunggu 1 detik

  // Baca berat makanan yang tersisa
  float berat = scale.get_units(5);
  Serial.print("Sisa makanan: ");
  Serial.print(berat, 2);
  Serial.println(" kilogram");

  // Kirim pesan ke Telegram
  if (WiFi.status() == WL_CONNECTED) {
    String message = "Pakan telah diberikan.\nSisa makanan: " + String(berat, 2) + " kg";
    sendTelegramMessage(message);
  } else {
    Serial.println("WiFi tidak terhubung!");
  }
}

