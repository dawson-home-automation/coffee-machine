#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <configs.h>

void setupMQTT(std::function<void(char*, uint8_t*, unsigned int)> callback);
void loopMQTT();
void publish_message(const char *, int, const char *, boolean);
void subscribe(char*);
void mqtt_connect();
