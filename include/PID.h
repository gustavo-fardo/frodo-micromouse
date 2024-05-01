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
#pragma once
#include <Arduino.h>


//Bits de configuração para a função setPID(controls)
#define PID_STRAIGHT 0b01
#define PID_INPLACE 0b10
#define PID_USE_TOF 0b100
#define PID_DEFAULT 0b00
#define PID_AUTO_STOP_X 0b10000
#define PID_AUTO_STOP_THETA 0b1000

/* @name setVW
* @brief Configura qual velocidade, linear e angular, que o micromouse deve seguir.
* @param v velocidade linear almejada em mm/s
* @param w velocidade angular almejada em rad/s
* @return void
* 
* @date alterações:
*   - 30/04/2024: criado comentário, começado a documentar. - @walger-lucas
*/
void setVW(float v, float w);

/* @name setXTheta
* @brief Configura qual o valor para parada automática de distância andada e angulo rotacionado.
* @param x distância em mm necessária para o auto stop retilínio ocorrer.
* @param theta rotação em radianos necessários para o auto stop rotacional ocorrer.
* @return void
* @attention Apenas funciona em caso das configurações do PID estarem com algum AUTO_STOP ativo.
* 
* @date alterações:
*   - 30/04/2024: criado comentário, começado a documentar. - @walger-lucas
*/
void setXTheta(float x, float theta);

/* @name resetIntegrals
* @brief Reseta diversas variáveis utilizadas para manter track do movimento do micromouse, como as integrais do PID, os counts dos encoders, os erros dos sensors e a flag de fim de movimento.
* @return void
* @attention Deve ser utilizado ao fim de um movimento ou inicio de um novo, para que os erros acumulados de um movimento anterior não interfiram no novo, que está iniciando e não possui ligações com este.
* 
* @date alterações:
*   - 30/04/2024: criado comentário, começado a documentar. - @walger-lucas
*/
void resetIntegrals();

/* @name setupPID
* @brief Faz setup dos pinos dos motores e da interrupção de timer do PID (que utiliza o timer1 e periodo de 10ms).
* @return void
* @attention Para função do pid PID_USE_TOF, o setup do TOF deve ser inicializado anteriormente.
* @date alterações:
*   - 30/04/2024: criado comentário, começado a documentar. - @walger-lucas
*/
void setupPID();

/* @name setPID
 * @brief configura PID para certa configuração dada
 * @param control Bits de configuração do micromouse;
 * @return void
 * @note Bits de configuração
 * @note PID_STRAIGHT - ativa PID para corrigir erros de drift angular
 * @note PID_INPLACE - ativa PID para corrigir drifts ao rotacionar, como offsets etc.
 * @note PID_USE_TOF - cuidado apenas ative se saber que está okay utilizá-lo no momento, irá utilizar os tofs para calcular erros angulares
 * @note PID_DEFAULT - não seta nada de diferenciado.
 * @note PID_AUTO_STOP_X - ativa parada automática do movimento retilínio quando a distancia desejada for alcançada.
 * @note PID_AUTO_STOP_THETA - ativa a parada autimática do movimento rotacional quando o angulo em rad for alcançado.
 * 
 * @example  setPID(PID_STRAIGHT | PID_AUTO_STOP_X | PID_USE_TOF); 
 * @example  seta PID para utilizar compensação se drift angular, utilizar parada automática de translação e TOF para calculo de erro angular.
 * 
 * alterações:
    - 30/04/2024: criado comentário, começado a documentar. -  @walger-lucas 
*/
void setPID(uint8_t control);

/* @name getX
* @brief Calcula a distância percorrida pela média dos counts dos motores desde o último resetIntegrals();
* @return Distância aproximada percorrida pelo micromouse em mm desde o último resetIntegrals().
* @date alterações:
*   - 30/04/2024: criado comentário, começado a documentar. - @walger-lucas
*/
float getX();
/* @name getTheta
* @brief Calcula a rotação percorrida pela diferença dos counts dos motores desde o último resetIntegrals();
* @return Rotação aproximada percorrida pelo micromouse em radianos desde o último resetIntegrals().
* @date alterações:
*   - 30/04/2024: criado comentário, começado a documentar. - @walger-lucas
*/
float getTheta();

/* @name moveEnded
* @brief Caso todos os movimentos de auto_stop tenham terminado, retorna true. É resetado pela função resetIntegrals.
* @return Retorna true em caso de todos os movimentos de AUTO_STOP setados tenham terminado.
* @date alterações:
*   - 30/04/2024: criado comentário, começado a documentar. - @walger-lucas
*/
bool moveEnded();

/* @name activatePID
* @brief Ativa switch geral do PID
* @param on  booleano de PID ativo
* @return void
* 
* @date alterações:
*   - 30/04/2024: criado comentário, começado a documentar. - @walger-lucas
*/
void activatePID(bool on);