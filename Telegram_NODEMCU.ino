//https://github.com/shurillu/CTBot/blob/master/examples/inlineKeyboard/inlineKeyboard.ino

#include "CTBot.h"

#define PUERTA1_CALLBACK "Puerta1"  
#define PUERTA2_CALLBACK "Puerta2" 
#define PORTON_CALLBACK "Porton" 
#define ESTADO_CALLBACK "Estado" 

#define LED_BUILTIN D1
#define PUERTA2     D2
#define PUERTA1     D5
#define PORTON      D7

CTBot myBot;
CTBotInlineKeyboard myKbd;  

String ssid = "";   
String pass = ""; 
String token = "";  


void setup() {

  Serial.begin(9600);
  Serial.println("Iniciando TelegramBot...");
  
  pinMode(LED_BUILTIN, OUTPUT);
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
    digitalWrite(LED_BUILTIN, HIGH);}
  else{
    Serial.println("Error al Conectar a la Red");
    digitalWrite(LED_BUILTIN, LOW);}

 
  myKbd.addButton("Puerta 1", PUERTA1_CALLBACK, CTBotKeyboardButtonQuery);

  myKbd.addButton("Puerta 2", PUERTA2_CALLBACK, CTBotKeyboardButtonQuery);

  myKbd.addRow();

  myKbd.addButton("Porton", PORTON_CALLBACK, CTBotKeyboardButtonQuery);

  myKbd.addRow();

  myKbd.addButton("Estado", ESTADO_CALLBACK, CTBotKeyboardButtonQuery);
}

void loop() {
  
  TBMessage msg;

  
  if (myBot.testConnection()){
	  
    digitalWrite(LED_BUILTIN, HIGH);
	
	} else{
		
    Serial.println("Error al Conectar a la Red");	
    digitalWrite(LED_BUILTIN, LOW);	
	myBot.wifiConnect(ssid, pass);	
    myBot.setTelegramToken(token);
	
	}

 
  if (myBot.getNewMessage(msg)) {
    
      if (msg.messageType == CTBotMessageText) {
        
          if (msg.text.equalsIgnoreCase("Teclado")) {        
                          
                                myBot.sendMessage(msg.sender.id, "Teclado", myKbd);
                                                         
                                 }
          if (msg.text.equalsIgnoreCase("Puerta1")) {        
                          
                                digitalWrite(PUERTA1, LOW);
                                delay(500);
                                digitalWrite(PUERTA1, HIGH);
                myBot.sendMessage(msg.sender.id, "Puerta Negra Abierta");
                                                         
                                 } 
          if (msg.text.equalsIgnoreCase("Puerta2")) {        
                          
                                digitalWrite(PUERTA2, LOW);
                                delay(500);
                                digitalWrite(PUERTA2, HIGH);
                                myBot.sendMessage(msg.sender.id, "Puerta Blanca Abierta");
                                                         
                                 }
          if (msg.text.equalsIgnoreCase("Porton")) {        
                          
                                digitalWrite(PORTON, LOW);
                                delay(500);
                                digitalWrite(PORTON, HIGH);
                                myBot.sendMessage(msg.sender.id, "Porton Accionado");
                                                         
                                 }    

          if (msg.text.equalsIgnoreCase("Estado")) {        
                          
                                myBot.sendMessage(msg.sender.id, "Estado OK !");
                                                         
                                 } 								 
    
        
        
        
            } 
  
  
  else if (msg.messageType == CTBotMessageQuery) {
      

      if (msg.callbackQueryData.equals(PUERTA1_CALLBACK)) {

                                digitalWrite(PUERTA1, LOW);
                                delay(500);
                                digitalWrite(PUERTA1, HIGH);
                                myBot.endQuery(msg.callbackQueryID, "Puerta Negra Abierta", true);
                
                }
                
    if (msg.callbackQueryData.equals(PUERTA2_CALLBACK)) {

                                digitalWrite(PUERTA2, LOW);
                                delay(500);
                                digitalWrite(PUERTA2, HIGH);
                                myBot.endQuery(msg.callbackQueryID, "Puerta Blanca Abierta", true);
                
                }    
				
   if (msg.callbackQueryData.equals(PORTON_CALLBACK)) {

                                digitalWrite(PORTON, LOW);
                                delay(500);
                                digitalWrite(PORTON, HIGH);
                                myBot.endQuery(msg.callbackQueryID, "Porton Accionado", true);
                
                }
				
   if (msg.callbackQueryData.equals(ESTADO_CALLBACK)) {

                                myBot.endQuery(msg.callbackQueryID, "Estado OK !", true);
                
                }				
    
    
    }
  }
 
  delay(500);
}