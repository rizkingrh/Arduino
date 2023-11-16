// 1. Cari gif icon di icons8 
// 2. Split gif to frame
// 3. Ubah gambar tersebut ke bentuk bitmap, pake "https://javl.github.io/image2cpp/"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "icon.h"

const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 64;  
const int reset = 4;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, reset);

// Untuk animation icon
const int dly = 25;
const int x = 38;
const int y = 6;
const int pixel1 = 50;
const int pixel2 = 50;

void animicon() {
  display.clearDisplay(); 
  display.drawBitmap(x, y, bitmap_card1, pixel1, pixel2, WHITE); 
  display.display();
  delay(dly);

  display.clearDisplay(); 
  display.drawBitmap(x, y, bitmap_card2, pixel1, pixel2, WHITE); 
  display.display();
  delay(dly);

  display.clearDisplay(); 
  display.drawBitmap(x, y, bitmap_card3, pixel1, pixel2, WHITE); 
  display.display();
  delay(dly);

  display.clearDisplay(); 
  display.drawBitmap(x, y, bitmap_card4, pixel1, pixel2, WHITE); 
  display.display();
  delay(dly);
  
  display.clearDisplay(); 
  display.drawBitmap(x, y, bitmap_card5, pixel1, pixel2, WHITE); 
  display.display();
  delay(dly);

  display.clearDisplay(); 
  display.drawBitmap(x, y, bitmap_card6, pixel1, pixel2, WHITE); 
  display.display();
  delay(dly);

  display.clearDisplay(); 
  display.drawBitmap(x, y, bitmap_card7, pixel1, pixel2, WHITE); 
  display.display();
  delay(dly);

  display.clearDisplay(); 
  display.drawBitmap(x, y, bitmap_card8, pixel1, pixel2, WHITE); 
  display.display();
  delay(dly);

  display.clearDisplay(); 
  display.drawBitmap(x, y, bitmap_card9, pixel1, pixel2, WHITE); 
  display.display();
  delay(dly);

  display.clearDisplay(); 
  display.drawBitmap(x, y, bitmap_card10, pixel1, pixel2, WHITE); 
  display.display();
  delay(dly);

  display.clearDisplay(); 
  display.drawBitmap(x, y, bitmap_card11, pixel1, pixel2, WHITE); 
  display.display();
  delay(dly);

  display.clearDisplay(); 
  display.drawBitmap(x, y, bitmap_card12, pixel1, pixel2, WHITE); 
  display.display();
  delay(dly);
  
  display.clearDisplay(); 
  display.drawBitmap(x, y, bitmap_card13, pixel1, pixel2, WHITE); 
  display.display();
  delay(dly);

  display.clearDisplay(); 
  display.drawBitmap(x, y, bitmap_card14, pixel1, pixel2, WHITE); 
  display.display();
  delay(dly);

  display.clearDisplay(); 
  display.drawBitmap(x, y, bitmap_card15, pixel1, pixel2, WHITE); 
  display.display();
  delay(dly);

  display.clearDisplay(); 
  display.drawBitmap(x, y, bitmap_card16, pixel1, pixel2, WHITE); 
  display.display();
  delay(dly);

  display.clearDisplay(); 
  display.drawBitmap(x, y, bitmap_card17, pixel1, pixel2, WHITE); 
  display.display();
  delay(dly);

  display.clearDisplay(); 
  display.drawBitmap(x, y, bitmap_card18, pixel1, pixel2, WHITE); 
  display.display();
  delay(dly);

  display.clearDisplay(); 
  display.drawBitmap(x, y, bitmap_card19, pixel1, pixel2, WHITE); 
  display.display();
  delay(dly);

  display.clearDisplay(); 
  display.drawBitmap(x, y, bitmap_card20, pixel1, pixel2, WHITE); 
  display.display();
  delay(dly);
  
  display.clearDisplay(); 
  display.drawBitmap(x, y, bitmap_card21, pixel1, pixel2, WHITE); 
  display.display();
  delay(dly);

  display.clearDisplay(); 
  display.drawBitmap(x, y, bitmap_card22, pixel1, pixel2, WHITE); 
  display.display();
  delay(dly);

  display.clearDisplay(); 
  display.drawBitmap(x, y, bitmap_card23, pixel1, pixel2, WHITE); 
  display.display();
  delay(dly);

  display.clearDisplay(); 
  display.drawBitmap(x, y, bitmap_card24, pixel1, pixel2, WHITE); 
  display.display();
  delay(dly);

  display.clearDisplay(); 
  display.drawBitmap(x, y, bitmap_card25, pixel1, pixel2, WHITE); 
  display.display();
  delay(dly);

  display.clearDisplay(); 
  display.drawBitmap(x, y, bitmap_card26, pixel1, pixel2, WHITE); 
  display.display();
  delay(dly);

  display.clearDisplay(); 
  display.drawBitmap(x, y, bitmap_card27, pixel1, pixel2, WHITE); 
  display.display();
  delay(dly);

  display.clearDisplay(); 
  display.drawBitmap(x, y, bitmap_card28, pixel1, pixel2, WHITE); 
  display.display();
  delay(dly);
}

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
  delay(3000); 
}

void loop() {
  animicon();
}

