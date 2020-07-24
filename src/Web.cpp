#include "Web.h"
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

Web::Web(const char* ssid, const char* wiFiPassword, const char* hostname, const uint16_t port, const char* otaPassword) {
    this->ssid = ssid;
    this->wiFiPassword = wiFiPassword;

    this->hostname = hostname;
    this->port = port;
    this->otaPassword = otaPassword;
}

Web::~Web() {
}

void Web::setup() {
    delay(10);
    
	_openWiFi();
    _setupOTA();    
}

void Web::loop() {
    ArduinoOTA.handle();
}

void Web::_openWiFi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, wiFiPassword);
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("Connection Failed! Rebooting...");
        delay(5000);
        ESP.restart();
    }
}

void Web::_setupOTA() {
    ArduinoOTA.setPort(port);
    ArduinoOTA.setHostname(hostname);
    ArduinoOTA.setPassword(otaPassword);

    ArduinoOTA.onStart([]() {
        Serial.println("Start");
    });
    ArduinoOTA.onEnd([]() {
        Serial.println("\nEnd");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });
    ArduinoOTA.begin();
    Serial.println("Ready");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}