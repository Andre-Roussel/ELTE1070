 #include <MQTT.h>

//const char mqttServer[] = "198.164.130.74"; // IP adress of IDO ThingsBoard Server (Broker) in the classroom
const char mqttServer[] = "192.168.1.99";
const int mqttServerPort = 1883; // broker mqtt port

const char key[] = "6IVjtvUSYTiZy6KA1uOF"; // broker access token
const char secret[] = ""; // broker secret
const char device[] = "15d3c5d0-440c-11ed-9169-1b4f89b20433"; // broker device identifier

//Modify this section to reflect the number of telemetry keys your are using

//NumberOfTelemetryKeys is the number of values that are sent via MQTT to the broker
//MaxLenghtTelemetryKeyName is the maximum lenght of the key name

const int NumberOfTelemetryKeys = 1;
const int MaxLenghtTelemetryKeyName = 50;


// Array to hold the values (take a look in the loop function

float KeyValue[NumberOfTelemetryKeys];


// Define your key names here
char  TelemetryKey[NumberOfTelemetryKeys][MaxLenghtTelemetryKeyName]={
  "Led ON/OFF"
  
};

MQTTClient mqqtClient;  // Create a MQTT client to handle messagin between object and broker


void messageReceived(String &topic, String &payload) {

  int tempDelay;
 
  Serial.println(payload);
  Serial.println(payload.substring(30,payload.length() -1));
  tempDelay = payload.substring(30,payload.length() -1).toInt();
  Serial.println(tempDelay);
  ledDelay = -tempDelay + 1000;
  
  Serial.println("Message received");
  Serial.print("Led delay is : ");
  Serial.println(ledDelay);
}


void MQTTConnect() {
  
  mqqtClient.begin(mqttServer, mqttServerPort, wifiClient);
  Serial.print("Connecting to broker...");
  mqqtClient.onMessage(messageReceived);
  while (!mqqtClient.connect(device, key, secret)) {
    Serial.print(".");
    delay(1000);
  }
  mqqtClient.subscribe("v1/devices/me/rpc/request/+");
  Serial.println("\nConnected to MQTT!\n");

}

void SendPayload(char TelemetryKey[NumberOfTelemetryKeys][MaxLenghtTelemetryKeyName],float KeyValue[NumberOfTelemetryKeys])
{

char attributes[200];

String payload = "{";
  for (int i=0; i < NumberOfTelemetryKeys; i++)
  {
    payload += "\"" + String(TelemetryKey[i]) + "\":";
    payload += String(KeyValue[i]);

    if(i != NumberOfTelemetryKeys-1)
    {
      payload +=",";
    }
   
  }

payload += "}";

  payload.toCharArray(attributes, 200);
  mqqtClient.publish("v1/devices/me/telemetry", attributes);
  Serial.println(attributes);

}
