#include "CTBot.h"

#define PUERTA1_CALLBACK "Puerta1"
#define PUERTA2_CALLBACK "Puerta2"
#define PORTON_CALLBACK "Porton"
#define ESTADO_CALLBACK "Estado"

#define LED D1
#define PUERTA2 D2
#define PUERTA1 D5
#define PORTON D7

CTBot myBot;
CTBotReplyKeyboard myKbd;
bool isKeyboardActive;

String ssid = "";
String pass = "";
String token = "";
long id = ;// id sin comillas

void setup(){

  Serial.begin(9600);
  Serial.println("Iniciando TelegramBot...");

  pinMode(LED, OUTPUT);
  pinMode(PUERTA1, OUTPUT);
  pinMode(PUERTA2, OUTPUT);
  pinMode(PORTON, OUTPUT);

  digitalWrite(PUERTA1, HIGH);
  digitalWrite(PUERTA2, HIGH);
  digitalWrite(PORTON, HIGH);

  myBot.wifiConnect(ssid, pass);

  myBot.setTelegramToken(token);

  if (myBot.testConnection()){
    Serial.println("Conectado a la Red Wifi");
    digitalWrite(LED, HIGH);
  }
  else
  {
    Serial.println("Error al Conectar a la Red");
    digitalWrite(LED, LOW);
  }
  
 myKbd.addButton("Puerta1");
 myKbd.addButton("Puerta2");
    myKbd.addRow();
 myKbd.addButton("Porton");
    myKbd.addRow();
 myKbd.addButton("Estado");
 myKbd.addButton("EstadoPorton");
 myKbd.addButton("EstadoTimbre");
 myKbd.enableResize();
 isKeyboardActive = true;
}

void loop(){

  TBMessage msg;

  if (myBot.getNewMessage(msg)){

    if(msg.sender.id == id){

    if (msg.messageType == CTBotMessageText){

      if (msg.text.equalsIgnoreCase("Teclado")){
        myBot.sendMessage(msg.sender.id, "Teclado", myKbd);
        isKeyboardActive = true;
      }

      if (msg.text.equalsIgnoreCase("Puerta1")){
        digitalWrite(PUERTA1, LOW);
        delay(500);
        digitalWrite(PUERTA1, HIGH);
        myBot.sendMessage(msg.sender.id, "Puerta Negra Abierta");
      }
      
      if (msg.text.equalsIgnoreCase("Puerta2")){
        digitalWrite(PUERTA2, LOW);
        delay(500);
        digitalWrite(PUERTA2, HIGH);
        myBot.sendMessage(msg.sender.id, "Puerta Blanca Abierta");
      }

      if (msg.text.equalsIgnoreCase("Porton")){
        digitalWrite(PORTON, LOW);
        delay(500);
        digitalWrite(PORTON, HIGH);
        myBot.sendMessage(msg.sender.id, "Porton Accionado");
      }

      if (msg.text.equalsIgnoreCase("Estado")){
        myBot.sendMessage(msg.sender.id, "Very Good MONOO !");
      }

    } else if (msg.messageType == CTBotMessageQuery){

      if (msg.callbackQueryData.equals(PUERTA1_CALLBACK)){
        digitalWrite(PUERTA1, LOW);
        delay(500);
        digitalWrite(PUERTA1, HIGH);
        myBot.endQuery(msg.callbackQueryID, "Puerta Negra Abierta", true);
      }

      if (msg.callbackQueryData.equals(PUERTA2_CALLBACK)){
        digitalWrite(PUERTA2, LOW);
        delay(500);
        digitalWrite(PUERTA2, HIGH);
        myBot.endQuery(msg.callbackQueryID, "Puerta Blanca Abierta", true);
      }

      if (msg.callbackQueryData.equals(PORTON_CALLBACK)){
        digitalWrite(PORTON, LOW);
        delay(500);
        digitalWrite(PORTON, HIGH);
        myBot.endQuery(msg.callbackQueryID, "Porton Accionado", true);
      }

      if (msg.callbackQueryData.equals(ESTADO_CALLBACK)){
        myBot.endQuery(msg.callbackQueryID, "Very Good MONOO !", true);
      }
      
    }

  } else{myBot.sendMessage(msg.sender.id, "JUIRAAAA !!");}

  }

  delay(500);
}
