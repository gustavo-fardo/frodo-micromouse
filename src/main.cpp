#include <Arduino.h>
#include <leds.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  
  setupLEDs();
}

void loop() {
  setLED(LED_ALL,HIGH);
  updateLEDs();
}