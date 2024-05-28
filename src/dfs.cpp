#include <states.h>
#include <tof.h>
#include <position.h>
bool dfsSearch()
{
    //follow right wall
    if(!wallAt(R))
    {
        setInstruction(INPLACE_ROTATION,RIGHT);
        setSecondInstruction(MOVEMENT,FORWARDS);
    } else if(!wallAt(U))
    {
        setSecondInstruction(MOVEMENT,FORWARDS);
    } else if(!wallAt(L))
    {
        setInstruction(INPLACE_ROTATION,LEFT);
        setSecondInstruction(MOVEMENT,FORWARDS);
    } else
    {
        setInstruction(INPLACE_ROTATION,RIGHT);
        setInstruction(INPLACE_ROTATION,RIGHT);
    }


    return false;
}