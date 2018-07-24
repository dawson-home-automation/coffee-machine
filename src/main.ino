#include <wifi.h>
#include <mqtt_client.h>

void setup() {
  Serial.begin(9600);

  setupMQTT(callback);
  setupWifi();
  subscribe((char *) "topic/to/use");
}

void loop() {
  connectWifi();
  loopUpdateServer();
  loopMQTT();
  delay(200);
}

void callback(char* topic, byte* payload, unsigned int length) {
  String payloadStr = String((char *) payload).substring(0, length);
  if (payloadStr.indexOf("command") >= 0){
    publish_message(topic, 0, "The is executed!", true);
  }
}
