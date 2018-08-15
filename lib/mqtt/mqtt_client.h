#include <ESP8266WiFi.h>
#include <PubSubClient.h>

void setupMQTT(char* mqtt_server,
               int mqtt_port,
               char* mqtt_username,
               char* mqtt_password,
               boolean secure,
               std::function<void(char*, uint8_t*, unsigned int)> callback);
void loopMQTT();
void publish_message(const char *, int, const char *, boolean);
void subscribe(char*);
void mqtt_connect();
