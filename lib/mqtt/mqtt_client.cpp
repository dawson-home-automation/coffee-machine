#include <mqtt_client.h>
#include <config.h>

WiFiClientSecure wifi;
PubSubClient client(wifi);
char* topic_subscribed;

void callback(char* topic, byte* payload, unsigned int length) {
  String payloadStr = String((char *) payload).substring(0, length);
  if (payloadStr.indexOf("command") >= 0){
    publish_message(topic, 0, "The is executed!", true);
  }
}

void setupMQTT() {
  client.setServer(MQTT_SERVER, MQTT_SERVER_PORT);
  client.setCallback(callback);
}

void loopMQTT() {
  if (!client.connected()) {
    mqtt_connect();
    subscribe(topic_subscribed);
  }
  client.loop();
}

void subscribe(char* topic) {
  mqtt_connect();
  topic_subscribed = topic;
  client.subscribe(topic, 0);
}

void publish_message(char * topic, int qos, char * message, boolean retained) {
  mqtt_connect();
  client.publish(topic, message, retained);
}

void mqtt_connect() {
  unsigned char mac[6];
  WiFi.macAddress(mac);

  while (!client.connected()) {
    if (client.connect((char *) mac, MQTT_USERNAME, MQTT_PASSWORD)) {
      Serial.println("action=mqtt status=success");
    } else {
      Serial.printf("action=mqtt status=error code=%d", client.state());
    }
  }
}

String macToStr(const uint8_t* mac) {
  String result;
  for (int i = 0; i < 6; ++i) {
    result += String(mac[i], 16);
    if (i < 5) {
      result += ':';
    }
  }
  return result;
}

String getMacAddress() {
  unsigned char mac[6];

  WiFi.macAddress(mac);
  return macToStr(mac);
}
