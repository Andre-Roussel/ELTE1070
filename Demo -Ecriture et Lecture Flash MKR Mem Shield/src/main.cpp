#include <Arduino.h>


#include <Arduino_MKRMEM.h>
/* ... */
static char const PANGRAM[] = "Portez ce vieux whisky au juge blond qui fume";
/* ... */
void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
    /* code */
  }
  
  flash.begin();
  /* ... */
  if(SPIFFS_OK != filesystem.mount()) {
    Serial.println("mount() failed with error code "); Serial.println(filesystem.err()); return;
  }
  /* ... */
  File file = filesystem.open("fox.txt", CREATE | READ_WRITE| TRUNCATE);
  /* ... */
  file.write((void *)PANGRAM, strlen(PANGRAM));
  /* ... */
  file.lseek(0, START); /* Rewind file pointer to the start */
  char buf[64] = {0};
  int const bytes_read = file.read(buf, sizeof(buf));
  buf[bytes_read] = '\0';
  Serial.println(buf);
  /* ... */
  file.close();
  filesystem.unmount();
}

void loop()
{}