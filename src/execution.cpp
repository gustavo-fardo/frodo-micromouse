#include <states.h>
#include<PID.h>
bool executionAlgorithm()
{
    setPID(PID_STRAIGHT | PID_USE_TOF_SIDES);
    //TODO execução
    return false;
}