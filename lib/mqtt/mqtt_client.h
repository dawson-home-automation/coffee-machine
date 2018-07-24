#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "config.h"

void setupMQTT();
void loopMQTT();
void publish_message(char *, int, char *, boolean);
void subscribe(char*);
void mqtt_connect();
