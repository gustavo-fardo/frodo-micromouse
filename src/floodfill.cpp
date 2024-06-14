#include <states.h>
#include <tof.h>
#include <position.h>
#include <maze.h>
#include <vector.h>
#include <PID.h>
#include<floodfill.h>

uint8_t floodfill_state = 0;
bool floodfillSearch();


bool floodfillSearch()
{
    uint8_t center;
    switch(floodfill_state){
        case 0:
            if(getX() == SIZE/2  && getY() == SIZE/2){
                floodfill_state = 1;
                return false;
            }
            center = createCoord(SIZE/2, SIZE/2);
            floodfill(center);
            followFloodFill();
            break;
        case 1:
            if(getX() == 0  && getY() == 0){
                floodfill_state = 2;
                setInstruction(INPLACE_ROTATION,UTURN);
                return false;
            }
            center = createCoord(0, 0);
            floodfill(center);
            followFloodFill();
            break;
        case 2:
            floodfill_state = 0;
            activatePID(false);
            return true;
            
            break;
    }
    
    return false;
}
// Preencha matriz
void floodfill(uint8_t center, bool isValidUnexplored){
    uint8_t array[SIZE*SIZE], size = 0;
    for(uint8_t i = 0; i < SIZE; i++){
        for(uint8_t j = 0; j < SIZE; j++){
            setCell(i, j, 255);
        }
    }
    setCell(getXFromCoord(center), getYFromCoord(center), 0);
    push(array, size, center);
    while(size > 0){
        uint8_t centroide = pop(array, size), isValid;
        for(uint8_t i = 0; i < 4; i++){
            if(validAdjacentCell(&isValid, getXFromCoord(centroide), getYFromCoord(centroide), (DIRECTIONS)i ,isValidUnexplored) 
            && isValid > getCell(getXFromCoord(centroide), getYFromCoord(centroide))){
                uint8_t newCord = createCoord(getFrontX((DIRECTIONS)i, getXFromCoord(centroide)), getFrontY((DIRECTIONS)i, getYFromCoord(centroide)));
                setCell(getXFromCoord(newCord), getXFromCoord(newCord), (getCell(getXFromCoord(centroide), getYFromCoord(centroide)) + 1));                
                push(array, size, newCord);
            }
        }
    }

    // 255 255 255
    // 255  0  255
    // 255 255 255
    // Verifica as celulas entorno do centro, se não houver parede, atribui peso 1
    // A partir das celulas de peso 1, preencher com +1
}

void followFloodFill(bool validUnexplored)
{
    uint8_t value = 255, data;
    DIRECTIONS directions;
    for(uint8_t i = 0; i < 4; i++){
        if(validAdjacentCellLocal(&data,(DIRECTIONS)i,validUnexplored)){
            if (data < value){
                directions = (DIRECTIONS)i;
                value = data;
            } 
        }
    }
    goTo(directions);

}