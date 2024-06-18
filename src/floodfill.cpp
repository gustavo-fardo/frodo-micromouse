#include <states.h>
#include <tof.h>
#include <position.h>
#include <maze.h>
#include <vector.h>
#include <PID.h>
#include<floodfill.h>
#include<leds.h>

uint8_t floodfill_state = 0;
bool floodfillSearch();


bool floodfillSearch()
{
    uint8_t center;
    switch(floodfill_state){
        case 0:

            if(getX() == SIZE/2  && getY() == SIZE/2){
                floodfill_state = 1;
            } else{
                center = createCoord(SIZE/2, SIZE/2);
                floodfill(center,true);
                followFloodFill(true);
                return false;
            }
            
        case 1:
            if(getX() == 0  && getY() == 0){
                floodfill_state = 2;
                setInstruction(INPLACE_ROTATION,UTURN);
                return false;
            }
            center = createCoord(0, 0);
            floodfill(center,true);
            followFloodFill(true);
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
uint8_t array[SIZE*SIZE], size=0, start = 0;
void floodfill(uint8_t center, bool isValidUnexplored){
    size = 0;
    start = 0;
    
    for(uint8_t i = 0; i < SIZE; i++){
        for(uint8_t j = 0; j < SIZE; j++){
            setCell(i, j, 0xFF);
        }
    }
    setCell(getXFromCoord(center), getYFromCoord(center), 0);
    queue_push(array,&size,0,SIZE*SIZE);

    while(size-start != 0){
        uint8_t centroide=queue_pop(array,&start,SIZE*SIZE);
        uint8_t isValid;
        uint8_t xcent = getXFromCoord(centroide);
        uint8_t ycent = getYFromCoord(centroide);
        for(uint8_t i = 0; i < 4; i++){

            if(validAdjacentCell(&isValid, xcent, ycent, (DIRECTIONS)i ,isValidUnexplored) 
            && isValid > getCell(xcent, ycent)){
                uint8_t xfront = getFrontX((DIRECTIONS)i,xcent);
                uint8_t yfront = getFrontY((DIRECTIONS)i,ycent);
                uint8_t newCord = createCoord(xfront, yfront);
                setCell(xfront, yfront, getCell(xcent,ycent) + 1);                
                queue_push(array,&size,newCord,SIZE*SIZE);
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
    uint8_t value = 0xFF, data;
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