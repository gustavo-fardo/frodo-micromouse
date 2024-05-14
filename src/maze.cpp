#include <maze.h>

#define WALL_BYTES ((SIZE)*(SIZE-1)+3)/4
#define CELL_BYTES (SIZE*SIZE+7)/8
#define CELL_COUNT SIZE*SIZE
uint8_t exploredCells[CELL_BYTES] = {0};
uint8_t wall[WALL_BYTES]= {0};
uint16_t cells[SIZE][SIZE] ={0};

void resetMaze()
{
    for(uint8_t i = 0; i< WALL_BYTES;i++)
    {
        wall[i]=0;
    }
    for(uint8_t i = 0; i< CELL_BYTES;i++)
    {
        exploredCells[i]=0;
    }
    for(uint8_t i = 0; i< SIZE;i++)
    {
        for(uint8_t j=0;j<SIZE; j++)
            cells[i][j]= 0;
    }
    setWall(R,0,0);
    exploreCell(0,0);

}

DIRECTIONS sumDirection(DIRECTIONS direction1,DIRECTIONS direction2)
{
    return (DIRECTIONS)(((uint8_t) direction1+ (uint8_t)direction2)%4);
}

void exploreCell(uint8_t x, uint8_t y)
{
    uint16_t bit = (uint16_t)y*SIZE+(uint16_t)x;
    uint16_t byte = bit/8;
    bit = bit - byte*8;
    exploredCells[byte] |= 0b1<<bit;
}

bool cellExplored(uint8_t x, uint8_t y)
{
    uint16_t bit = (uint16_t)y*SIZE+(uint16_t)x;
    uint16_t byte = bit/8;
    bit = bit - byte*8;
    return (exploredCells[byte] & 0b1<<bit)!=0;
}

bool getWall(DIRECTIONS direction, uint8_t x, uint8_t y)
{
    if((x==0 && direction ==L)
    || (x==SIZE-1 && direction ==R)
    || (y==0 && direction ==D)
    || (y==SIZE-1 && direction ==U))
        return true;
    
    if(direction == L)
    {
        return getWall(R,x-1,y);
        
    }
    if(direction == D)
    {
        return getWall(U,x,y-1);
    }

    uint16_t bit = (uint16_t)x*SIZE + (uint16_t)y;
    if(direction == R)
        bit += SIZE*(SIZE-1);
    uint16_t byte = bit/8;
    bit = bit - byte*8;
    return (wall[byte] & 0b1<<bit)!=0;
}

void setWall(DIRECTIONS direction, uint8_t x, uint8_t y)
{
    if((x==0 && direction ==L)
    || (x==SIZE-1 && direction ==R)
    || (y==0 && direction ==D)
    || (y==SIZE-1 && direction ==U))
        return;
    if(direction == L)
    {
        setWall(R,x-1,y);
        return;
    }
    if(direction == D)
    {
        setWall(U,x,y-1);
        return;
    }
    bool explored = cellExplored(x,y);
    uint8_t x_= x+1;
    uint8_t y_= y+1;


    //caso esta parede já tenha sido explorada, não sobrescrever
    if((direction == R && (explored || cellExplored(x_,y)))
    || (direction == U && (explored || cellExplored(x,y_))))
    {
        return;
    }

    // se Direita, x está entre 0 e SIZE-2, e y está entre 0 e SIZE-1
    // se Cima, x está entre 0 e SIZE-1, e y está entre 0 e SIZE-2
    
    uint16_t bit = (uint16_t)x*SIZE + (uint16_t)y;
    if(direction == R)
        bit += SIZE*(SIZE-1);
    uint16_t byte = bit/8;
    bit = bit - byte*8;
    wall[byte] |= 0b1<<bit;
}

void setCell(uint8_t x, uint8_t y, uint16_t value)
{
    cells[x][y]= value;
}
uint16_t getCell(uint8_t x, uint8_t y)
{
    return cells[x][y];
}

void seeWalls(bool front, bool left, bool right, DIRECTIONS direction, uint8_t x, uint8_t y)
{
    if(getWall(direction,x,y))
        return;
    uint8_t front_x= getFrontX(direction,x), front_y = getFrontY(direction,y);
    if(front)
        setWall(sumDirection(direction,U),front_x,front_y);
    if(left)
        setWall(sumDirection(direction,L),front_x,front_y);
    if(right)
        setWall(sumDirection(direction,R),front_x,front_y);
    exploreCell(front_x,front_y);


}

uint8_t getFrontX(DIRECTIONS direction, uint8_t x)
{
    switch (direction)
    {
    case R:
        return x+1;
        break;
    case L:
        return x-1;
        break;
    
    default:
        return 0;
        break;
    }
}
uint8_t getFrontY(DIRECTIONS direction, uint8_t y)
{
    switch (direction)
    {
    case U:
        return y+1;
        break;
    case D:
        return y-1;
        break;
    
    default:
        return 0;
        break;
    }
}