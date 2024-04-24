#ifndef _BUTTONS
#define BUTTONS
#include<Arduino.h>
//setup button PINS and registers
void setupButtons();
//return witch buttons are being pressed right now and then zero it out.
uint8_t readButtons();
#endif