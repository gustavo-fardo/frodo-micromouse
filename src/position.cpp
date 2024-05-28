#include<position_mutator.h>
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