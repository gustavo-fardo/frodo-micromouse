/* parte privada de position, apenas colocar em arquivos que realmente necessitam utilizar estas funções
*/
#pragma once
#include<Arduino.h>
#include<position.h>


/* @name setX
* @param x coordenada x a ser setada, do micromouse.
*/
void setX(uint8_t x);
/* @name setY
* @param y coordenada y a ser setada, do micromouse.
*/
void setY(uint8_t y);

/* @name setDir
* @param dir Direção a ser setada, do micromouse.
*/
void setDir(DIRECTIONS dir);
