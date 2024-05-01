/* @name LEDS
* @author @walger-lucas
* @date 30/04/2024
* @paragraph Funções para interface com os Leds
*/

#ifndef _LEDS
#define _LEDS
#include <Arduino.h>

//Bits de ativaçãode cada LED
#define MB        0b01110000 // todos os leds de busca
#define MB1       0b01000000 // LED MB1
#define MB2       0b00100000 // LED MB2
#define MB3       0b00010000 // LED MB3
#define MO        0b00001100 // todos os leds de operação
#define MO1       0b00001000 //LED MO1
#define MO2       0b00000100 //LED MO2
#define LED_DIR   0b10000011 //todos os leds de direção
#define LED_LEFT  0b00000010 //LED de direção Esquerdo
#define LED_FRONT 0b00000001 //LED de direção Frontal
#define LED_RIGHT 0b10000000 //LED de direção Direito
#define LED_ALL   0b11111111 //todos os leds

/* @name setLED
* @brief seta um ou uma coleção de leds para um valor 1 ou 0, ativado ou destivado.
* @return void
* @attention juntar LEDs com LED1 | LED2 | LED3 ... etc. É necessário realizar updateLEDs() para escrever os valores após esta função.
* 
* @date alterações:
*   - 30/04/2024: criado comentário, começado a documentar. - @walger-lucas
*/
void setLED(uint8_t led, bool on);

/* @name updateLEDs
* @brief atualiza shiftRegister com os valores de LEDs dados.
* @return void
* 
* @date alterações:
*   - 30/04/2024: criado comentário, começado a documentar. - @walger-lucas
*/
void updateLEDs();

/* @name setupLEDs
* @brief faz setup dos pinos para comunicação com o shift register.
* @return void
* 
* @date alterações:
*   - 30/04/2024: criado comentário, começado a documentar. - @walger-lucas
*/
void setupLEDs();

#endif