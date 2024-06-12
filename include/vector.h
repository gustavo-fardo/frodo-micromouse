#include <stdlib.h>
#include <Arduino.h>

/*
* @name push
* @brief insere um valor no array e incrementa o tamanho desse array, como uma stack
* @param array onde sera armazenado o valor
* @param size tamanho atual do array
* @param value valor a ser adicionado no vetor
*/
void push(uint8_t* array, uint8_t size, uint8_t value);

/*
* @name pop
* @brief retira um valor do array, como uma stack
* @param array onde sera armazenado o valor
* @param size tamanho atual do array
*/
uint8_t pop(uint8_t* array, uint8_t size);