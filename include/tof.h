#ifndef _TOF
#define _TOF
#include <Arduino.h>
extern int16_t dist_left, dist_right, dist_front_left, dist_front_right;
extern bool wall_left,wall_front,wall_right;

void setupTOF();
void readTOF();


#endif