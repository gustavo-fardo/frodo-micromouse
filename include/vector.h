#include <stdlib.h>
#include <Arduino.h>

/*
* @name push
* @brief insere um valor no array e incrementa o tamanho desse array, como uma queue
* @param array onde sera armazenado o valor
* @param size tamanho atual do array
* @param value valor a ser adicionado no vetor
*/
void queue_push(uint8_t* array, uint8_t* size, uint8_t value,uint8_t max);

/*
* @name pop
* @brief retira um valor do array, como uma queue
* @param array onde sera armazenado o valor
* @param size tamanho atual do array
*/
uint8_t queue_pop(uint8_t* array, uint8_t* start,uint8_t max);