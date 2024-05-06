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

bool instructMovement()
{
    switch (cur_instr.instr_code)
    {
    case NONE:
        return true;
    case MOVEMENT:
        return movement();
    case INPLACE_ROTATION:
        return false;
    case RADIUS_ROTATION:
        return false;
    }
    return false;
}

bool movement()
{
    float spd = 200.0;
    switch (state)
    {
    case 0:
        setPID(PID_AUTO_STOP_X | PID_STRAIGHT | PID_USE_TOF);
        resetIntegrals();
        setXTheta(300,0);
        
        if(cur_instr.instr_mode != FORWARDS)
            spd = -spd;
        setVW(spd,0);
        state = 1;
        break;
    
    case 1:
        if(cur_instr.instr_mode == FORWARDS && wall_front)
        {
            if(dist_front_left+dist_front_right < 30.0*2)
            {
                setVW(0,0);
                return true;
            }
        } else
            return moveEnded();
        break;
    default:
        return true;
    }
    return false;
}


