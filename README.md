# IoT Water Surface Detection using ESP8266

Sistem monitoring ketinggian air berbasis IoT menggunakan ESP8266 dengan notifikasi Telegram, LCD display, dan buzzer alarm.

---

## Features

-  Real-time water level detection using ultrasonic sensor
-  LCD display (status + distance)
-  Buzzer alarm saat kondisi banjir
-  Telegram notification (WASPADA & BANJIR)
-  WiFi connectivity (IoT enabled)
-  Anti-spam notification system

---

## System Logic

Jarak > 20 cm  AMAN => Normal 
Jarak 10 - 20 cm Status:WASPADA => Buzzer + Telegram Notif dikirim
Jarak < 10 cm Status:BANJIR => Buzzer + Telegram Notif dikirim

---

## Hardware

- NodeMCU ESP8266
- HC-SR04 Ultrasonic Sensor
- LCD 16x2 I2C (0x27)
- Buzzer
- Resistor divider (untuk pin ECHO Pada sensor)
- Jumper wires

---

## Library

Install via Arduino IDE Library Manager:

- ESP8266WiFi
- UniversalTelegramBot
- ArduinoJson
- LiquidCrystal_I2C
- Wire

---

##Configuration

Edit kode berikut untuk konfigurasi wifi dan API BOT

```
const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";

#define BOT_TOKEN "YOUR_TELEGRAM_BOT_TOKEN"
#define CHAT_ID "YOUR_CHAT_ID"
