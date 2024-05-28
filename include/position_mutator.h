/* parte privada de position, apenas colocar em arquivos que realmente necessitam utilizar estas funções
*/
#pragma once
#include<Arduino.h>
#include<position.h>

void setX(uint8_t x);
void setY(uint8_t y);
void setDir(DIRECTIONS dir);
