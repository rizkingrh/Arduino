//scientist BENIELS LAB
/* CREATED BY: HOW TO ELECTRONICS | MODIFIED BY: SCIENTIST BENIELS  LAB */
#define BLYNK_TEMPLATE_ID "TMPL6yrMewhS5"
#define BLYNK_TEMPLATE_NAME "Projectdasmik"
#define BLYNK_AUTH_TOKEN "9N5wcSd9KXz_d8lXB_H5pLIG-7tPg5NR"
#define BLYNK_PRINT Serial

#include "CTBot.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS     1000

CTBot myBot;
LiquidCrystal_I2C lcd(0x27, 16, 2);

char ssid[] = "Redmi";
char pass[] = "12345678";
String token = "6453487650:AAH0-We-9-RvDuVj9FYumzELSJGCAo4TI9U";
const int id = 1837173195;
String pesan = "";

byte smile[] = {
  B00000,
  B00000,
  B01010,
  B00000,
  B10001,
  B01110,
  B00000,
  B00000
};
byte mod[] = {
  B00000,
  B00000,
  B01010,
  B00000,
  B11111,
  B00000,
  B00000,
  B00000
};
byte sad[] = {
  B00000,
  B00000,
  B01010,
  B00000,
  B01110,
  B10001,
  B00000,
  B00000
};

PulseOximeter pox;
uint32_t tsLastReport = 0;

void onBeatDetected()
{

  Serial.println("Beat!!!");

}

void setup()
{
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.begin(115200);
  Serial.println("Starting telegram bot...");

  myBot.wifiConnect(ssid, pass);
  myBot.setTelegramToken(token);

  if (myBot.testConnection()){
    Serial.println("Connection Success...");
  } else {
    Serial.println("Connection Failed...");
  }

  lcd.init();
  lcd.backlight();
  lcd.createChar(1 , smile);
  lcd.createChar(2 , mod);
  lcd.createChar(3 , sad);
  lcd.setCursor(0, 0);
  lcd.print("      Pluse");
  lcd.setCursor(0, 1);
  lcd.print("    Oximeter");
  delay(2000);

  if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");
  }
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);

  pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop()
{
  Blynk.run();
  pox.update();
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {

    lcd.clear();
    lcd.setCursor(0 , 0);
    lcd.print("BPM : ");
    lcd.print(pox.getHeartRate());
    Serial.println(pox.getHeartRate());
    Blynk.virtualWrite(V1, pox.getHeartRate());
    lcd.setCursor(0 , 1);
    lcd.print("Sp02: ");
    lcd.print(pox.getSpO2());
    Serial.println(pox.getSpO2());
    lcd.print("%");
    Blynk.virtualWrite(V2, pox.getSpO2());
    tsLastReport = millis();

    if (pox.getSpO2() >= 96) {
      lcd.setCursor(15 , 1);
      lcd.write(1);                 
    }
    else if (pox.getSpO2() <= 95 && pox.getSpO2() >= 91) {
      lcd.setCursor(15 , 1);
      lcd.write(2);                 
    }
    else if (pox.getSpO2() <= 90) {
      lcd.setCursor(15 , 1);
      lcd.write(3);
    }
  }
}
