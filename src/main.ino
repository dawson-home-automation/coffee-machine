#include <wifi.h>
#include <mqtt_client.h>
#include <node_mapping.h>
#include <configs.h>

#define COFFEE_MACHINE_SWITCH D4

void setup() {
  Serial.begin(9600);
  pinMode(COFFEE_MACHINE_SWITCH, OUTPUT);

  setupMQTT(process_machine_state);
  setupWifi();
  subscribe((char *) MQTT_TOPIC);
}

void loop() {
  connectWifi();
  loopUpdateServer();
  loopMQTT();
  delay(200);
}

void process_machine_state(char* topic, byte* payload, unsigned int length) {
  String payloadStr = String((char *) payload).substring(0, length);
  if (payloadStr.indexOf("coffee_machine=on") >= 0) {
    digitalWrite(COFFEE_MACHINE_SWITCH, HIGH);
  } else if (payloadStr.indexOf("coffee_machine=off") >= 0) {
    digitalWrite(COFFEE_MACHINE_SWITCH, LOW);
  }
}
