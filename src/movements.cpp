#include<movements.h>
#include <Arduino.h>
#include<PID.h>
#include <tof.h>
typedef struct Instruction
{
    //stores the code for the instructions of movement
    uint8_t instr_code;
    //stores the mode in witch this instruction will be executed, such as backwards forwards, rotate left, rotate right
    uint8_t instr_mode;
} Instruction;
Instruction cur_instr= {CODES::NONE,MODES::EMPTY};
uint8_t state=0;
void setInstruction(CODES code ,MODES mode)
{
    cur_instr.instr_code = code;
    cur_instr.instr_mode = mode;
    state=0;
}

bool movement();
bool rotation();
bool begin_setup();

bool instructMovement()
{
    switch (cur_instr.instr_code)
    {
    case NONE:
        setVW(0,0);
        return true;
    case MOVEMENT:
        return movement();
    case INPLACE_ROTATION:
        return rotation();
    case RADIUS_ROTATION:
        return false;
    case BEGIN_SETUP:
        return begin_setup();
    }
    return false;
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
        setVW(-150,0);
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
    if(cur_instr.instr_mode == FORWARDS && wall_front)
    {
            if(dist_front_left+dist_front_right < 30.0*2)
            {
                setVW(0,0);
                resetIntegrals();
                setPID(PID_DEFAULT);
                return true;
            }
    }

    float spd = 300.0;
    switch (state)
    {
    case 0:
        setPID(PID_STRAIGHT|PID_AUTO_STOP_X);
        normalizeCounts();
        setXTheta(143,0);
        
        if(cur_instr.instr_mode != FORWARDS)
            spd = -spd;
        setVW(spd,0);
        state = 1;
        break;
    
    case 1:

        return moveEnded();
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
        setPID(PID_AUTO_STOP_THETA|PID_INPLACE);
        resetIntegrals();
        resetFinished();
        resetCounts();
        if(cur_instr.instr_mode== UTURN)
            setXTheta(0,3.1416);
        else if(cur_instr.instr_mode== LEFT)
            //setXTheta(0,1.4318);
            setXTheta(0,3.1416/2);
        else
            setXTheta(0,3.1416/2);
        
        if(cur_instr.instr_mode != LEFT)
            spd = -spd;
        setVW(0,spd);
        state = 1;
        break;
    
    case 1:
            if(moveEnded())
            {
                resetIntegrals();
                resetFinished();
                resetCounts();
                return true;
            } else
            {
                return false;
            }
        break;
    default:
        return true;
    }
    return false;
}


