#include <Arduino.h>
#include <Adafruit_AHTX0.h>
//Librairire de branchement WIFI et MQTT
#include "WIFI_NINA_Connector.h"
#include "MQTTConnector.h"
unsigned long reconnected =0;
unsigned long LastMillis=0;
unsigned long PresentMillis =0;

const uint32_t delayMS = 5000;

Adafruit_AHTX0 aht;



/*
 * The setup function. We only start the sensors here
 */
void setup(void)
{

  Serial.begin(9600);

  wifiConnect();                            //  Branchement au réseau WIFI
  MQTTConnect();                            //  Branchement au broker MQTT

   aht.begin();                             // Mise en marche du AHT20

}

/*
 * Main function, get and show the temperature
 */
void loop(void)
{ 

  if(ClientWIFI.connected() && ClientMQTT.connected())
  {
      ClientMQTT.loop(); 
  //    Code goes here...
  

    PresentMillis=millis();
    
    if(PresentMillis-LastMillis > delayMS)
    {
      
     
      sensors_event_t humidity, temp;
      aht.getEvent(&humidity, &temp);
      

      appendPayload("Reconnected", reconnected);
      appendPayload("Temperature", temp.temperature);
      appendPayload("Humidité", humidity.relative_humidity);
      sendPayload();
      LastMillis=PresentMillis;
    }

   
  }
  else //Si et seulement si ClientWIFI.connected() == False ou ClientMQTT.connected() == False
  {

    status=WL_IDLE_STATUS;
    WiFi.end();
    wifiConnect();
    MQTTConnect();
    reconnected++;  //  Incrémente la valeur
  }
  
}