#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <config.h>

void setupMQTT();
void loopMQTT();
void publish_message(const char *, int, const char *, boolean);
void subscribe(char*);
void mqtt_connect();
