#ifndef _ENCODER
#define _ENCODER
#include <Arduino.h>


#define INVERSE_COUNTS_PER_ROT 1/406.9f

extern int16_t count_left,count_right;
void setupEncoders();

#endif