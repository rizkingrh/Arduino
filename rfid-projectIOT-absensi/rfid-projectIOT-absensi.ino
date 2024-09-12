#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SPI.h>
#include <MFRC522.h>

const char* ssid = "Redmi";    //Your Wifi SSID
const char* password = "87654321";   //Wifi Password
const char* host= "192.168.182.1";  //your server address or computer IP

#define RST_PIN         16   //pin-D0
#define SDA_PIN          0    //pin-D3
MFRC522 mfrc522(SDA_PIN, RST_PIN);   // Create MFRC522 instance

int buzzer = 15;
String UIDCard;

void setup() {
  Serial.begin(9600);

  //setting wifi
  WiFi.hostname("NodeMCU");
  WiFi.begin(ssid, password);

  //cek koneksi wifi
  while(WiFi.status() != WL_CONNECTED) {
    //status search wifi
    delay(500);
    Serial.println(".");
  }

  Serial.println("WiFi Connected");
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());

  pinMode(buzzer, OUTPUT);

  SPI.begin();    // Init SPI bus
  mfrc522.PCD_Init();  // Init MFRC522 card
  Serial.println("Read Uid data on a MIFARE PICC:");   //shows in serial that it is ready to read                        // Show details of PCD - MFRC522 Card Reader details
}

void loop() {
  
  // Getting ready for Reading PICCs
  if ( ! mfrc522.PICC_IsNewCardPresent()) { 
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {   
    return;
  }

  UIDCard ="";
  Serial.println("Scanned PICC's UID:");
   
  for ( byte i = 0; i < mfrc522.uid.size; i++) {  
    UIDCard += String(mfrc522.uid.uidByte[i], HEX);
  }
  
  UIDCard.toUpperCase(); //Capital
  Serial.print("UID:");
  Serial.println(UIDCard);
  Serial.println("**End Reading**");

  digitalWrite(buzzer, HIGH);delay(200);
  digitalWrite(buzzer, LOW);delay(200);
  digitalWrite(buzzer, HIGH);delay(200);
  digitalWrite(buzzer, LOW);

  //connect to server
  WiFiClient client;
  const int httpPort = 80;
  if(!client.connect(host, httpPort)) {
    Serial.println("Connection Failed");
    return;
  }

  //send UID to database
  String Link;
  HTTPClient http;
  WiFiClient wifiClient;
  Link = "http://"+String(host)+"/project-iot/apps/senduid.php?uid=" + UIDCard;
  http.begin(wifiClient, Link);
  http.GET();
  //read status response
  String responseSend = http.getString();
  Serial.println(responseSend);
  http.end();

  //set control response
  if(responseSend == "Berhasil") {
    delay(2000);
    digitalWrite(buzzer, HIGH);delay(1000);
    digitalWrite(buzzer, LOW);
    Serial.println("Control Berhasil");
  } else {
    Serial.println("Control Gagal");
  }

  delay(2000);
  
  mfrc522.PICC_HaltA(); // Stop reading
  return;
}