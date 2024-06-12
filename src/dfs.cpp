#include <states.h>
#include <tof.h>
#include <position.h>
#define NULO 0xFF
uint8_t dfs_state = 0;
DIRECTIONS last_dir = U;
bool dfsSearch()
{
    switch (dfs_state)
    {
    case 0:
        for(int i = 0; i<SIZE;i++)
        {
            for(int j = 0; j<SIZE;j++)
            {
                setCell(i,j,NULO);
            }
        }
        setCell(0,0,0);
        dfs_state = 1;
        break;
    case 1:
        uint8_t dir;
        for(uint8_t i = 0; i<4;i++)
        {
            if(validAdjacentCellLocal(&dir,(DIRECTIONS) i))
            {
                if(dir == NULO)
                {
                    last_dir = (DIRECTIONS) i;
                    goTo(last_dir);
                    dfs_state = 2;
                    return false;
                }
            }
        }
        goTo((DIRECTIONS) getCell(getX(),getY()));
        break;
    case 2:
        setCell(getX(),getY(),(uint8_t) sumDirection(D,last_dir));
        if(getX() == SIZE/2 && getY()==SIZE/2)
        {
            dfs_state = 3;
        } else
        {
            dfs_state = 1;
        }
    case 3:
        if(getX() == 0 && getY() == 0)
        {
            dfs_state = 0;
            setInstruction(INPLACE_ROTATION,UTURN);
            return true;
        }
        goTo((DIRECTIONS) getCell(getX(),getY()));

        break;
    default:
        break;
    }
    return false;
}