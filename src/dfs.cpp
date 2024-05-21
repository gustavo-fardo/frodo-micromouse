#include <states.h>
#include <tof.h>

bool dfsSearch()
{
    if(!wall_front)
        setInstruction(MOVEMENT,FORWARDS);
    else
        setInstruction(INPLACE_ROTATION,LEFT);

    return false;
}