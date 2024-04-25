#include <Arduino.h>
#include <leds.h>
#include <tof.h>
#include <buttons.h>
#include <encoder.h>
#include <constants.h>
#include <PID.h>
void setup() {
  setupTOF();
  setupButtons();
  setupLEDs();
  setupEncoders();
  setupPID();
  
  pinMode(13,OUTPUT);
  readTOF();
  readButtons();
  setLED(1,1);
  updateLEDs();
  
  setVW(0,0);
  
}

void loop() {
  delay(1000);
  digitalWrite(13,HIGH);
  delay(1000);
  digitalWrite(13,LOW);
}