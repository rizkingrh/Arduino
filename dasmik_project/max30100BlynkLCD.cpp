//scientist BENIELS LAB
/* CREATED BY: HOW TO ELECTRONICS | MODIFIED BY: SCIENTIST BENIELS  LAB */
#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN ""
#define BLYNK_PRINT Serial

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS     1000

Adafruit_SSD1306 display(128, 64, &Wire);

char ssid[] = "";
char pass[] = "";

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
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }  
  //----------------------------------------menampilkan logo
  display.clearDisplay(); 
  display.drawBitmap(0, 0, bmp_cover, 128, 64, WHITE);
  display.display();
  delay(3000); 

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20, 5);
  display.print("Please Waiting");
  display.setCursor(42, 20); 
  display.print("To get");
  display.setCursor(4, 35);
  display.print("The Heart Rate value");
  display.display(); 
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
    
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print(pox.getHeartRate());

    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 32);
    display.print(pox.getSpO2());
    display.display(); 

    Serial.println(pox.getHeartRate());
    Serial.println(pox.getSpO2());
    Blynk.virtualWrite(V1, pox.getHeartRate());
    Blynk.virtualWrite(V2, pox.getSpO2());
    tsLastReport = millis();

    // if (pox.getSpO2() >= 96) {
    //   lcd.setCursor(15 , 1);
    //   lcd.write(1);                 
    // }
    // else if (pox.getSpO2() <= 95 && pox.getSpO2() >= 91) {
    //   lcd.setCursor(15 , 1);
    //   lcd.write(2);                 
    // }
    // else if (pox.getSpO2() <= 90) {
    //   lcd.setCursor(15 , 1);
    //   lcd.write(3);
    // }
  }
}