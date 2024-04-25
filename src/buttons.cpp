
#include<buttons.h>
#include<pins.h>
void setupButtons()
{
  pinMode(PUSH_BUTTON1,INPUT_PULLUP);
  pinMode(PUSH_BUTTON2,INPUT_PULLUP);
  //setup pb interruptions
  PCICR |= 0b010;
  PCMSK0 |=0b1001;
}

uint8_t pushedButtons = 0;
uint8_t readButtons() 
{
  uint8_t aux = pushedButtons;
  pushedButtons = 0;
  return aux;
}
ISR (PCINT0_vect)
{
  if(!digitalRead(PUSH_BUTTON1) && !digitalRead(PUSH_BUTTON2))
  {
    pushedButtons = 0b11;
  }
  else if(!digitalRead(PUSH_BUTTON1))
  {
    pushedButtons = 0b01;
    //pb1 pushed
  }else if (!digitalRead(PUSH_BUTTON2))
  {
    pushedButtons = 0b10;
    //pb2 pushed
  }
}