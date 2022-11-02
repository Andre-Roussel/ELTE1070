#include <Arduino.h>
#include <ThingsBoard.h>



#include "WIFI_NINA_Connector.h"
#include "MQTTConnector.h"

int delayTimer = 1000;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT); 

  wifiConnect();
  MQTTConnect();

  // start the WiFi OTA library with internal (flash) based storage
 


}

void loop() {
  // put your main code here, to run repeatedly:
  
  ArduinoOTA.poll();

  digitalWrite(LED_BUILTIN, HIGH);
  delay(delayTimer);

  digitalWrite(LED_BUILTIN, LOW);
  delay(delayTimer);

}