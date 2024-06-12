#include<position_mutator.h>
#include<movements.h>
uint8_t x=0, y=0;
DIRECTIONS dir=U;
void setX(uint8_t _x)
{
    x = _x;
}
void setY(uint8_t _y)
{
    y= _y;
}
void setDir(DIRECTIONS _dir)
{
    dir = _dir;
}

uint8_t getX()
{
    return x;
}
uint8_t getY()
{
    return y;
}
DIRECTIONS getDir()
{
    return dir;
}
bool wallAt(DIRECTIONS dir)
{
    return getWall(sumDirection(dir,getDir()),getX(),getY());
}

bool validAdjacentCellLocal(uint8_t* data, DIRECTIONS dir, bool validUnexplored)
{
    return validAdjacentCell(data,getX(),getY(),dir,validUnexplored);
}

void goTo(DIRECTIONS dir)
{
    DIRECTIONS go = sumDirection(getDir(),dir);
    switch (go)
    {
    case U:
        setInstruction(MOVEMENT,FORWARDS);
        break;
    case L:
        setInstruction(INPLACE_ROTATION,LEFT);
        setSecondInstruction(MOVEMENT,FORWARDS);
        break;
    case R:
        setInstruction(INPLACE_ROTATION,RIGHT);
        setSecondInstruction(MOVEMENT,FORWARDS);
        break;
    case D:
        setInstruction(INPLACE_ROTATION,UTURN);
        setSecondInstruction(MOVEMENT,FORWARDS);
        break;
    }

}

uint8_t getXFromCoord(uint8_t coord)
{
    return coord & 0xF;
}
uint8_t getYFromCoord(uint8_t coord)
{
    return coord>>4;
}

uint8_t createCoord(uint8_t x, uint8_t y)
{
    return (x & 0xF) | (y << 4);
}