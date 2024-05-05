#include <states.h>

bool floodfillSearch()
{
    static int a = 0;
    if(a%2)
        setInstruction(CODES::MOVEMENT,MODES::FORWARDS);
    else
        setInstruction(CODES::MOVEMENT,MODES::BACKWARDS);
    //TODO floodfill
    return false;
}