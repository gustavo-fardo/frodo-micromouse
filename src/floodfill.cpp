#include <states.h>

bool floodfillSearch()
{
    static int a = 0;
    //if(a%2)
    //if(a==0)
    //{
    if(a%2==0)
        setInstruction(CODES::MOVEMENT,MODES::FORWARDS);
    else 
    {
        a++;
        return true;
    }
    a++;
    
    //} else
    //{
    //    setInstruction(CODES::NONE,MODES::EMPTY);
    //}
    //a++;
    //else
       // setInstruction(CODES::MOVEMENT,MODES::BACKWARDS);
    //TODO floodfill
    return false;
}