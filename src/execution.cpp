#include <states.h>
#include<PID.h>
#include <floodfill.h>
#include <position.h>
#include <PID.h>
uint8_t execution_state = 0;
bool executionAlgorithm()
{
    switch (execution_state)
    {
    case 0:
        floodfill(createCoord(SIZE/2,SIZE/2),false);
        followFloodFill();
        execution_state = 1;
        break;
    
    case 1:
        if(getX() == SIZE/2 && getY() == SIZE/2)
        {
            floodfill(createCoord(0,0),false);
            execution_state = 2;
        }
        followFloodFill();
        break;
    case 2:
        if(getX() == 0 && getY() == 0)
        {
            setInstruction(INPLACE_ROTATION,UTURN);
            execution_state = 3;
        } else
        {
            followFloodFill();
        }
    
        break;
    case 3:
        activatePID(false);
        execution_state = 0;
        return true;
    }
    //TODO execução
    return false;
}