#include <vector.h>

void queue_push(uint8_t* array, uint8_t* size, uint8_t value,uint8_t max){
    array[*size] = value;
    *size = (*size+1)%max;
};

uint8_t queue_pop(uint8_t* array, uint8_t* start,uint8_t max){
    uint8_t out = array[*start];
    *start = (*start+1)%max;
    return out;
};
