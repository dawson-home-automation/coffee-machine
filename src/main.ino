#include <wifi.h>

void setup() {
  Serial.begin(9600);

  setupMQTT();
  setupWifi();
  subscribe("topic/to/use");
}

void loop() {
  connectWifi();
  loopUpdateServer();
  loopMQTT();
  delay(200);
}
