# OSRailway Train

This is an arduino ESP-8266 firmware to control an [OSRailway](https://www.thingiverse.com/thing:4408535) train using [MQTT](https://en.wikipedia.org/wiki/MQTT). The wiring is the same as described for the official firmware of the [Hectorrail 141 Wifi locomotive](https://www.thingiverse.com/thing:2575667).

# Features

Currently it supports:

- Setting the speed and direction using the topic "/OSRailway/<train_name>/drive" using integers from -1023 to 1023.
- Stopping the train using the same topic with the value 0.
- OverTheAir update capability if configured propperly. Updates have to be installed using Platformio.

# Prequisites

- Platformio installed. (example platformio.ini provided)
- A ESP-8266 NodeMCU board.
- A MQTT broker accessible using a WIFI network (currently without SSL support).
- Rename the config.example.h and adapt it as you need it.

# Future

I have the following ideas for possible improvements and features:

- Support the LEDs like the official firmware.
- Support smooth starting and stopping similar to the official firmware.
- Create a control-server with web-ui to control several trains at once.
- Create a raspi-image with the server software and a mosquitto server pre-installed.
