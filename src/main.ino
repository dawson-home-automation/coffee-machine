#include <wifi.h>
#include <mqtt_client.h>

void setup() {
  Serial.begin(9600);

  setupMQTT();
  setupWifi();
  subscribe((char *) "topic/to/use");
}

void loop() {
  connectWifi();
  loopUpdateServer();
  loopMQTT();
  delay(200);
}
