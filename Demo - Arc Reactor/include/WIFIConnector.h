
// Connection using WPA2 Enterpriser WIFI network


#include <WiFiNINA.h>
#include <SPI.h>
//#include <ArduinoOTA.h>

#include "wifiStatus.h"

//please enter your sensitive data for log on

//char ssid[] = "MiFi7000-ED1C";  // your WPA2 enterprise network SSID (name)
//char pass[] = "a63cc8aa";  // your WPA2 enterprise password

//char ssid[] = "Fusion";  // your WPA2 enterprise network SSID (name)
//char pass[] = "obbb1753";  // your WPA2 enterprise password

//char ssid[] ="IDO-OBJECTS";  // your WPA2 enterprise network SSID (name)
//char pass[] = "42Bidules!";  // your WPA2 enterprise password

//char ssid[] ="IOT_OBJECTS";  // your WPA2 enterprise network SSID (name)
//char pass[] = "42Bidules!";  // your WPA2 enterprise password

char ssid[] ="IDO";  // your WPA2 enterprise network SSID (name)
char pass[] = "99Bidules!";  // your WPA2 enterprise password


//char ssid[] = "CCNB-IOT-WRLS";  // your WPA2 enterprise network SSID (name)
//char user[] = "ba-ido-01";  // your WPA2 enterprise username
//char pass[] = "iotwifi2020";  // your WPA2 enterprise password

int status = WL_IDLE_STATUS;     // the Wifi radio's status

//

WiFiClient wifiClient; 

void wifiConnect()
{
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA2 enterprise network:
    // - You can optionally provide additional identity and CA cert (string) parameters:
    //      WiFi.beginEnterprise(ssid, user, pass, identity, caCert)
    // . if your network requires them.
    status = WiFi.begin(ssid, pass);
    //status = WiFi.beginEnterprise(ssid, user, pass);
    Serial.println(status);
    Serial.println(WiFi.reasonCode());
    // start the WiFi OTA library with internal (flash) based storage
   

    // wait 10 seconds for connection:
    delay(10000);
  }

  //ArduinoOTA.begin(WiFi.localIP(), "Arduino", "password", InternalStorage);
  // you're connected now, so print out the data:
  Serial.print("You're connected to the network");
  printCurrentNet();
  printWifiData();

}
