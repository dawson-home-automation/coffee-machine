#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <service_register.h>
#include <update_server.h>

void connectWifi(char* network_ssid, char* network_password) {
  while(WiFi.waitForConnectResult() != WL_CONNECTED){
    WiFi.begin(network_ssid, network_password);
    if(WiFi.waitForConnectResult() == WL_CONNECTED) {
      setupUpdateServer();
      registerDevice();
    } else {
      Serial.println("action=wifi status=error");
    }
  }
}

void setupWifi(char* network_ssid, char* network_password){
  WiFi.mode(WIFI_STA);
  WiFi.begin(network_ssid, network_password);
  if(WiFi.waitForConnectResult() == WL_CONNECTED) {
    Serial.println("action=wifi status=success");
    setupUpdateServer();
    registerDevice();
  }
}
