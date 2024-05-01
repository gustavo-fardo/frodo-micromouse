/* @name BUTTONS
* @author @walger-lucas
* @date 30/04/2024
* @paragraph Funções para interface com os botões
*/

#ifndef _BUTTONS
#define BUTTONS
#include<Arduino.h>
/* @name setupButtons
* @brief Faz setup dos pinos de botões e dos interrupts ligados a eles.
* @return void
* 
* @date alterações:
*   - 30/04/2024: criado comentário, começado a documentar. - @walger-lucas
*/
void setupButtons();


/* @name readButtons
* @brief Informa botões clicados desde o último resetButtons()
* @return Byte com os 2 bits iniciais informando se SW0 e SW1, respectivamente, sofreram um clique, FALLING EDGE, desde o último resetButtons.
* 
* @date alterações:
*   - 30/04/2024: criado comentário, começado a documentar. - @walger-lucas
*/
uint8_t readButtons();

/* @name resetButtons()
* @brief reseta byte de botões clicados, dando acknowledge nos botões anteriores dados.
* @return void
* @date alterações:
*   - 30/04/2024: criado comentário, começado a documentar. - @walger-lucas
*/
void resetButtons();
#endif