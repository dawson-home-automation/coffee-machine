#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>

#define UPDATE_PORT 8080
const char* host = "arduino";

ESP8266WebServer httpServer(UPDATE_PORT);
ESP8266HTTPUpdateServer httpUpdater;

void setupUpdateServer(void){
  MDNS.begin(host);
  httpUpdater.setup(&httpServer);
  httpServer.begin();

  MDNS.addService("http", "tcp", UPDATE_PORT);
  Serial.printf("action=update_server status=success port=%d\n", UPDATE_PORT);
}

void loopUpdateServer(void){
  httpServer.handleClient();
}
