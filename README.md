# ESP8266-MQTT-To-433mz-Gateway
## Minimalistic MQTT to 433mz remote socket gateway for ESP8266

A robust and minimalistic mqtt to 433mhz gateway for the esp8266.
Enables cheap wireless sockets from the DIY store to be controlled via the MQTT home automation server.
This project follows a minimalist approach, designed solely for reliability.

### Requirenments

- ESP8266 board definition ( https://arduino-esp8266.readthedocs.io/en/latest/installing.html )
- PubSubClient.h ( https://pubsubclient.knolleary.net/ )
- RCSwitch.h ( https://github.com/sui77/rc-switch )
- ESP8266WiFi.h ( https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi )
- Ticker.h ( https://github.com/esp8266/Arduino/tree/master/libraries/Ticker )

### Install

- set wifi settings (ssid and passsword)
- set mqtt settings (mqttServer, mqttPort, mqttUser, mqttPassword)
- deploy to your esp8266

### Node-RED integration

ToDo

### Background information

- 433mhz sender is expected to be on port 12 of the esp8266 but can be changed by changing "TRANSMIT_PIN"
- main loop has to finish every cycle in 10 seconds or the watchdog restarts the device
- if wifi reconnect fails 5 times in a row, the revice restarts

### Further Improvements (maybe... maybe not):

- MQTT over TLS ( + verify certificate fingerprint )
- port project to esp32 and use firmware encryption to protect the passwords
- publish sensor values (dht22?) to mqtt
