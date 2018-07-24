# Esp8266 Base Firmware

This project is a base firmware to use with the [IOT PAAS](https://github.com/iot-paas). With the base for secure communication with external devices.

The project is built with a security base to ensure that you IOT device wont be used by a non authorized person.

## Installation

The project is created with [PlatformIO](http://platformio.org) and open source ecosystem for IOT development.

In order to compile and run the project, you need to install the following software:

Fist install [Atom](https://atom.io/)

Then install the [PlatformIO](http://platformio.org/get-started/ide?install) as an atom plugin

## Usage

All the necessary configurations are located in the [config.h](https://github.com/iot-paas/firmware-base-nodemcu/blob/master/lib/config/config.h) file.

`NETWORK_SSID`: Your wifi network SSID

`NETWORK_PASSWORD`: Your wifi network password

`MQTT_SERVER`: Url of the MQTT server
`MQTT_SERVER_PORT`: Port of the MQTT Server

## License

Copyright © 2016 Dawson Freitas Israel

Distributed under the Eclipse Public License either version 1.0 or (at
your option) any later version.
