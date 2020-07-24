#include "Train.h"

#include "config.h"

Train::Train() {}

Train::~Train() {}

void Train::setup() {
  pinMode(LED_BL2, OUTPUT);
  pinMode(LED_BL1, OUTPUT);
  pinMode(LED_HB2, OUTPUT);
  pinMode(LED_HB1, OUTPUT);

  pinMode(LED_HDL, OUTPUT);

  pinMode(motor_AIN1, OUTPUT);
  pinMode(motor_AIN2, OUTPUT);
  pinMode(motor_PWM, OUTPUT);

  digitalWrite(LED_BL2, 0);
  digitalWrite(LED_BL1, 0);
  digitalWrite(LED_HB2, 0);
  digitalWrite(LED_HB1, 0);

  digitalWrite(motor_AIN1, 0);
  digitalWrite(motor_AIN2, 1);

  analogWrite(motor_PWM, 0);
  analogWrite(LED_HDL, 1023);
}

void Train::setSpeed(int16_t speed) {
  if (speed < 0) {
    this->direction = BACKWARD;
  } else {
    this->direction = FORWARD;
  }

  this->currentSpeed = abs(speed);
}

void Train::loop() {
  analogWrite(motor_PWM, this->currentSpeed);

  digitalWrite(motor_AIN1, this->direction);
  digitalWrite(motor_AIN2, !this->direction);
}