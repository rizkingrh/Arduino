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
#include "icon.h"

#define REPORTING_PERIOD_MS     1000

Adafruit_SSD1306 display(128, 64, &Wire);

char ssid[] = "";
char pass[] = "";

PulseOximeter pox;
uint32_t tsLastReport = 0;

void onBeatDetected() {
  Serial.println("Beat!!!");
  display.drawBitmap(62, 2, image_Layer_2_bits, 19, 8, 1);
  display.display();
}

void setup() {
  pinMode(buzzer, OUTPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.clearDisplay(); 
  display.drawBitmap(0, 0, bmp_cover, 128, 64, WHITE);
  display.display();
  delay(2000); 

  loading();

  if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");
  }
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
  pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop() {
  Blynk.run();
  pox.update();
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    display.clearDisplay();
    display.drawLine(4, 13, 123, 13, 1);
    display.drawBitmap(85, 2, image_Lock_7x8_bits, 7, 8, 1);
    display.drawBitmap(95, 2, image_Battery_26x8_bits, 26, 8, 1);
    display.drawBitmap(96, 3, image_Layer_5_bits, 12, 6, 1);
    
    display.setTextColor(1);
    display.setTextSize(1);
    display.setCursor(6, 3);
    display.setTextWrap(false);
    display.print("12:00");
    
    display.setTextColor(1);
    display.setTextSize(2);
    display.setCursor(4, 20);
    display.setTextWrap(false);
    display.print("BPM:");
    display.print(pox.getHeartRate());

    display.setTextColor(1);
    display.setTextSize(2);
    display.setCursor(4, 42);
    display.setTextWrap(false);
    display.print("Sp02:");
    display.print(pox.getSpO2());
    display.print("%"); 
    display.display();

    Serial.println(pox.getHeartRate());
    Serial.println(pox.getSpO2());
    Blynk.virtualWrite(V1, pox.getHeartRate());
    Blynk.virtualWrite(V2, pox.getSpO2());
    tsLastReport = millis();
  }
}

void loading() {
  display.clearDisplay();
  display.drawLine(4, 13, 123, 13, 1);
  display.drawBitmap(85, 2, image_Lock_7x8_bits, 7, 8, 1);
  display.drawBitmap(95, 2, image_Battery_26x8_bits, 26, 8, 1);
  display.drawBitmap(96, 3, image_Layer_5_bits, 12, 6, 1);
    
  display.setTextColor(1);
  display.setTextSize(1);
  display.setCursor(6, 3);
  display.setTextWrap(false);
  display.print("12:00");

  display.drawBitmap(7, 14, image_heartrate, 50, 50, 1);
  display.setTextColor(1);
  display.setTextSize(1);
  display.setCursor(61, 35);
  display.setTextWrap(false);
  display.print("Loading...");

  display.display();
  delay(3000);
}