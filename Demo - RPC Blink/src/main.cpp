/*
  Titre      : DEMO - RPC Blink
  Auteur     : André Roussel
  Date       : 20/10/2022
  Description: Démonstration de l'abonement a un message MQTT (RPC) et son affichage dans le moniteur série
  Droits     : Reproduction permise pour usage pédagogique
  Version    : 0.0.1
*/



#include <Arduino.h>
#include "WIFI_NINA_Connector.h"
#include "MQTTConnector.h"

void setup() {
  // put your setup code here, to run once:
  wifiConnect();                            //  Branchement au réseau WIFI
  MQTTConnect();  

}

void loop() {
  // put your main code here, to run repeatedly:
  ClientMQTT.loop(); 
}