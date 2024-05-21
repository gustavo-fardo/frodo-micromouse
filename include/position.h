/*interface com as coordenadas x e y do micromouse e sua direção atual*/

#pragma once
#include<Arduino.h>
#include<maze.h>
//mm micromouse
namespace mm
{
    uint8_t getX();
    uint8_t getY();
    DIRECTIONS getDir();
}