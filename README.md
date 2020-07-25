# OSRailway Train

This is an arduino ESP-8266 firmware to control an [OSRailway](https://www.thingiverse.com/thing:4408535) train using [MQTT](https://en.wikipedia.org/wiki/MQTT). The wiring is the same as described for the official firmware of the [Hectorrail 141 Wifi locomotive](https://www.thingiverse.com/thing:2575667).

# Features

Currently it supports:

- Setting the speed and direction using the topic "/OSRailway/<train_name>/drive" using integers from -1023 to 1023.
- Stopping the train using the same topic with the value 0.
- OverTheAir update capability if configured properly. Updates have to be installed using Platformio.
- Configurable smooth speed change.
- Force speed change (e.g. immediate stop)

# Prequisites

- Platformio installed. (example platformio.ini provided)
- A ESP-8266 NodeMCU board.
- A MQTT broker accessible using a WIFI network (currently without SSL support).
- Rename the config.example.h and adapt it as you need it.

# MQTT Topics

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

# Future

I have the following ideas for possible improvements and features:

- Support the LEDs like the official firmware.
- Create a control-server with web-ui to control several trains at once.
- Create a raspi-image with the server software and a mosquitto server pre-installed.
