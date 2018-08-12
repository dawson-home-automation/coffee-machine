#include <mqtt_client.h>

#ifdef USE_SECURE_CONNECTION
    WiFiClientSecure wifi;
#else
    WiFiClient wifi;
#endif

PubSubClient client(wifi);
char* topic_subscribed;

void setupMQTT(std::function<void(char*, uint8_t*, unsigned int)> callback) {
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

void publish_message(const char * topic, int qos, const char * message, boolean retained) {
  mqtt_connect();
  client.publish(topic, message, retained);
}

void mqtt_connect() {
  unsigned char mac[6];
  WiFi.macAddress(mac);

  while (!client.connected()) {
    int result;

    if (MQTT_USERNAME == NULL) {
      result = client.connect((char *) mac);
    } else {
      result = client.connect((char *) mac, MQTT_USERNAME, MQTT_PASSWORD);
    }

    if (result) {
      Serial.println("action=mqtt status=success");
    } else {
      Serial.printf("action=mqtt status=error code=%d\n", client.state());
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
