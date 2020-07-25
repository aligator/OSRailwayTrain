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

/**
 * setSpeed sets the target speed. The train will slowly
 * accelerate or slow down to the requested speed based
 * on the set acceleration parameters.
 */
void Train::setSpeed(int16_t speed) {
  if (speed < 0) {
    this->targetDirection = BACKWARD;
  } else {
    this->targetDirection = FORWARD;
  }

  if (this->targetDirection != this->currentDirection) {
    this->isChangingDirection = true;
  }
  this->targetSpeed = abs(speed);
}

/**
 * forceSpeed is the same as the setSpeed
 * but sets immediately the new speed and direction.
 */
void Train::forceSpeed(int16_t speed) {
  if (speed < 0) {
    this->targetDirection = BACKWARD;
  } else {
    this->targetDirection = FORWARD;
  }

  this->currentDirection = this->targetDirection;

  this->currentSpeed = abs(speed);
  this->targetSpeed = abs(speed);
}

void Train::setAccelerationSteps(int16_t steps) {
  this->accelerationSteps = steps;
}

void Train::setAccelerationTimeSteps(int16_t millis) {
  this->accelerationTimeSteps = millis;
}

void Train::setBackLights(bool state) { this->backLights = state; }
void Train::setHeadLights(bool state) { this->headLights = state; }

void Train::loop() {
  analogWrite(motor_PWM, this->currentSpeed);

  digitalWrite(motor_AIN1, this->currentDirection);
  digitalWrite(motor_AIN2, !this->currentDirection);

  if (this->backLights) {
    digitalWrite(LED_BL2, this->currentDirection);
    digitalWrite(LED_BL1, !this->currentDirection);
  } else {
    digitalWrite(LED_BL2, 0);
    digitalWrite(LED_BL1, 0);
  }

  if (this->headLights) {
    digitalWrite(LED_HB2, this->currentDirection);
    digitalWrite(LED_HB1, !this->currentDirection);

  } else {
    digitalWrite(LED_HB2, 0);
    digitalWrite(LED_HB1, 0);
  }

  uint16_t targetSpeed = this->targetSpeed;
  if (this->isChangingDirection) {
    targetSpeed = 0;
  }

  if (this->currentSpeed == targetSpeed) {
    if (this->isChangingDirection) {
      this->isChangingDirection = false;
      this->currentDirection = this->targetDirection;
      targetSpeed = this->targetSpeed;
    } else {
      return;
    }
  }

  unsigned long currentMillis = millis();
  if (currentMillis - this->previousMillis >= this->accelerationTimeSteps) {
    this->previousMillis = currentMillis;

    if (targetSpeed < this->currentSpeed) {
      this->currentSpeed -= this->accelerationSteps;
      if (this->currentSpeed < targetSpeed) {
        this->currentSpeed = targetSpeed;
      }
    } else {
      this->currentSpeed += this->accelerationSteps;
      if (this->currentSpeed > targetSpeed) {
        this->currentSpeed = targetSpeed;
      }
    }
  }
}