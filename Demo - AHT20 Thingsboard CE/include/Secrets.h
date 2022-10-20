/*

Important - Add to git ignore

*/

/*
SSID du WIFI ainsi que le mot de passe
Modifier les paramètre WIFI pour le réseau auquels votre objets doit se brancher
*/


// Uncoment to use home network
/*
    #define WIFI_SECRET_SSID "LeCamping"
    #define WIFI_SECRET_USER ""
    #define WIFI_SECRET_PASS "Summer2019"
*/

//  Uncoment to use IDO Office open network
/*
    #define WIFI_SECRET_SSID "IOT_OBJECTS"
    #define WIFI_SECRET_USER ""
    #define WIFI_SECRET_PASS "42Bidules!"


*/
//  Uncoment to use IDO Class open network

    #define WIFI_SECRET_SSID "IDO-OBJECTS"
    #define WIFI_SECRET_USER ""
    #define WIFI_SECRET_PASS "42Bidules!"



//  Uncoment to test other wifi  networks
/*
    #define WIFI_SECRET_SSID "CCNB-IOT-WRLS"
    #define WIFI_SECRET_USER ""
    #define WIFI_SECRET_PASS "iotwifi2020"

*/

//  Uncoment to use CCNB WPA2 Enterprise network
/*  
    #define WIFI_SECRET_SSID "CCNB-IOT-WRLS"
    #define WIFI_SECRET_USER "ba-ido-01"
    #define WIFI_SECRET_PASS "iotwifi2020"
*/

/*
Information nécessaire pour le branchement a un Broker MQTT
Dans le cadre du cours AIIA1013, ne modifié pas cet information
*/

//#define SECRET_MQTT_SERVER_IP "198.164.130.74"    //Thingsboard Pro
#define SECRET_MQTT_SERVER_IP "10.10.2.20"          //Thingsboard CE Office
#define SECRET_MQTT_SERVER_PORT 1883

/*
Détails sur l'indentification de l'objet
Cette information provient de l'objet virtuel créer sur le serveur Thingsbord
*/

#define SECRET_TOKEN  "DWSjVMBsEZXl7XbRm5Hc"
#define SECRET_DEVICE_ID "e4ae3bd0-3b36-11ed-ab16-cf66c0c207fe"



