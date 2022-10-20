#include <Arduino.h>

/* SPIFFSUsage.ino
 * 
 * This sketch demonstrates various file operations utilizing
 * the Arduino MKR MEM shield port for the SPIFFS.
 * 
 * Alexander Entinger
 */

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <Arduino_MKRMEM.h>
#include <stdio.h>
#include <Adafruit_AHTX0.h>

#include "RTClib.h"

RTC_DS3231 rtc;
Adafruit_AHTX0 aht;

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

/* A pangram is a sentence using every letter of a given alphabet at least once. */
static char const PANGRAM[] = "The quick brown fox jumps over the lazy dog.\n";

/**************************************************************************************
 * SETUP/LOOP
 **************************************************************************************/
bool StopWriting = false;

void writeToFile(char CharToWrite[])
{


  Serial.println("Writing ...");
    File file = filesystem.open("fox.txt", CREATE | READ_WRITE| APPEND);

  int const bytes_to_write = strlen(CharToWrite);
      int const bytes_written = file.write((void *)CharToWrite, bytes_to_write);
      
      if(bytes_written != bytes_to_write) {
        Serial.println("write() failed with error code "); Serial.println(filesystem.err()); return;
      } else {
        Serial.print(bytes_written);
        Serial.println(" bytes written");
      }


      Serial.println("Retrieving filesystem info ...");
      unsigned int bytes_total = 0,
                  bytes_used = 0;
      if(SPIFFS_OK != filesystem.info(bytes_total, bytes_used)) {
        Serial.println("check() failed with error code "); Serial.println(filesystem.err()); return;
      } else {
        char msg[64] = {0};
        snprintf(msg, sizeof(msg), "SPIFFS Info:\nBytes Total: %d\nBytes Used:  %d", bytes_total, bytes_used);
        Serial.println(msg);
      }


      Serial.println("Reading ...");
      file.lseek(0, START); /* Rewind file pointer to the start */

      char buf[10000] = {0};
      int const bytes_read = file.read(buf, sizeof(buf));
      buf[bytes_read] = '\0';
      
      Serial.print("["); Serial.print(bytes_read); Serial.print("] ");
      Serial.println(buf);

    file.close();
}

void formatFlash()
{
  Serial.println("Erasing chip ...");
  flash.eraseChip();

  Serial.println("Mounting ...");
  int res = filesystem.mount();
  if(res != SPIFFS_OK && res != SPIFFS_ERR_NOT_A_FS) {
    Serial.println("mount() failed with error code "); Serial.println(res); return;
  }

  Serial.println("Unmounting ...");
  filesystem.unmount();

  Serial.println("Formatting ...");
  res = filesystem.format();
  if(res != SPIFFS_OK) {
    Serial.println("format() failed with error code "); Serial.println(res); return;
  }

  Serial.println("Mounting ...");
  res = filesystem.mount();
  if(res != SPIFFS_OK) {
    Serial.println("mount() failed with error code "); Serial.println(res); return;
  }

  Serial.println("Checking ...");
  res = filesystem.check();
  if(res != SPIFFS_OK) {
    Serial.println("check() failed with error code "); Serial.println(res); return;
  }

  Serial.println("Retrieving filesystem info ...");
  unsigned int bytes_total = 0,
               bytes_used  = 0;
  res = filesystem.info(bytes_total, bytes_used);
  if(res != SPIFFS_OK) {
    Serial.println("check() failed with error code "); Serial.println(res); return;
  } else {
    char msg[64] = {0};
    snprintf(msg, sizeof(msg), "SPIFFS Info:\nBytes Total: %d\nBytes Used:  %d", bytes_total, bytes_used);
    Serial.println(msg);
  }

  Serial.println("Unmounting ...");
  filesystem.unmount();
}

void setup() {
  Serial.begin(9600);
  rtc.begin();
  aht.begin();

  unsigned long const start = millis();
  for(unsigned long now = millis(); !Serial && ((now - start) < 5000); now = millis()) { };
  
  flash.begin();

  formatFlash();

  Serial.println("Mounting ...");
  if(SPIFFS_OK != filesystem.mount()) {
    Serial.println("mount() failed with error code "); Serial.println(filesystem.err()); return;
  }


  Serial.println("Checking ...");
  if(SPIFFS_OK != filesystem.check()) {
    Serial.println("check() failed with error code "); Serial.println(filesystem.err()); return;
  }


  
}

void loop() {


if (!StopWriting)
{
    
    for(int i=0; i<10;i++ && !StopWriting)
    {
     
      
    
      char StringToWrite[40]; 
      char tempString[10];
      char humString[10];
     
      sensors_event_t humidity, temp;
      aht.getEvent(&humidity, &temp);
      sprintf(tempString,"%f",temp.temperature);
      sprintf(humString,"%f",humidity.relative_humidity);
      
      DateTime now = rtc.now(); 
      //Updated now.day to now.date
      sprintf(StringToWrite, "%02d:%02d:%02d %02d/%02d/%02d",  now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year()); 
      
      strncat(StringToWrite," ",1);
      strncat(StringToWrite,tempString,10);
      strncat(StringToWrite," ",1);
      strncat(StringToWrite,humString,10);
      strncat(StringToWrite,"\n",1);
      writeToFile(StringToWrite);
      delay(1000);

      if( i==9)
      {
        StopWriting=true;
      }

  }

     
  Serial.println("Unmounting ...");
  filesystem.unmount();


  }

  


}