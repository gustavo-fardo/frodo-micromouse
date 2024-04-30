#ifndef _BUTTONS
#define BUTTONS
#include<Arduino.h>
//setup button PINS and registers
void setupButtons();
//return witch buttons are being pressed right now
uint8_t readButtons();
//zeroes buttons, as if already analized
void resetButtons();
#endif