#include <Arduino.h>
#include <leds.h>
#include <tof.h>
#include <buttons.h>

void setup() {
  setupTOF();
  setupButtons();
  setupLEDs();
  pinMode(13,OUTPUT);
  readTOF();
  readButtons();
  setLED(1,1);
  updateLEDs();
}

void loop() {
  delay(1000);
  digitalWrite(13,HIGH);
  delay(1000);
  digitalWrite(13,LOW);
}