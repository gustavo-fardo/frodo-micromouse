#include <Arduino.h>
#include <leds.h>
#include <tof.h>
#include <buttons.h>
#include <encoder.h>
#include <constants.h>
#include <PID.h>
#include <pins.h>
void setup() {
  setupEncoders();
  setupTOF();
  setupButtons();
  setupLEDs();
  
  setupPID();
  
  pinMode(13,OUTPUT);
  readTOF();
  readButtons();
  setLED(1,1);
  updateLEDs();
  setPID(PID_AUTO_STOP_X);
  setXTheta(180,0);
  setVW(60,0);
  digitalWrite(13,LOW);
}

void loop() {
  if(MoveEnded())
    digitalWrite(13,HIGH);
  
}