#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//WIFI CONFIG
const char* ssid = " "; // ubah nama WiFi
const char* password = " "; // ubah password WiFi

// TELEGRAM
#define BOT_TOKEN " " // token bot Telegram
#define CHAT_ID " " // ID chat telegram

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

// CONFIG PIN
#define TRIG_PIN 5
#define ECHO_PIN 18
#define BUZZER_PIN 14

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// VAR
long duration;
float distance;

bool warningSent = false;  // status kirim pesan WASPADA
bool alertSent = false; // status kirim pesan BANJIR

// SENSOR
float readDistance() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if(duration == 0) return -1;

  return duration * 0.034 / 2;
}

// ========== SETUP ==========
void setup() {

  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(BUZZER_PIN, LOW);

  Wire.begin(21, 22);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("CONNECT WIFI");

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  client.setInsecure();

  lcd.clear();
  lcd.print("WIFI CONNECTED");

  bot.sendMessage(CHAT_ID, "UNIT TESTING ONLINE", "");

  delay(2000);
  lcd.clear();
}

//LOOP
void loop() {

  distance = readDistance();

  lcd.clear();

  if(distance < 0) {
    lcd.setCursor(0,0);
    lcd.print("SENSOR ERROR");
    return;
  }

  lcd.setCursor(0,0);
  lcd.print("Dist:");
  lcd.print(distance,1);
  lcd.print("cm");

  // WARNING AMAN
  if(distance > 20) { //UBAH RANGE SENSOR

    lcd.setCursor(0,1);
    lcd.print("AMAN");

    digitalWrite(BUZZER_PIN, LOW);

    warningSent = false;
    alertSent = false;
  }

  // WASPADA 
  else if(distance > 10) {

    lcd.setCursor(0,1);
    lcd.print("WASPADA");

    digitalWrite(BUZZER_PIN, LOW);

    if(!warningSent) {

      bot.sendMessage(CHAT_ID,
        "WASPADA BANJIR!\nJarak: " + String(distance), "");

      warningSent = true;
    }
  }

  // BANJIR
  else {

    lcd.setCursor(0,1);
    lcd.print("BANJIR!");

    digitalWrite(BUZZER_PIN, HIGH);
    delay(200); //delay BUZZER
    digitalWrite(BUZZER_PIN, LOW);
    delay(200);

    if(!alertSent) {

      bot.sendMessage(CHAT_ID,
        "BANJIR TERDETEKSI!\nJarak: " + String(distance), "");

      alertSent = true;
    }
  }

  delay(1000);
}
