
#include <maze.h>
#include <Arduino.h>
#include <leds.h>
#include <tof.h>
#include <buttons.h>
#include <constants.h>
#include <PID.h>
#include <pins.h>
#include <states.h>
#include <position.h>


void setup() {
  setupTOF();
  setupButtons();
  setupLEDs();
  setupPID(); //internamente chama setupEncoders(), não adicionar a parte
  activatePID(false);
  setLED(MO1|MB1,HIGH);
  updateLEDs();
  resetMaze();
}

void loop() {

  readTOF();
  baseState();
  setLED(LED_FRONT,wall_front);
  setLED(LED_RIGHT,wall_right);
  setLED(LED_LEFT,wall_left);
  updateLEDs();
}