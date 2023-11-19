#include "CTBot.h"
CTBot myBot;

String ssid = "";
String pass = "";
String token = "";
const int id = ;
String pesan = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Starting telegram bot...");

  myBot.wifiConnect(ssid, pass);
  myBot.setTelegramToken(token);

  if (myBot.testConnection()){
    Serial.println("Connection Success...");
  } else {
    Serial.println("Connection Failed...");
  }
}

void loop() {
  //put your main code here, to run repeatedly:

  // Eror gara2 getNewMessage
  TBMessage msg;
  // if(myBot.getNewMessage(msg)){
  //   Serial.println("Message Send : " + msg.text);
  // }

  // if (CTBotMessageText == myBot.getNewMessage(msg)){ 
  //   Serial.print("Pesan Masuk: "); 
  //   Serial.println(msg.text); 
  //   pesan = msg.text;
  // }

  //Ini udah bisa ngirim data
  myBot.sendMessage(id, "Hallo...");
  delay(5000);
}