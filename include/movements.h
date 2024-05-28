/* @name MOVEMENTS
   @author @walger-lucas
   @brief Funções que organizam e abstraem a movimentação do PID

   @date 02/05/2024
*/
#pragma once

typedef enum CODES
{
    NONE, //wait for new instruction
    BEGIN_SETUP, //use when starting run, will crash into back wall and then position itself correctly on the first square.
    MOVEMENT, //go forwards or Backwards
    INPLACE_ROTATION, //rotate 90° to either side or 180° by either side (inplace)
    RADIUS_ROTATION, // rotate 90° in a curve with the radius equal to the cell
} CODES;
typedef enum MODES
{
    EMPTY,
    FORWARDS, // go forward one cell (MOVEMENT)
    BACKWARDS, // go backwards one cell (MOVEMENT)
    LEFT, // rotate 90 degrees left (ANY ROTATION)
    RIGHT, // rotate 90 degrees rigth (ANY ROTATION)
    UTURN, // rotate 180 degrees (INPLACE ROTATION)
} MODES;

void setInstruction(CODES code ,MODES mode);
void setSecondInstruction(CODES code ,MODES mode);
bool instructMovement();