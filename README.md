# ESP8266 gateway: MQTT to 433mz

## Minimalistic MQTT to 433mz remote socket gateway for ESP8266

A robust and minimalistic mqtt to 433mhz gateway for the esp8266.
Enables cheap wireless sockets from the DIY store to be controlled via the MQTT home automation server.
This project follows a minimalist approach, designed solely for reliability and easy Node-RED integration.

![Soldering like a boss](https://github.com/schneebonus/ESP8266-MQTT-To-433mz-Gateway/blob/main/gateway.jpeg?raw=true)

### Requirenments

- ESP8266 board definition ( https://arduino-esp8266.readthedocs.io/en/latest/installing.html )
- PubSubClient.h ( https://pubsubclient.knolleary.net/ )
- RCSwitch.h ( https://github.com/sui77/rc-switch )
- ESP8266WiFi.h ( https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi )
- Ticker.h ( https://github.com/esp8266/Arduino/tree/master/libraries/Ticker )

### Install

- Download 433mhz_mqtt_gateway.ino
- Set wifi settings (ssid and passsword)
- Set mqtt settings (mqttServer, mqttPort, mqttUser, mqttPassword)
- Deploy to your esp8266

### Node-RED integration

- Install the default mqtt node
- Create a function containing nodered_function.js:
![Node-RED Integration Example](https://github.com/schneebonus/ESP8266-MQTT-To-433mz-Gateway/blob/main/nodered.png?raw=true)

### Background information

- 433mhz sender is expected to be on pin 12 of the esp8266 but can be changed by changing "TRANSMIT_PIN"
- main loop has to finish every cycle in 10 seconds or the watchdog restarts the device
- if wifi reconnect fails 5 times in a row, the revice restarts

### Further Improvements (maybe... maybe not):

- MQTT over TLS ( + verify certificate fingerprint )
- port project to esp32 and use firmware encryption to protect the passwords
- publish sensor values (dht22?) to mqtt
