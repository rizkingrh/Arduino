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
#include "icon.h"

#define REPORTING_PERIOD_MS     1000

Adafruit_SSD1306 display(128, 64, &Wire);

char ssid[] = "";
char pass[] = "";

PulseOximeter pox;
uint32_t tsLastReport = 0;

static const unsigned char PROGMEM image_Lock_7x8_bits[] = {0x38,0x44,0x44,0xfe,0xfe,0xee,0xfe,0x7c};
static const unsigned char PROGMEM image_Battery_26x8_bits[] = {0x7f,0xff,0xfe,0x00,0x80,0x00,0x01,0x00,0x80,0x00,0x01,0xc0,0x80,0x00,0x01,0x40,0x80,0x00,0x01,0x40,0x80,0x00,0x01,0xc0,0x80,0x00,0x01,0x00,0x7f,0xff,0xfe,0x00};
static const unsigned char PROGMEM image_Layer_5_bits[] = {0xff,0xf0,0xff,0xf0,0xff,0xf0,0xff,0xf0,0xff,0xf0,0xff,0xf0};

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