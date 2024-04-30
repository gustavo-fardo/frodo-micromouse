#pragma once
#include <Arduino.h>

#define PID_STRAIGHT 0b01
#define PID_INPLACE 0b10
#define PID_USE_TOF 0b100
#define PID_DEFAULT 0b00
#define PID_AUTO_STOP_X 0b10000
#define PID_AUTO_STOP_THETA 0b1000

/* MANUAL
- FAÇA O SETUP DO PID com setupPID(); uma única vez
- Ative o pid com activate PID();

toda vez que realizar uma ação:
- faça o setup das configurações para a ação com setPID(control), utilizando as configurações acima, que podem ser conectadas
 PID_STRAIGHT - ativa PID para corrigir erros de drift angular
 PID_INPLACE - ativa PID para corrigir drifts ao rotacionar, como offsets etc.
 PID_USE_TOF - cuidado apenas ative se saber que está okay utilizá-lo no momento, irá utilizar os tofs para calcular erros angulares
 PID_DEFAULT - não seta nada de diferenciado.
 PID_AUTO_STOP_X - ativa parada automática do movimento retilínio quando a distancia desejada for alcançada.
 PID_AUTO_STOP_THETA - ativa a parada autimática do movimento rotacional quando o angulo em rad for alcançado.
 obs. a função MoveEnded apenas funciona caso ao menos uma das configurações de AUTO_STOP estiverem ligadas. Caso ambas estejam
 ela apenas retorna true quando os dois movimentos acabarem.
  - resete os counts e integrais com resetIntegrals()
 - sete a velocidade e velocidade angular que deseja ter com setVW(v,w) em mm/s e rad/s
 - sete o angulo e a distância que deseja percorrer com setXTheta(x,theta) em mm e rad - apenas quando AUTO_STOP ativo.
- observe o decorrimento do movimento com getTheta() ou getX() ou até MoveEnded().


*/
void setVW(float v, float w);
void setXTheta(float x, float theta);
//reseta integrais de pid além de valores de count dos encoders
void resetIntegrals();
//faz setup dos interrupts e pinos do PID
void setupPID();
//faz setup de como o PID deve se comportar
void setPID(uint8_t control);
//retorna distancia andada em mm
float getX();
//retorna giro realizado em radianos
float getTheta();
//retorna true quando movimento de auto_stop acaba
bool moveEnded();
//ativa todo o sistema de PID
void activatePID(bool on);