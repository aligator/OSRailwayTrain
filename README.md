# OSRailway Train

This is an arduino ESP-8266 firmware to control an [OSRailway](https://www.thingiverse.com/thing:4408535) train using [MQTT](https://en.wikipedia.org/wiki/MQTT). The wiring is the same as described for the official firmware of the [Hectorrail 141 Wifi locomotive](https://www.thingiverse.com/thing:2575667).

Iam currently also building a first version of a web-ui to control several trains with this firmware:
[OSRailway Control](https://github.com/aligator/OSRailwayControl)

# Disclaimer

This software is in an early stage. The MQTT-api may change.

# Features

Currently it supports:

- Setting the speed and direction.
- Stopping the train using the same topic with the value 0.
- OverTheAir update capability if configured properly. Updates have to be installed using Platformio.
- Configurable smooth speed change.
- Force speed change (e.g. immediate stop)
- Set back lights. (the red lights)
- Set head lights. (the white lights)
- Setting the availability status automatically and unset it as last will.

# Prequisites

- Platformio installed. (example platformio.ini provided)
- A ESP-8266 NodeMCU board.
- A MQTT broker accessible using a WIFI network (currently without SSL support).
- Rename the config.example.h and adapt it as you need it.

# MQTT Topics

All topics are prefixed by "/OSRailway/train-name".
So if you configured a train name like "train1" it would result in "/OSRailway/train1/drive".

- /drive
  Just pass a value from -1023 to 1023 to drive the train. You can use 0 to stop it. The speed is changed slowly based on the acceleration settings.
- /drive/force
  Just pass a value from -1023 to 1023 to drive the train. The speed is changed immediately. The acceleration settings are ignored.
  Can also be used to stop the train immediately using 0.
- /acceleration/timeSteps
  This sets the time steps in milliseconds. Just pass a value from 0 to 1000.
  So if you set it for example to 500 it changes the speed every half second until the target speed is reached.
- /acceleration/speedSteps
  This sets the speed steps to increase for every configured time step. Just pass a value from 0 to 2047.
  If you set it for example to 200 it changes the speed by 200 speed-points every configured time step.
- /lights/back
  This enables the red back lights. Just pass 1 to enable and 0 to disable the lights.
  They are always automatically adapted to match the driving direction.
- /lights/head
  This enables the white head lights. Just pass 1 to enable and 0 to disable the lights.
  They are always automatically adapted to match the driving direction.
- /status
  If it is set to 1 the train is alive. Else it is disconnected.

# How to install

(To be written...)

# Future

I have the following ideas for possible improvements and features:

- Create a raspi-image with the server software [OSRailway Control](https://github.com/aligator/OSRailwayControl) and a mosquitto server pre-installed.
