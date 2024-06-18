#include<movements.h>
#include <Arduino.h>
#include<PID.h>
#include <tof.h>
#include <maze.h>
#include <position_mutator.h>

typedef struct Instruction
{
    //stores the code for the instructions of movement
    CODES instr_code;
    //stores the mode in witch this instruction will be executed, such as backwards forwards, rotate left, rotate right
    MODES instr_mode;
} Instruction;
Instruction cur_instr= {CODES::NONE,MODES::EMPTY};
bool two_instructions = false;
Instruction next_instr = {CODES::NONE,MODES::EMPTY};
uint8_t state=0;
void setInstruction(CODES code ,MODES mode)
{
    cur_instr.instr_code = code;
    cur_instr.instr_mode = mode;
    two_instructions = false;
    state=0;
}

void setSecondInstruction(CODES code ,MODES mode)
{
    next_instr.instr_code = code;
    next_instr.instr_mode = mode;
    two_instructions = true;
}


bool movement();
bool rotation();
bool begin_setup();

bool instructMovement()
{
    bool inst = false;
    switch (cur_instr.instr_code)
    {
    case NONE:
        setVW(0,0);
        inst= true;
        break;
    case MOVEMENT:
        inst = movement();
        break;
    case INPLACE_ROTATION:
        inst = rotation();
        break;
    case RADIUS_ROTATION:
        inst = false;
        break;
    case BEGIN_SETUP:
        inst = begin_setup();
        break;
    }
    if(inst && two_instructions)
    {
        two_instructions = false;
        setInstruction(next_instr.instr_code,next_instr.instr_mode);
        inst = instructMovement();
        
    }
    return inst;
}


bool begin_setup()
{
    switch (state)
    {
    case 0:
        setPID(PID_STRAIGHT);
        resetIntegrals();
        resetCounts();
        resetFinished();
        setVW(-80,0);
        delay(2000);
        setPID(PID_STRAIGHT|PID_AUTO_STOP_X);
        resetIntegrals();
        setXTheta(45,0);
        setVW(150,0);
        state = 1;
        return false;
        break;
    case 1:
        if( moveEnded())
        {
            resetIntegrals();
            resetCounts();
            resetFinished();
        }
        break;
    
    default:
        break;
    }
    return false;
}

bool movement()
{
    //pare movimento se uma parede estiver a menos de 1.5 cm dos sensores frontais
    if(cur_instr.instr_mode == FORWARDS && wall_front && state != 0)
    {
            if(dist_front_left+dist_front_right < 65.0*2)
            {
                setVW(0,0);
                resetIntegrals();
                setPID(PID_DEFAULT);
                return true;
            }
    }
    
    float spd = 250.0; 
    switch (state)
    {
    case 0:
        setPID(PID_STRAIGHT|PID_AUTO_STOP_X);
        
        normalizeCounts();
        resetFinished();
        setX(getFrontX(getDir(),getX()));
        setY(getFrontY(getDir(),getY()));

        
        
        setXTheta(15,0);
    
        if(cur_instr.instr_mode != FORWARDS)
            spd = -spd;
        setVW(spd,0);
        state = 10;
        break;
    
    case 1:
        
        if(moveEnded())
        {
            
            seeWalls(wall_front,wall_left,wall_right,getDir(),getX(),getY());
            setXTheta(175,0);
            setVW(spd,0);
            resetFinished();
            if(wallAt(U))
                setPID(PID_STRAIGHT|PID_AUTO_STOP_X |PID_USE_TOF_FRONT);
            else
                setPID(PID_STRAIGHT|PID_AUTO_STOP_X|PID_USE_TOF_SIDES);
            
            state = 2;
        }
        break;
    case 2:
        return moveEnded();
        break;
    case 10:
        if(moveEnded())
        {

            state = 1;
            resetFinished();
            setXTheta(100,0);
            setVW(spd,0);
            setPID(PID_STRAIGHT|PID_AUTO_STOP_X|PID_USE_TOF_SIDES);


        }
        break;
    default:
        return true;
    }
    return false;
}


bool rotation()
{
    float spd = 4;
    switch (state)
    {
    case 0:
        resetIntegrals();
        resetFinished();
        resetCounts();
        if(dist_front_left+dist_front_right < 130.0*2)
        {
                setPID(PID_STRAIGHT |PID_USE_TOF_FRONT);
                setVW(200,0);
                state = 2;
   
            break;
        }
        state = 4;
        break;
    
    case 1:
            if(moveEnded())
            {
                resetIntegrals();
                resetFinished();
                resetCounts();
                setPID(PID_STRAIGHT |PID_AUTO_STOP_X);
                setVW(-200,0);
                setXTheta(9,0);

                switch (cur_instr.instr_mode)
                {
                case LEFT:
                    setDir(sumDirection(getDir(),L));
                    break;
                
                case RIGHT:
                    setDir(sumDirection(getDir(),R));
                    break;
                case UTURN:
                    setDir(sumDirection(getDir(),D));
                    break;
                default:
                    break;
                }
                
                state = 3;
            }
        break;
    case 2:
        if(dist_front_left+dist_front_right < 65.0*2)
        {
                
                resetIntegrals();
                resetCounts();
                resetFinished();
                setPID(PID_USE_TOF_FRONT |PID_STRAIGHT);
                setVW(0,0);
                state = 4;
        }
        break;
    case 3:
            
            if(moveEnded())
            {
                    resetIntegrals();
                    resetFinished();
                    resetCounts();
                    setVW(0,0);
                
                return true;
            }
        break;
    case 4:
        setPID(PID_AUTO_STOP_THETA|PID_INPLACE);
        if(cur_instr.instr_mode == UTURN)
            setXTheta(0,PI); 
        else  
        setXTheta(0,PI/2);
        
        if(cur_instr.instr_mode == RIGHT)
            spd = -spd;
        setVW(0,spd);
        state = 1;
        break;
    default:
        return true;
    }
    return false;
}


