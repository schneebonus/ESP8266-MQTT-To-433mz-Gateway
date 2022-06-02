
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <RCSwitch.h>
#include <Ticker.h>

#define DEBUGGING false
#define TRANSMIT_PIN 12

const char* ssid = "";          # ToDo
const char* password = "";      # ToDo
const char* mqttServer = "";    # ToDo
const int mqttPort = 1883;      # ToDo
const char* mqttUser = "";      # ToDo
const char* mqttPassword = "";  # ToDo

String MQTT_TOPIC = "433mhz";

WiFiClient espClient;
PubSubClient client(espClient);
volatile int watchdogCount = 0;
Ticker secondTick;
RCSwitch mySwitch = RCSwitch();

void setup() {
  if(DEBUGGING)Serial.begin(115200);

  // init
  connect_wifi();               // wlan verbinden
  connect_mqtt();               // mqtt verbinden
  client.subscribe((MQTT_TOPIC + "/+").c_str());
  mySwitch.enableTransmit(TRANSMIT_PIN);

  // start the watchdog
  // restarts esp in case main loop does not finish after 10 seconds
  secondTick.attach(1, ISRWatchdog);
}

void loop() {
    client.loop();

    // reset watchdog to prevent reset
    watchdogCount = 0;
    
    // handle wifi connection
    int wifi_retry = 0;
    while(WiFi.status() != WL_CONNECTED && wifi_retry < 5 ) {
        // reconnect wifi if not connected
        wifi_retry++;
        WiFi.disconnect();
        WiFi.mode(WIFI_OFF);
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid, password);
        delay(1000);
    }
    if(wifi_retry >= 5) {
        // if reconnect failed 5 times -> restart esp
        ESP.restart();
    }
}
//---------------------- String Magic --------------------------//
String extract_hauscode_from_topic(String topic){
  return extract_code_from_topic(topic, 0, 5);
}

String extract_device_code_from_topic(String topic){
  return extract_code_from_topic(topic, 5, 10);
}

String extract_code_from_topic(String topic, int start, int end){
  if(topic.indexOf('/') == 6){
    String prefix = topic.substring(0,6);
    if(DEBUGGING)Serial.println("Prefix: " + prefix);
    if(prefix == MQTT_TOPIC){
      String code = topic.substring(7, 17);
      if(DEBUGGING)Serial.println("Code: " + code);
      String result = code.substring(start,  end);
      return result;
    }
    return "wrong prefix";
  }
  return "wrong prefix size";
}

//---------------------- 433mhz --------------------------//
// switch a 433mhz device
void switchDevice(String state, const char* codeA, const char* codeB){
    if(state == "true"){
      mySwitch.switchOn(codeA, codeB);
    }
    else if(state == "false"){
      mySwitch.switchOff(codeA, codeB);
    }
}

//---------------------- WIFI --------------------------//
void connect_wifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(10);
  }
  if(DEBUGGING)Serial.println("Connected to the WiFi network");
}



//---------------------- MQTT --------------------------//
void connect_mqtt() {
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  while (!client.connected()) {
    if (client.connect("ESP32Client", mqttUser, mqttPassword )) {
      if(DEBUGGING)Serial.println("Connected to MQTT");
    } else {
      if(DEBUGGING)Serial.print("failed with state ");
      if(DEBUGGING)Serial.print(client.state());
      delay(2000);
    }
  }
}

// callback to handle incoming mqtt events
void callback(char* topic, byte* payload, unsigned int length) {
  if(DEBUGGING)Serial.println("callback");
  String state = byteToString(payload, length);  
  if(DEBUGGING)Serial.println(String(topic) + ": " + String(state));
  if(is_my_business(topic)){
    String hauscode = extract_hauscode_from_topic(topic);
    String device_code = extract_device_code_from_topic(topic);
    if(DEBUGGING)Serial.println("Haus: " + hauscode);
    if(DEBUGGING)Serial.println("Gerät: " + device_code);
    switchDevice(state, hauscode.c_str(), device_code.c_str());
  }
}

bool is_my_business(String topic){
  if(topic.indexOf('/') == 6){
    String prefix = topic.substring(0,6);
    if(prefix == MQTT_TOPIC){
        return true;
    }
    return false;
    }
    return false;
}

//---------------------- Watchdog --------------------------//
// watchdog to reset after crashes
void ISRWatchdog(){
  watchdogCount++;
  if(watchdogCount == 10){
    ESP.reset();
  }
}

//---------------------- Utils --------------------------//
// convert a byte array with a given length to a string
String byteToString(byte* payload, unsigned int length){
  String state = "";
  for (int i = 0; i < length; i++) {
    state += (char)payload[i];
  }
  return state;
}
