#include <Arduino.h>
#include <leds.h>
#include <tof.h>
#include <buttons.h>
#include <constants.h>
#include <PID.h>
#include <pins.h>
#include <states.h>

//TODO funções para lidar com o mapa e paredes do labirinto (não aqui é claro)


void setup() {
  setupTOF();
  setupButtons();
  setupLEDs();
  setupPID(); //internamente chama setupEncoders(), não adicionar a parte
  activatePID(false);
  setLED(MO1|MB1,HIGH);
  updateLEDs();
}


void loop() {
  readTOF();
  baseState();
  setLED(LED_FRONT,wall_front);
  setLED(LED_RIGHT,wall_right);
  setLED(LED_LEFT,wall_left);
  updateLEDs();
}