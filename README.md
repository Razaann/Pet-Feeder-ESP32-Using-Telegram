# 🐾 Pet Feeder ESP32 Using Telegram

This is an **Internet of Things (IoT)** project built using Wokwi that automates scheduled feeding for your pet. It uses an ESP32 microcontroller, a servo motor, a load cell with HX711, and an RTC module to dispense food at specific times and notifies you via Telegram about the status and remaining food weight.

## 🚀 Features

- Automatic scheduled feeding system
- Sends notification via Telegram after each feeding:
  - Confirms feeding
  - Displays how much food is left (in grams)
- Simulated using [Wokwi](https://wokwi.com/)

## 🧰 Hardware Components

- ESP32 Dev Board
- Servo Motor
- HX711 + Load Cell
- RTC Module (DS3231)
- Internet connection via Wi-Fi

## 🛠️ Libraries Used

Ensure these libraries are installed in your Arduino IDE:
- `WiFi.h`
- `HTTPClient.h`
- `HX711.h`
- `RTClib.h`
- `Wire.h`

## 🖼️ Wokwi Preview
![Preview](https://i.imghippo.com/files/RzK2304iMc.png)

## 💬 Telegram Setup

This project **sends notifications only** (no user commands). To receive messages:
1. Create a bot with [@BotFather](https://t.me/BotFather) on Telegram and get your Bot Token.
2. Get your Telegram `chat_id` using [@IDBot](https://web.telegram.org/a/#100237842).
3. Paste both the token and `chat_id` in the code before uploading.

## ⏱️ How It Works

1. The ESP32 reads the current time from the RTC.
2. At the preset schedule, it:
   - Rotates the servo to dispense food.
   - Reads the weight from the load cell.
   - Sends a notification via Telegram that feeding was successful.
   - Displays how much food is left (based on weight reading).

## ⚙️ Configuration

Update these fields in the code:
```cpp
// Configuration WiFi & Telegram
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* botToken = "7973828596:AAEs6CKyd277c0jjzeHZVUzIG_pgfcSe7_M"; // Change The Token Bot If Needed
const char* chatId = "1087541114"; // Change The IDBot
