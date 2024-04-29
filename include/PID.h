#pragma once
#include <Arduino.h>

#define PID_STRAIGHT 0b01
#define PID_INPLACE 0b10
#define PID_USE_TOF 0b100
#define PID_DEFAULT 0b00
#define PID_AUTO_STOP_X 0b10000
#define PID_AUTO_STOP_THETA 0b1000

void setVW(float v, float w);
void setXTheta(float x, float theta);
void resetIntegrals();
void setupPID();
void setPID(uint8_t control);
float getX();
float getTheta();
bool MoveEnded();