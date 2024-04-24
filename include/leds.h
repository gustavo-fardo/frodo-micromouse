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

//seta um led ou coleção de leds para um valor 1 ou 0, juntar LEDs com LED1 | LED2 | LED3 ... etc
void setLED(uint8_t led, bool on);
//pega os valores de LED atual e os seta no shift register
void updateLEDs();
//faz o setup inicial dos pinos de saída e entrada dos LEDs
void setupLEDs();

#endif