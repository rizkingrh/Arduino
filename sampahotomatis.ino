#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myservo;

// ultrasonic1
int trigpin1 = 9;
int echopin1 = 10;
long duration1, distance1;

// ultrasonic2
int trigpin2 = 8;
int echopin2 = 7;
long duration2, distance2;

void setup()
{
    Serial.begin(9600);
    pinMode(trigpin1, OUTPUT);
    pinMode(echopin1, INPUT);
    pinMode(trigpin2, OUTPUT);
    pinMode(echopin2, INPUT);
    myservo.attach(6); // Menghubungkan servo ke pin 6
    myservo.write(90);
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Kapasitas Sampah");
}

void ultrasonic1()
{
    digitalWrite(trigpin1, HIGH);
    delayMicroseconds(1000);
    digitalWrite(trigpin1, LOW);
    duration1 = pulseIn(echopin1, HIGH);
    distance1 = (duration1 / 2) / 29.1;
    Serial.print("Ultrasonic 1 : ");
    Serial.print(distance1);
    Serial.println("CM");
    if (distance1 <= 10)
    {
        myservo.write(0);
    }
    else
    {
        myservo.write(90);
    }
}

void ultrasonic2()
{
    digitalWrite(trigpin2, HIGH);
    delayMicroseconds(1000);
    digitalWrite(trigpin2, LOW);
    duration2 = pulseIn(echopin2, HIGH);
    distance2 = (duration2 / 2) / 29.1;

    if (distance2 <= 5)
    {
        lcd.setCursor(0, 1);
        lcd.print("Full");
        Serial.println("Full      ");
    }
    else if (distance2 <= 10)
    {
        lcd.setCursor(0, 1);
        lcd.print("75%       ");
        Serial.println("75%");
    }
    else if (distance2 <= 15)
    {
        lcd.setCursor(0, 1);
        lcd.print("50%       ");
        Serial.println("50%");
    }
    else if (distance2 <= 20)
    {
        lcd.setCursor(0, 1);
        lcd.print("25%       ");
        Serial.println("25%");
    }
    else
    {
        lcd.setCursor(0, 1);
        lcd.print("Kosong    ");
        Serial.println("Kosong");
    }
}

void loop()
{
    ultrasonic1();
    delay(1000);
    ultrasonic2();
    delay(1000);
}