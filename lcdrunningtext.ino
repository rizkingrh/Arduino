#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int posisi = 0;

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop()
{
  lcd.clear();
  lcd.setCursor(posisi, 0);
  lcd.print("Hello, World!");
  lcd.setCursor(posisi, 1);
  lcd.print("Testing Running");
  posisi = posisi + 1;

  if (posisi < 0 || posisi >= 16)
  {
    posisi = 0;
  }

  delay(500);
}