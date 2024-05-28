/* @name TOF
* @author @walger-lucas
* @date 30/04/2024
* @paragraph Funções para interface geral com os TOFs.
*/
#ifndef _TOF
#define _TOF
#include <Arduino.h>

// WALL DISTANCE OFFSET CONSTANTS (mm)
#define TOF_OFFSET 10

//variáveis que retornam as saídas dos sensores em mm, respectivamente esquerda, direita, frente esquerda e frente direita
extern float dist_left, dist_right, dist_front_left, dist_front_right;
//bools que retornam caso foi percebido uma parede, respectivamente, a esquerda, a frente e a direita
extern bool wall_left,wall_front,wall_right;


/* @name setupTOF
* @brief Faz setup do I2C e separação entre os sensores TOF, além de inicializá-los.
* @return void
* @date alterações:
*   - 30/04/2024: criado comentário, começado a documentar. - @walger-lucas
*/
void setupTOF();


/* @name readTOF
* @brief Atualiza variáveis globais dist_left, dist_right, dist_front_left e dist_front_right com os dados sáidos dos sensores. 
* Também atualiza flags wall_left, wall_front e wall_right, a partir da distância para cada uma dessas direções e as constantes em constants.h
* @return void
* @attention todos os valores dos sensores possuem seu valor diminuido em TOF_OFFSETS
* @date alterações:
*   - 30/04/2024: criado comentário, começado a documentar. - @walger-lucas
*/
void readTOF();


#endif