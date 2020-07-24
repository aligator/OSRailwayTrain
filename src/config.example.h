#ifndef CONFIG_H_
#define CONFIG_H_

// Lights
#define LED_BL2 15;  // Red light on side 2 GPIO15
#define LED_BL1 13;  // Red light on side 1 GPIO13
#define LED_HB2 14;  // High beam side 2 GPIO12
#define LED_HB1 12;  // High beam side 1 GPIO14
#define LED_HDL 2;   // PWM for headlights controlled by motor board

// Motor control
#define motor_AIN1 5;  // GPIO5
#define motor_AIN2 4;  // GPIO4
#define motor_PWM 0;   // GPIO0

#define MQTT_BROKER "192.168.178.53"
#define MQTT_PORT 1883
#define MQTT_USER "...."
#define MQTT_PASSWD "...."

#define WIFI_SSID "...."
#define WIFI_PASSWD "...."

// used to create the mdns <hostname>.local
// (e.g. can be used for the ota update)
#define WIFI_HOSTNAME "os-railway-train1"

#define OTA_PASSWD "....."
#define OTA_PORT 8266

// used to specify the topic:
// e.g. /OSRailway/train1/drive
#define TRAIN_NAME "train1"

#endif /* CONFIG_H_ */