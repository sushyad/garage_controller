#include "debug.h"
#include "garage_controller.h"

// MQTT: topics
// state
const PROGMEM char* MQTT_GARAGE_DOOR_LEFT_STATE_TOPIC = "garageDoor/left/status";
const PROGMEM char* MQTT_GARAGE_DOOR_LEFT_COMMAND_TOPIC = "garageDoor/left/command";
const PROGMEM char* MQTT_GARAGE_DOOR_RIGHT_STATE_TOPIC = "garageDoor/right/status";
const PROGMEM char* MQTT_GARAGE_DOOR_RIGHT_COMMAND_TOPIC = "garageDoor/right/command";

// pins used for the rgb led (PWM)
const PROGMEM uint8_t GARAGE_DOOR_LEFT_PIN = 12;
const PROGMEM uint8_t GARAGE_DOOR_RIGHT_PIN = 13;

// function called to adapt the brightness and the color of the led
void toggle(uint8_t pin) {
  digitalWrite(pin, 0);
  delay(500);
  digitalWrite(pin, 1);  
}

void setupDevice() {
  pinMode(GARAGE_DOOR_LEFT_PIN, OUTPUT);
  pinMode(GARAGE_DOOR_RIGHT_PIN, OUTPUT);
  digitalWrite(GARAGE_DOOR_LEFT_PIN, 1);
  digitalWrite(GARAGE_DOOR_RIGHT_PIN, 1);
}

void mqttConnectedDeviceCallback(PubSubClient mqttClient) {
  mqttClient.subscribe(MQTT_GARAGE_DOOR_LEFT_COMMAND_TOPIC);
  mqttClient.subscribe(MQTT_GARAGE_DOOR_RIGHT_COMMAND_TOPIC);
}

void checkDevice() {
}

boolean deviceCallback(char* p_topic, byte* p_payload, unsigned int p_length) {
  // concat the payload into a string
  String payload;
  for (uint8_t i = 0; i < p_length; i++) {
    payload.concat((char)p_payload[i]);
  }
  // handle message topic
  if (String(MQTT_GARAGE_DOOR_LEFT_COMMAND_TOPIC).equals(p_topic)) {
    toggle(GARAGE_DOOR_LEFT_PIN);
    return true;
  } else if (String(MQTT_GARAGE_DOOR_RIGHT_COMMAND_TOPIC).equals(p_topic)) {
    toggle(GARAGE_DOOR_RIGHT_PIN);
    return true;
  }
  return false;
}
