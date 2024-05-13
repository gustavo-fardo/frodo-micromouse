#pragma once
#include <Arduino.h>

#define SIZE 7

typedef enum DIRECTIONS
{
    //up
    U = 0,
    //left
    L = 1, 
    //down
    D = 2,
    //right
    R = 3
} DIRECTIONS;
/*
* @name getWall
* @brief retorna se na célula dada, na direção dada existe uma parede
* @param direction direção para onde deve ser observada a existência de parede
* @param x coordenada x da célula
* @param y coordenada y da célula
*/
bool getWall(DIRECTIONS direction, uint8_t x, uint8_t y);

void setWall(DIRECTIONS direction, uint8_t x, uint8_t y);

bool cellExplored(uint8_t x, uint8_t y);

void exploreCell(uint8_t x, uint8_t y);

void setCell(uint8_t x, uint8_t y, uint16_t value);
uint16_t getCell(uint8_t x, uint8_t y);



/*
* @name sumDirection
* @brief retorna se na célula dada, na direção dada existe uma parede
* @param direction direção para onde deve ser observada a existência de parede
* @param x coordenada x da célula
* @param y coordenada y da célula
*/
DIRECTIONS sumDirection(DIRECTIONS direction1,DIRECTIONS direction2);

void resetMaze();