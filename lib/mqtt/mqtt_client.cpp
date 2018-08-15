#include <mqtt_client.h>

PubSubClient client;
char* topic_subscribed;
char* username;
char* password;

void setupMQTT(char* mqtt_server,
               int mqtt_port,
               char* mqtt_username,
               char* mqtt_password,
               boolean secure,
               std::function<void(char*, uint8_t*, unsigned int)> callback) {

  if (secure) {
    WiFiClientSecure wifi_secure;
    client.setClient(wifi_secure);
  } else {
    WiFiClient wifi;
    client.setClient(wifi);
  }

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  username = mqtt_username;
  password = mqtt_password;
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

    if (username == NULL) {
      result = client.connect((char *) mac);
    } else {
      result = client.connect((char *) mac, username, password);
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
