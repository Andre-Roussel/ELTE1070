/*

Important - Add to git ignore

*/

/*
SSID du WIFI ainsi que le mot de passe
Modifier les paramètre WIFI pour le réseau auquels votre objets doit se brancher
*/



//  Uncoment to use IDO open network
/*
    #define WIFI_SECRET_SSID "IOT_OBJECTS"
    #define WIFI_SECRET_USER ""
    #define WIFI_SECRET_PASS "42Bidules!"
    #define SECRET_MQTT_SERVER_IP "10.10.2.20"

*/

//  Uncoment to use IDO open network
/*
    #define WIFI_SECRET_SSID "IDO2"
    #define WIFI_SECRET_USER ""
    #define WIFI_SECRET_PASS "99Bidules!"
    #define SECRET_MQTT_SERVER_IP "192.168.1.99"
*/

//  Uncoment to use demo open network

    #define WIFI_SECRET_SSID "IDO2"
    #define WIFI_SECRET_USER ""
    #define WIFI_SECRET_PASS "99Bidules!"
    #define SECRET_MQTT_SERVER_IP "192.168.2.199"



//  Uncoment to test other wifi  networks
/*
    #define WIFI_SECRET_SSID "CCNB-IOT-WRLS"
    #define WIFI_SECRET_USER ""
    #define WIFI_SECRET_PASS "iotwifi2020"
    #define SECRET_MQTT_SERVER_IP "198.164.130.74"

*/

//  Uncoment to use CCNB WPA2 Enterprise network
/*  
    #define WIFI_SECRET_SSID "CCNB-IOT-WRLS"
    #define WIFI_SECRET_USER "ba-ido-01"
    #define WIFI_SECRET_PASS "iotwifi2020"
    #define SECRET_MQTT_SERVER_IP "198.164.130.74"
*/
/*
Information nécessaire pour le branchement a un Broker MQTT
Dans le cadre du cours AIIA1013, ne modifié pas cet information
*/

#define SECRET_MQTT_SERVER_PORT 1883

/*
Détails sur l'indentification de l'objet
Cette information provient de l'objet virtuel créer sur le serveur Thingsbord
*/

#define SECRET_TOKEN  "bZtOjXALFUo4jBGI0HOf"
#define SECRET_DEVICE_ID "19b8b040-5085-11ed-9f5d-cb63774c0837"



