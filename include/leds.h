#ifndef _LEDS
#define _LEDS
#include <Arduino.h>

#define MB        0b01110000
#define MB1       0b01000000
#define MB2       0b00100000
#define MB3       0b00010000
#define M0        0b00001100
#define MO1       0b00001000
#define MO2       0b00000100
#define LED_DIR   0b10000011
#define LED_LEFT  0b00000010
#define LED_FRONT 0b00000001
#define LED_RIGHT 0b10000000
#define LED_ALL   0b11111111

void setLED(uint8_t led, bool on);
void updateLEDs();

#endif