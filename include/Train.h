#ifndef TRAIN_H_
#define TRAIN_H_

#include "Arduino.h"
#include "config.h"

#define FORWARD 0
#define BACKWARD 1

class Train {
 public:
  Train();
  virtual ~Train();

  void setup();
  void loop();
  void setSpeed(int16_t speed);
  void forceSpeed(int16_t speed);
  void setAccelerationSteps(int16_t steps);
  void setAccelerationTimeSteps(int16_t millis);
  void setBackLights(bool state);
  void setHeadLights(bool state);

 private:
  int16_t currentSpeed = 0;
  int16_t targetSpeed = 0;
  uint16_t accelerationSteps = 5;
  uint16_t accelerationTimeSteps = 10;
  bool backLights = false;
  bool headLights = false;
  bool currentDirection = FORWARD;
  bool targetDirection = FORWARD;
  bool isChangingDirection = false;

  unsigned long previousMillis = 0;
};

#endif /* TRAIN_H_ */