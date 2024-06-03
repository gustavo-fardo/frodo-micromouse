#pragma once
#include <Arduino.h>

#define SIZE 4

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

/*
* @name setWall
* @brief adiciona uma parede na posição, caso não esteja em uma célula explorada
* @param direction direção para onde deve ser colocada a parede
* @param x coordenada x da célula
* @param y coordenada y da célula
*/
void setWall(DIRECTIONS direction, uint8_t x, uint8_t y);

/*
* @name cellExplored
* @brief retorna caso a célula já tenha sido explorada
* @param x coordenada x da célula
* @param y coordenada y da célula
*/
bool cellExplored(uint8_t x, uint8_t y);

/*
* @name exploreCell
* @brief explora célula
* @param x coordenada x da célula
* @param y coordenada y da célula
*/
void exploreCell(uint8_t x, uint8_t y);

/*
* @name setCell
* @brief coloca valor a célula escolhida
* @param x coordenada x da célula
* @param y coordenada y da célula
* @value 2 bytes de informação correspondentes a célula escolhida
*/
void setCell(uint8_t x, uint8_t y, uint8_t value);

/*
* @name getCell
* @brief retorna valor armazenado na célula
* @param x coordenada x da célula
* @param y coordenada y da célula
*/
uint8_t getCell(uint8_t x, uint8_t y);

/*
* @name getFrontX
* @brief retorna valor de x caso ande em uma unidade para a direção dada
* @param direction direção para andar
* @param x coordenada x da célula
*/
uint8_t getFrontX(DIRECTIONS direction, uint8_t x);

/*
* @name getFrontY
* @brief retorna valor de y caso ande em uma unidade para a direção dada
* @param direction direção para andar
* @param y coordenada y da célula
*/
uint8_t getFrontY(DIRECTIONS direction, uint8_t x);

/*
* @name seeWalls
* @brief atualiza paredes nos buffers, e explora a célula a frente da atual
* @param front há uma parede frontal
* @param left há uma parede à esquerda
* @param right há uma parede à direita
* @param direction direção para onde deve ser colocada a parede
* @param x coordenada x da célula
* @param y coordenada y da célula
*/
void seeWalls(bool front, bool left, bool right, DIRECTIONS direction, uint8_t x, uint8_t y);



/*
* @name sumDirection
* @brief retorna se na célula dada, na direção dada existe uma parede
* @param direction direção para onde deve ser observada a existência de parede
* @param x coordenada x da célula
* @param y coordenada y da célula
*/
DIRECTIONS sumDirection(DIRECTIONS direction1,DIRECTIONS direction2);

/*
* @name resetMaze
* @brief Reseta buffers e explora a célula 0,0, adicionando uma parede obrigatória a direita.
*/
void resetMaze();

/*
* @name validAdjacentCell
* @brief retorna se a célula adjacente é válida a ser explorada, e sua entrada na matriz de custos,
* @brief ser valido a ser explorado significa que não há uma parede entre o local atual e a direção desejada, ou que não tenha sido explorado caso validUnexplored = false
* @param data ponteiro para onde os dados da célula devem ser guardados.
* @param x coordenada x
* @param y coordenada y
* @param dir direção
* @param validUnexplored flag que caso setada considera que células não exploradas são validas.
*/
bool validAdjacentCell(uint8_t* data,uint8_t x, uint8_t y, DIRECTIONS dir, bool validUnexplored = true);
