#include <Arduino.h>
#include <leds.h>
#include <tof.h>
#include <buttons.h>
#include <encoder.h>
#include <constants.h>
#include <PID.h>
#include <pins.h>
#include <states.h>
void setup() {
  setupEncoders();
  setupTOF();
  setupButtons();
  setupLEDs();
  setupPID();
}


void loop() {
  readTOF();
  baseState();
  setLED(LED_FRONT,wall_front);
  setLED(LED_RIGHT,wall_right);
  setLED(LED_LEFT,wall_left);
  updateLEDs();
}