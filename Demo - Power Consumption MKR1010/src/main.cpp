#include <Arduino.h>
//Librairire de branchement WIFI et MQTT
#include "WIFI_NINA_Connector.h"
#include "MQTTConnector.h"

void setup(void)
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,LOW);
}

void loop(void)
{ 

  //Branchement WIFI
  Serial.println("Connecting");
  digitalWrite(LED_BUILTIN,HIGH);
//  wifiConnect();                            //  Branchement au réseau WIFI
//  MQTTConnect();
  delay(20000);       //Observation de connection multiple

//  status=WL_IDLE_STATUS;
  
//  WiFi.disconnect();
//  WiFi.end();
  Serial.println("Disconnected");
  digitalWrite(LED_BUILTIN,LOW);
  delay(5000);
  
}