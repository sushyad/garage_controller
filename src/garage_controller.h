#ifndef GARAGE_CONTRLLER_H_INCLUDED
#define GARAGE_CONTRLLER_H_INCLUDED

#include "base.h"

#endif /* GARAGE_CONTRLLER_H_INCLUDED */

void toggle(uint8_t pin);
boolean deviceCallback(char* p_topic, byte* p_payload, unsigned int p_length);
void mqttConnectedDeviceCallback(PubSubClient mqttClient);
