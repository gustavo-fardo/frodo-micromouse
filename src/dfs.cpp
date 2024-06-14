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
        //seta tudo pra NULO
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
        //encontra um que nao esta nulo
        for(uint8_t i = 0; i<4;i++)
        {
            if(validAdjacentCell(&dir,getX(),getY(),(DIRECTIONS) i,true))
            {
                if(dir == NULO)
                {
                    last_dir = (DIRECTIONS) i;
                    goTo(last_dir);
                    setCell(getFrontX(last_dir,getX()),getFrontY(last_dir,getY()),(last_dir+2)%4);
                    dfs_state = 2;
                    return false;
                }
            }
        }
        //goTo(U);
        //vai pro antecessor
        goTo((DIRECTIONS) getCell(getX(),getY()));
        //setInstruction(NONE,EMPTY);
        break;
    case 2:
        //se no meio retorna se nao analiza dnv
        setInstruction(NONE,EMPTY);
        if(getX() == SIZE/2 && getY()==SIZE/2)
        {
            dfs_state = 3;
        } else
        {
            dfs_state = 1;
        }
        break;
    case 3:
        //ao chegar ao inicio terminar, se nao, volte para trás
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