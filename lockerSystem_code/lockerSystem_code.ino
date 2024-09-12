#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define RST_PIN 5
#define SDA_PIN 10
#define RELAY_PIN 4
#define BUZZER_PIN 6

MFRC522 mfrc522(SDA_PIN, RST_PIN);   // Create MFRC522 instance

String UIDCard;
const String validUIDs[] = {"B3492334", "23542D14"}; // Replace with your valid UIDs

void setup() {
  Serial.begin(9600);
  
  SPI.begin();          // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522 card
  
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("Tempelkan RFID");

  Serial.println("Setup complete. Ready to scan.");
}

void loop() {
  // Check if a new card is present
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Read UID
  UIDCard = "";
  Serial.println("Scanned PICC's UID:");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    UIDCard += String(mfrc522.uid.uidByte[i], HEX);
  }
  UIDCard.toUpperCase(); // Capitalize
  Serial.print("UID:");
  Serial.println(UIDCard);
  Serial.println("**End Reading**");

  // Check if UID is valid
  bool isValid = false;
  for (int i = 0; i < sizeof(validUIDs) / sizeof(validUIDs[0]); i++) {
    if (UIDCard == validUIDs[i]) {
      isValid = true;
      break;
    }
  }

  // Display result on LCD
  lcd.clear();
  if (isValid) {
    lcd.setCursor(0, 0);
    lcd.print("Akses Diizinkan");
    lcd.setCursor(0, 1);
    lcd.print("Locker Terbuka");
    
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
    delay(200);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);

    // Open solenoid doorlock
    Serial.println("Access granted. Unlocking solenoid...");
    digitalWrite(RELAY_PIN, LOW); // Unlock solenoid
    delay(3000); // Keep the door unlocked for 3 seconds
    digitalWrite(RELAY_PIN, HIGH); // Lock solenoid again
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Locker Terkunci");
    Serial.println("Solenoid locked again.");
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Akses Ditolak");
    lcd.setCursor(0, 1);
    lcd.print("Locker Terkunci");
    Serial.println("Access denied.");
    
    digitalWrite(BUZZER_PIN, HIGH);
    delay(1000);
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(1000); // Small delay to ensure the message is displayed

  // Display "Tempelkan RFID" again
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Tempelkan RFID");

  mfrc522.PICC_HaltA(); // Stop reading
  mfrc522.PCD_StopCrypto1(); // Stop encryption on PCD

  Serial.println("Ready for next scan.");
}
