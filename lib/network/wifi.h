#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <config.h>
#include <service_register.h>
#include <update_server.h>

void connectWifi(void) {
  while(WiFi.waitForConnectResult() != WL_CONNECTED){
    WiFi.begin(NETWORK_SSID, NETWORK_PASSWORD);
    if(WiFi.waitForConnectResult() == WL_CONNECTED) {
      setupUpdateServer();
      registerDevice();
    } else {
      Serial.println("action=wifi status=error");
    }
  }
}

void setupWifi(void){
  WiFi.mode(WIFI_STA);
  WiFi.begin(NETWORK_SSID, NETWORK_PASSWORD);
  if(WiFi.waitForConnectResult() == WL_CONNECTED) {
    Serial.println("action=wifi status=success");
    setupUpdateServer();
    registerDevice();
  }
}
