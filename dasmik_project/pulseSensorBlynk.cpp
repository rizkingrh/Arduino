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
#include "icon.h"

Adafruit_SSD1306 display(128, 64, &Wire);

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";

unsigned long previousMillisGetHR = 0; //--> menyimpan waktu millis ketika sudah diperbaharui (heartbeat)
unsigned long previousMillisResultHR = 0; //--> menyimpan waktu millis ketika sudah diperbaharui (BPM)
const long intervalGetHR = 20; //--> Interval pebacaan.
const long intervalResultHR = 5000; //--> Interval pembacaan setiap 5 detik
int PulseSensorSignal; 
const int buzzer = 15; // D8
const int PulseSensorHRWire = A0; 
int UpperThreshold = 540; 
int LowerThreshold = 520; 
int cntHB = 0; 
boolean ThresholdStat = true; //--> variabel untuk mentriger detak jantung
int detak_jantung = 0; 

int x=0; 
int y=0; 
int lastx=0;
int lasty=0;

//---------------------------------------------------Logo Hati-----------------------------------
const unsigned char Heart_Icon [] PROGMEM = {
  0x00, 0x00, 0x18, 0x30, 0x3c, 0x78, 0x7e, 0xfc, 0xff, 0xfe, 0xff, 0xfe, 0xee, 0xee, 0xd5, 0x56, 
  0x7b, 0xbc, 0x3f, 0xf8, 0x1f, 0xf0, 0x0f, 0xe0, 0x07, 0xc0, 0x03, 0x80, 0x01, 0x00, 0x00, 0x00
};

void setup() {
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600); 
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }  
  //----------------------------------------menampilkan logo
  display.clearDisplay(); 
  display.drawBitmap(0, 0, bmp_cover, 128, 64, WHITE);
  display.display();
  delay(3000); 

  //----------------------------------------menampilkan nilai bpm
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
  
  //----------------------------------------tampilan pertama mebuat nilai bpm 0
  display.clearDisplay(); 
  display.drawBitmap(0, 47, Heart_Icon, 16, 16, WHITE);
  
  display.drawLine(0, 43, 127, 43, WHITE);
  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(20, 48); 
  display.print(": 0 BPM");
  display.display(); 
  Serial.println();
  Serial.println("Please wait 10 seconds to get the BPM Value");

  digitalWrite(buzzer, HIGH);
  delay(2500);
  digitalWrite(buzzer, LOW);
}

void loop() { 
  Blynk.run();
  GetHeartRate();
}

void GetHeartRate() {
  //----------------------------------------proses pembacaan.
  unsigned long currentMillisGetHR = millis();

  if (currentMillisGetHR - previousMillisGetHR >= intervalGetHR) {
    previousMillisGetHR = currentMillisGetHR;

    PulseSensorSignal = analogRead(PulseSensorHRWire);
    // Serial.print(PulseSensorSignal);
    // Serial.print("   ");

    if (PulseSensorSignal > UpperThreshold && ThresholdStat == true) {
      cntHB++;
      ThresholdStat = false;
    }

    if (PulseSensorSignal < LowerThreshold) {
      ThresholdStat = true;
    }
    
    DrawGraph();
  }
  //Konversi pembacaan Analog ke nilai BPM
  unsigned long currentMillisResultHR = millis();

  if (currentMillisResultHR - previousMillisResultHR >= intervalResultHR) {
    previousMillisResultHR = currentMillisResultHR;

    detak_jantung = cntHB * 6;
    Serial.print("BPM : ");
    Serial.println(detak_jantung);
    Blynk.virtualWrite(V0, detak_jantung);
    
    display.fillRect(20, 48, 108, 18, BLACK);
    
    display.drawBitmap(0, 47, Heart_Icon, 16, 16, WHITE); 
    display.drawLine(0, 43, 127, 43, WHITE); 
  
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(20, 48);
    display.print(": ");
    display.print(detak_jantung);
    display.display(); 
    
    cntHB = 0;
    
    if (detak_jantung >= 40) {
      digitalWrite(buzzer, HIGH);
    } else {
      digitalWrite(buzzer, LOW);
    }
  }
}
//--------------------------------------------------------------------------------membuat grafik
void DrawGraph() {
  if (x > 127) {
    display.fillRect(0, 0, 128, 42, BLACK);
    x = 0;
    lastx = 0;
  }
  int ySignal = PulseSensorSignal; 
  
  if (ySignal > 850) ySignal = 850;
  if (ySignal < 350) ySignal = 350;

  int ySignalMap = map(ySignal, 350, 850, 0, 40);    
  
  y = 40 - ySignalMap;
  // Serial.println(y);
  display.writeLine(lastx,lasty,x,y,WHITE);
  display.display();   
  lastx = x;
  lasty = y;
  
  x++;
}
