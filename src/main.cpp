#include <Arduino.h>

#include "Mqtt.h"
#include "Train.h"
#include "Web.h"
#include "config.h"

const char* ssid = WIFI_SSID;
const char* wiFiPassword = WIFI_PASSWD;
const char* hostname = WIFI_HOSTNAME;

const uint16_t otaPort = OTA_PORT;
const char* otaPassword = OTA_PASSWD;

Web* web = new Web(ssid, wiFiPassword, hostname, otaPort, otaPassword);
Train* train = new Train();
Mqtt* mqtt = new Mqtt(train);

void setup() {
  Serial.begin(9600);
  web->setup();
  mqtt->setup();
  train->setup();
}

void loop() {
  web->loop();
  mqtt->loop();
  train->loop();
}