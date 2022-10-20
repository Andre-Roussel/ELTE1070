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