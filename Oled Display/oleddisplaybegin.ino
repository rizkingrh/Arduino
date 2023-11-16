#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 64;  
const int reset = 4;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, reset);

void setup() {
// put your setup code here, to run once:
  Serial.begin(9600);
  // Cek konesi oled, termasuk 0x3C apa 0x3D
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }
  // Inisialisasi oled awal
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(32,15); // (x,y), x = panjang, y = tinggi
  display.println(F("Hello"));
  display.setCursor(20,32);
  display.println(F("TESTING"));
  display.display();
  delay(100); 
}

void loop() {
  
}