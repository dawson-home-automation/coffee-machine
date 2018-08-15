#include <wifi.h>
#include <mqtt_client.h>
#include <node_mapping.h>
#include <configs.h>

#define COFFEE_MACHINE_SWITCH D9

void setup() {
  Serial.begin(9600);
  pinMode(COFFEE_MACHINE_SWITCH, OUTPUT);

  setupMQTT(process_machine_state);
  setupWifi(NETWORK_SSID, NETWORK_PASSWORD);
  subscribe((char *) MQTT_TOPIC);
}

void loop() {
  connectWifi(NETWORK_SSID, NETWORK_PASSWORD);
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
