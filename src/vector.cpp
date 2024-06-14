#include <vector.h>

void push(uint8_t* array, uint8_t& size, uint8_t value){
    array[size] = value;
    size++;
};

uint8_t pop(uint8_t* array, uint8_t& size){
    size--;
    return array[size];
};
