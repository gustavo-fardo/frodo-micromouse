#ifndef _ENCODER
#define _ENCODER
#include <Arduino.h>

//encoder constants
#define COUNTS_PER_ROT 406.3f

extern int32_t count_left,count_right;
float getV1();
float getV2();
void setupEncoders();

#endif