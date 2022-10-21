
/*
  Titre      : DEMO - Rule Chain pour RPC
  Auteur     : André Roussel
  Date       : 21/10/2022
  Description: Démonstration de l'utilisation d'un rule chain pour RPC a un uC
  Droits     : Reproduction permise pour usage pédagogique
  Version    : 0.0.1
*/


#include <Arduino.h>

bool LedStatus = false;
int Intensite =0;
#include "WIFI_NINA_Connector.h"
#include "MQTTConnector.h"
const int LED_PIN =2;
int temperature = 20;

void setup() {
  // put your setup code here, to run once:
  wifiConnect();                            //  Branchement au réseau WIFI
  MQTTConnect(); 

  pinMode(LED_PIN,OUTPUT); 

}

void loop() {
  // put your main code here, to run repeatedly:
  ClientMQTT.loop(); 
  
  
  if (LedStatus)
  {
    digitalWrite(LED_PIN,HIGH);
   
  }
  else
  {
    digitalWrite(LED_PIN, LOW);
  }
  

  
  
  if(temperature == 20)
  {
    temperature = 25;
    appendPayload("temperature", temperature);
    sendPayload();
    Serial.println(temperature);
  }
  else
  {
    temperature =20;
    appendPayload("temperature", temperature);
    sendPayload();
    Serial.println(temperature);
  }

  delay(5000);

  
}