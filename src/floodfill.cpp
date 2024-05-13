#include <states.h>

bool floodfillSearch()
{
    static int a = 0;
    CODES c[14]= {MOVEMENT,MOVEMENT,INPLACE_ROTATION,MOVEMENT,INPLACE_ROTATION,
                MOVEMENT,INPLACE_ROTATION, MOVEMENT, MOVEMENT,INPLACE_ROTATION,MOVEMENT,INPLACE_ROTATION,MOVEMENT,INPLACE_ROTATION};
    MODES m[14]= {FORWARDS,FORWARDS,LEFT,FORWARDS,LEFT,FORWARDS,LEFT,FORWARDS,FORWARDS,RIGHT,FORWARDS,RIGHT,FORWARDS,RIGHT};
    setInstruction(c[a%14],m[a%14]);
    a++;
    //if(a%2)
    //if(a==0)
    //{
    /*if(a%2==0)
        setInstruction(CODES::MOVEMENT,MODES::FORWARDS);
    else 
    {
        
    }
    a++;*/
    
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