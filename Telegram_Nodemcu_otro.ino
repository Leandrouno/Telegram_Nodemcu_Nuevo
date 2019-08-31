//https://github.com/shurillu/CTBot/blob/master/examples/inlineKeyboard/inlineKeyboard.ino

/* Inicializamos la conexion WIFI con el Router
char ssid[] = "Quien es Mi Idolo ?";     // el nombre de tu Red
char password[] = "LioMessi"; // la clave de tu Red
const char id_chat [] ="590173240";
566903986:AAEs-5oiAimxg5HJXgbV_WuJjSoTXmTzLtM
*/
#include "CTBot.h"

#define PUERTA1_CALLBACK "Puerta1"  
#define PUERTA2_CALLBACK "Puerta2" 
#define PORTON_CALLBACK "Porton" 

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

  // connect the ESP8266 to the desired access point
  myBot.wifiConnect(ssid, pass);

  // set the telegram bot token
  myBot.setTelegramToken(token);

  // check if all things are ok
  if (myBot.testConnection()){
    Serial.println("Conectado a la Red Wifi");}
  else{
    Serial.println("Error al Conectar a la Red");}

 

  // add a query button to the first row of the inline keyboard
  myKbd.addButton("Puerta 1", PUERTA1_CALLBACK, CTBotKeyboardButtonQuery);
  // add another query button to the first row of the inline keyboard
  myKbd.addButton("Puerta 2", PUERTA2_CALLBACK, CTBotKeyboardButtonQuery);
  // add a new empty button row
  myKbd.addRow();
  // add a URL button to the second row of the inline keyboard
  myKbd.addButton("Porton", PORTON_CALLBACK, CTBotKeyboardButtonQuery);
}

void loop() {
  // a variable to store telegram message data
  TBMessage msg;

  // if there is an incoming message...
  if (myBot.getNewMessage(msg)) {
    
      if (msg.messageType == CTBotMessageText) {
        
          if (msg.text.equalsIgnoreCase("Teclado")) {        
                          
                                myBot.sendMessage(msg.sender.id, "Teclado", myKbd);
                                                         
                                 }
          if (msg.text.equalsIgnoreCase("Puerta1")) {        
                          
                                digitalWrite(PUERTA1, LOW);
                                delay(500);
                                digitalWrite(PUERTA1, HIGH);
                                Serial.println("Puerta Negra");
                                Serial.println();
                                myBot.endQuery(msg.callbackQueryID, "Puerta Negra Abierta", true);
                                                         
                                 } 
          if (msg.text.equalsIgnoreCase("Puerta2")) {        
                          
                                digitalWrite(PUERTA2, LOW);
                                delay(500);
                                digitalWrite(PUERTA2, HIGH);
                                Serial.println("Puerta Blanca");
                                Serial.println();
                                myBot.endQuery(msg.callbackQueryID, "Puerta Blanca Abierta", true);
                                                         
                                 }
          if (msg.text.equalsIgnoreCase("Porton")) {        
                          
                                digitalWrite(PORTON, LOW);
                                delay(500);
                                digitalWrite(PORTON, HIGH);
                                Serial.println("Porton");
                                Serial.println();
                                myBot.endQuery(msg.callbackQueryID, "Porton Accionado", true);
                                                         
                                 }                     
    
        
        
        
            } 
  
  
  else if (msg.messageType == CTBotMessageQuery) {
      

      if (msg.callbackQueryData.equals(PUERTA1_CALLBACK)) {

                                digitalWrite(PUERTA1, LOW);
                                delay(500);
                                digitalWrite(PUERTA1, HIGH);
                                Serial.println("Puerta Negra");
                                Serial.println();
                                myBot.endQuery(msg.callbackQueryID, "Puerta Negra Abierta", true);
                
                }
                
    if (msg.callbackQueryData.equals(PUERTA2_CALLBACK)) {

                                digitalWrite(PUERTA2, LOW);
                                delay(500);
                                digitalWrite(PUERTA2, HIGH);
                                Serial.println("Puerta Blanca");
                                Serial.println();
                                myBot.endQuery(msg.callbackQueryID, "Puerta Blanca Abierta", true);
                
                }             
   if (msg.callbackQueryData.equals(PORTON_CALLBACK)) {

                                digitalWrite(PORTON, LOW);
                                delay(500);
                                digitalWrite(PORTON, HIGH);
                                Serial.println("Porton Accionado");
                                Serial.println();
                                myBot.endQuery(msg.callbackQueryID, "Porton Accionado", true);
                
                }
    
    
    }
  }
  // wait 500 milliseconds
  delay(500);
}
