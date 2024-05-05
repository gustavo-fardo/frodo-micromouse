/* @name ENCODERS
* @author @walger-lucas
* @date 30/04/2024
* @paragraph Funções para interface com os encoders dos motores
*/
#ifndef _ENCODER
#define _ENCODER
#include <Arduino.h>

//COUNTS PER FULL ROTATION
#define COUNTS_PER_ROT 406.3f

//TOTAL COUNTS LEFT ROTATION AND RIGHT ROTATION
extern volatile int32_t count_left,count_right;


/* @name getV1
* @brief calcula a velocidade em mm/s da roda esquerda v1.
* @return velocidade em mm/s da roda esquerda.
* @attention caso não haja interrupts de encoder nos últimos 10ms, retorna velocidade 0
* 
* @date alterações:
*   - 30/04/2024: criado comentário, começado a documentar. - @walger-lucas
*/
float getV1();

/* @name getV2
* @brief calcula a velocidade em mm/s da roda esquerda v2.
* @return velocidade em mm/s da roda direita.
* @attention caso não haja interrupts de encoder nos últimos 10ms, retorna velocidade 0
* 
* @date alterações:
*   - 30/04/2024: criado comentário, começado a documentar. - @walger-lucas
*/
float getV2();

/* @name setupEncoders
* @brief faz setup dos pinos e interrupts dos Encoders.
* @return void
* 
* @date alterações:
*   - 30/04/2024: criado comentário, começado a documentar. - @walger-lucas
*/
void setupEncoders();

#endif