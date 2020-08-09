#include "Mqtt.h"

#include <functional>

#include "Util.h"

#define TOPIC_TRAIN "/OSRailway/" TRAIN_NAME
#define TOPIC_STATUS TOPIC_TRAIN "/status"
#define TOPIC_ALL TOPIC_TRAIN "/#"
#define TOPIC_DRIVE TOPIC_TRAIN "/drive"
#define TOPIC_DRIVE_FORCE TOPIC_TRAIN "/drive/force"
#define TOPIC_ACCELERATION_TIME_STEPS TOPIC_TRAIN "/acceleration/timeSteps"
#define TOPIC_ACCELERATION_SPEED_STEPS TOPIC_TRAIN "/acceleration/speedSteps"
#define TOPIC_BACKLIGHT TOPIC_TRAIN "/lights/back"
#define TOPIC_HEADLIGHT TOPIC_TRAIN "/lights/head"

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
  if (topicString.equals(TOPIC_BACKLIGHT)) {
    if (Util::isValidNumber(message)) {
      int status = message.toInt();
      if (status >= 0 && status <= 1) {
        train->setBackLights(status);
      } else {
        Serial.println("the lights can be enabled / disabled using 1 or 0");
      }
    }
    return;
  }
  if (topicString.equals(TOPIC_HEADLIGHT)) {
    if (Util::isValidNumber(message)) {
      int status = message.toInt();
      if (status >= 0 && status <= 1) {
        train->setHeadLights(status);
      } else {
        Serial.println("the lights can be enabled / disabled using 1 or 0");
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
    this->client.setKeepAlive(10);
    // Attempt to connect
    // For now use "" to indicate the removal of the train
    // as the last will message.
    // Later we may also remember inactive trains (and therefore set the status
    // to "0")
    if (!this->client.connect(clientId.c_str(), user, password, TOPIC_STATUS, 0,
                              true, "", true)) {
      Serial.print("failed, rc=");
      Serial.println(client.state());
    } else {
      Serial.println("Connected");
      delay(100);
      this->client.subscribe(TOPIC_ALL);
      this->client.publish(TOPIC_STATUS, "1", true);
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