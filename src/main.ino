#include "network/wifi.h"
#include "mqtt/mqtt_client.h"
#include "node_mapping/node_mapping.h"
#include <configs.h>

#define COFFEE_MACHINE_SWITCH D9

void setup() {
  Serial.begin(9600);
  pinMode(COFFEE_MACHINE_SWITCH, OUTPUT);

  setupMQTT((char *) MQTT_SERVER,
            MQTT_SERVER_PORT,
            (char *) MQTT_USERNAME,
            (char *) MQTT_PASSWORD,
            false,
            process_machine_state);

  setupWifi((char *) NETWORK_SSID, (char *) NETWORK_PASSWORD, (char *) TARGET);
  subscribe((char *) MQTT_TOPIC);
}

void loop() {
  connectWifi((char *) NETWORK_SSID, (char *) NETWORK_PASSWORD, (char *) TARGET);
  loopUpdateServer();
  loopMQTT();
  delay(200);
}

void process_machine_state(char* topic, byte* payload, unsigned int length) {
  String payloadStr = String((char *) payload).substring(0, length);
  if (payloadStr.indexOf("coffee_machine=on") >= 0) {
    Serial.println("Turning ON");
    digitalWrite(COFFEE_MACHINE_SWITCH, HIGH);
  } else if (payloadStr.indexOf("coffee_machine=off") >= 0) {
    Serial.println("Turning Off");
    digitalWrite(COFFEE_MACHINE_SWITCH, LOW);
  }
}
