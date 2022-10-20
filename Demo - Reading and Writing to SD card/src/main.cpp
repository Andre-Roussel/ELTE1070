#include <Arduino.h>
#include "WIFI_NINA_Connector.h"
#include "MQTTConnector.h"
#include "ArduinoLowPower.h"


#include <SPI.h>
#include <SD.h>

#include <Adafruit_AHTX0.h>

#include "RTClib.h"


RTC_DS3231 rtc;
Adafruit_AHTX0 aht;

const int chipSelect = 4;

boolean runEveryShort(unsigned long interval)
{
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    return true;
  }
  return false;
}

boolean runEveryLong(unsigned long interval)
{
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    return true;
  }
  return false;
}

String BuildMQTTString(DateTime myTimeStamp, float Temperature, float Humidity)
{


    char TimeStampString[25] ="";

    //Updated now.day to now.date
    sprintf(TimeStampString, "D%02d%02d%02dT%02d%02d%02d",  myTimeStamp.year(), myTimeStamp.month(), myTimeStamp.day(), myTimeStamp.hour(), myTimeStamp.minute(), myTimeStamp.second()); 

    // make a string for assembling the data to log:
    String tempString = "{\"";

   
  
    char tempValue[10] ="";
    char humValue[10] = "";

    sprintf(tempValue,"%f",Temperature);
    sprintf(humValue,"%f",Humidity);
    tempString += "ObjectUnixTime";
    tempString += "\":";
    tempString += rtc.now().unixtime()+10800;
    tempString += ",\"";
    tempString += "MCT";
    tempString += "\":";
    tempString += tempValue ;
    tempString += ",";
    tempString += "\"";
    tempString += "MCH";
    tempString += "\":";
    tempString += humValue ;
    tempString += "}";
    


  return tempString;
}

void WriteStringToFile(String dataString)
{
// open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    
    File dataFile = SD.open("datalog.txt", FILE_WRITE);

    // if the file is available, write to it:
 
    if (dataFile) {
      dataFile.println(dataString);
      dataFile.close();     
    }


}

void removeFile(String fileName)
{
  if( SD.remove(fileName))
  {
    Serial.println("File datalog.txt removed");
  }

}

void sendMQTTData(String dataFile)
{
    File myFile = SD.open(dataFile,FILE_READ);
    digitalWrite(LED_BUILTIN,HIGH);
    wifiConnect();
    MQTTConnect();

    if(myFile)
    {
      String myString = myFile.readString();
      int stringLength = myString.length();
      char dataString[stringLength];
      myString.toCharArray(dataString, stringLength);
      int count =0;
      
      
      char * token = strtok(dataString, "\n");
      // loop through the string to extract all other tokens
      while( token != NULL ) {
        //String dummyString =  token; //printing each token
        Serial.println(count++);
        String dummyString = token;
        sendMQTTStringAsPayload(dummyString);
        Serial.println(dummyString);
        token = strtok(NULL, "\n");
      }


      Serial.println("end");




      myFile.close();

      removeFile("datalog.txt");
      status=WL_IDLE_STATUS;
  
      WiFi.disconnect();
      WiFi.end();
      digitalWrite(LED_BUILTIN,LOW);
    }


}

void setup() 
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  
  
  rtc.begin();
  aht.begin();

  

  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) 
  {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");


  removeFile("datalog.txt");

  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,LOW);
  
  
}

void loop() 
{


    if( runEveryShort(5000) )
    {
      sensors_event_t humidity, temp;
      aht.getEvent(&humidity, &temp);

      String mqttString = BuildMQTTString(rtc.now(), temp.temperature, humidity.relative_humidity);

      WriteStringToFile(mqttString);
     

    }

    if (runEveryLong(30000))
    {
      sendMQTTData("datalog.txt");      
    }
    
}
  
