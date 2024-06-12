/*interface com as coordenadas x e y do micromouse e sua direção atual*/

#pragma once
#include<Arduino.h>
#include<maze.h>
//mm micromouse


/* @name getX
* @returns retorna coordenada x do micromouse
*/
uint8_t getX();
/* @name getY
* @returns retorna coordenada y do micromouse
*/
uint8_t getY();
/* @name getDir
* @returns retorna direção do micromouse
*/
DIRECTIONS getDir();
/* @name wallAt
* @returns retorna se há uma parede na direção dada, do micromouse (considerando a direção local do carrinho)
* @param dir direção para onde se quer saber se há uma parede.
*/
bool wallAt(DIRECTIONS dir);

/*
* @name validAdjacentCellLocal
* @brief retorna se a célula adjacente é válida a ser explorada, e sua entrada na matriz de custos,
* @brief ser valido a ser explorado significa que não há uma parede entre o local atual e a direção desejada, ou que não tenha sido explorado caso validUnexplored = false
* @attention mesma função que validAdjacentCell, mas levando as variáveis x, y do micromouse, e a direção local em relação a direção do micromouse.
* @param data ponteiro para onde os dados da célula devem ser guardados.
* @param dir direção local ao micromouse
* @param validUnexplored flag que caso setada considera que células não exploradas são validas.
*/
bool validAdjacentCellLocal(uint8_t* data, DIRECTIONS dir, bool validUnexplored= true);


/*
* @name goTo
* @brief seta instrucoes para ir para a direção dada, em uma coordenada global, ou seja up sempre será y+1, etc.
* @param dir Direção global a ir
*/
void goTo(DIRECTIONS dir);

uint8_t getXFromCoord(uint8_t coord);
uint8_t getYFromCoord(uint8_t coord);
uint8_t createCoord(uint8_t x, uint8_t y);