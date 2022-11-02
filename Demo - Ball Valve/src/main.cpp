#include <Arduino.h>
//Librairire de branchement WIFI et MQTT
#include "WIFI_NINA_Connector.h"
#include "MQTTConnector.h"
unsigned long reconnected =0;


const int relayPin = 2;
const int sensorPin = A6;
const int moistureSetPoint = 400;

/*
 * The setup function. We only start the sensors here
 */
void setup(void)
{

  Serial.begin(9600);

  //wifiConnect();                            //  Branchement au réseau WIFI
  //MQTTConnect();                            //  Branchement au broker MQTT

  pinMode(relayPin,OUTPUT);
  pinMode(sensorPin,INPUT);

  

}

/*
 * Main function, get and show the temperature
 */
void loop(void)
{ 

Serial.println(analogRead(sensorPin));
if(analogRead(sensorPin) <= moistureSetPoint )
{
  digitalWrite(relayPin,HIGH);
}
else
{
  digitalWrite(relayPin,LOW);
}

/*
  if(ClientWIFI.connected() && ClientMQTT.connected())
  {
      ClientMQTT.loop(); 
  
  //  Code goes here...
  
  
  
  }
  else //Si et seulement si ClientWIFI.connected() == False ou ClientMQTT.connected() == False
  {

    status=WL_IDLE_STATUS;
    WiFi.end();
    wifiConnect();
    MQTTConnect();
    reconnected++;  //  Incrémente la valeur
  }

  */
}