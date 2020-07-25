#include "Mqtt.h"

#include <functional>

#include "Util.h"

#define TOPIC "/OSRailway/" TRAIN_NAME
#define TOPIC_ALL TOPIC "/#"
#define TOPIC_DRIVE TOPIC "/drive"
#define TOPIC_DRIVE_FORCE TOPIC "/drive/force"
#define TOPIC_ACCELERATION_TIME_STEPS TOPIC "/acceleration/timeSteps"
#define TOPIC_ACCELERATION_SPEED_STEPS TOPIC "/acceleration/speedSteps"

/**
 * converts bytes to a String
 */
String Mqtt::_byte2str(byte* data, unsigned int length) {
  char* buffer = (char*)malloc(length + 1);
  memcpy(buffer, data, length);
  buffer[length] = 0;

  // or for unicode:
  // const char* str((const wchar_t*)buffer);
  String out = String((const char*)buffer);
  free(buffer);
  return out;
}

void Mqtt::_receiveCallback(char* topic, byte* payload, unsigned int length) {
  String message = Mqtt::_byte2str(payload, length);
  String topicString = String(topic);

  if (topicString.equals(TOPIC_DRIVE)) {
    if (Util::isValidNumber(message)) {
      int speed = message.toInt();
      if (speed >= -1023 && speed <= 1023) {
        train->setSpeed(speed);
      } else {
        Serial.println("the speed has to be an integer from -1023 to 1023");
      }
    }
    return;
  }
  if (topicString.equals(TOPIC_DRIVE_FORCE)) {
    if (Util::isValidNumber(message)) {
      int speed = message.toInt();
      if (speed >= -1023 && speed <= 1023) {
        train->forceSpeed(speed);
      } else {
        Serial.println("the speed has to be an integer from -1023 to 1023");
      }
    }
    return;
  }
  if (topicString.equals(TOPIC_ACCELERATION_TIME_STEPS)) {
    if (Util::isValidNumber(message)) {
      int millis = message.toInt();
      if (millis >= 0 && millis <= 1000) {
        train->setAccelerationTimeSteps(millis);
      } else {
        Serial.println(
            "the acceleration time steps (in milliseconds) has to be an "
            "integer from 0 to 1000");
      }
    }
    return;
  }
  if (topicString.equals(TOPIC_ACCELERATION_SPEED_STEPS)) {
    if (Util::isValidNumber(message)) {
      int speed = message.toInt();
      if (speed >= 0 && speed <= 1000) {
        train->setAccelerationSteps(speed);
      } else {
        Serial.println(
            "the acceleration steps has to be an integer from 0 to 2047");
      }
    }
    return;
  }
}

Mqtt::Mqtt(Train* train) {
  this->train = train;
  this->client = PubSubClient(this->espClient);
}

Mqtt::~Mqtt() {}

void Mqtt::setup() {
  delay(100);
  this->client.setServer(broker, port);
  this->client.setCallback(
      std::bind(&Mqtt::_receiveCallback, this, std::placeholders::_1,
                std::placeholders::_2, std::placeholders::_3));
}

void Mqtt::_reconnect() {
  if (!this->client.connected()) {
    Serial.println("Reconnecting...");

    String clientId = WIFI_HOSTNAME "-";
    clientId += String(random(0xffff), HEX);

    // Attempt to connect
    if (!this->client.connect(clientId.c_str(), user, password)) {
      Serial.print("failed, rc=");
      Serial.println(client.state());
    } else {
      Serial.println("Connected");
      delay(100);
      this->client.subscribe(TOPIC_ALL);
    }
  }
}

void Mqtt::loop() {
  if (!this->client.connected()) {
    delay(1000);
    _reconnect();
  } else {
    this->client.loop();
  }
}