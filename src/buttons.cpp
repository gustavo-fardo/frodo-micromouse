
#include<buttons.h>
#include<pins.h>

uint8_t pushedButtons = 0; // botões apertados atuais
uint8_t lastValue= 0b11111111; // ultimo valor lido pelos botões

void setupButtons()
{
  pinMode(PUSH_BUTTON1,INPUT_PULLUP);
  pinMode(PUSH_BUTTON2,INPUT_PULLUP);
  //setup pb interruptions
  PCICR |= 0b010;
  PCMSK0 |=0b1001;
}

uint8_t readButtons() 
{
  return pushedButtons;
}
void resetButtons()
{
  pushedButtons = 0;
}
//interrupção de tratamento dos botões
ISR (PCINT0_vect)
{
  if(!digitalRead(PUSH_BUTTON1)&& lastValue & 0b01) // caso PB1 =0 e anterior =1, falling edge
  {
    pushedButtons |= 0b01;
    //pb1 pushed
  }else if (!digitalRead(PUSH_BUTTON2)&& lastValue & 0b10) //caso PB2=0 e anterior = 1, falling edge
  {
    pushedButtons |= 0b10;
    //pb2 pushed
  }
  lastValue = digitalRead(PUSH_BUTTON1) | (digitalRead(PUSH_BUTTON2)<<1);
}