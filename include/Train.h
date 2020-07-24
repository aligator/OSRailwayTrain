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
private:
    int16_t currentSpeed = 0;
    bool direction = FORWARD;
};

#endif /* TRAIN_H_ */