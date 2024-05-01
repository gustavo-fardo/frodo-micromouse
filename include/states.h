/* @name STATES
* @author @walger-lucas
* @date 30/04/2024
* @paragraph Interface com a state_machine
*/

#pragma once
#include <Arduino.h>

// PONTEIRO PARA A FUNÇÃO DE ESTADO BASE QUE RECEBE BOTÕES CLICADOS ATUALMENTE
extern void (*baseState) ();