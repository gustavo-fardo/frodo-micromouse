#include<states.h>
#include<buttons.h>
#include<PID.h>
#include<leds.h>

void beginState();
void walkState();

void (*baseState) () = beginState;


bool (*walkAlgorithm)();

//modo de busca atual 0 - competição 1 - bfs, 2 - dfs
uint8_t modoBusca= 0;
// modo de operação atual 0 - exploração 1 - resolução
uint8_t modoOperacao = 0;

/* beginState
* @brief estado de inicio do micromouse, lê os botões e atualiza os modos de busca e operação
* @return void
*   - 01/05/2024: criado comentário, começado a documentar. - @walger-lucas
*   - 02/05/2024: adição de interface com movements.cpp. - @walger-lucas
*/
void beginState()
{
    uint8_t buttons = readButtons();
    if(buttons == 0)
    {
        return;
    }
    delay(100);//espera 100ms para caso de double click (busy wait é td bem aqui por não estar ocorrendo PID no momento)
    buttons = readButtons();
    resetButtons();
    if(buttons == 0b01)
    {
        modoBusca = (modoBusca +1)%3;
        setLED(MB,LOW);
        setLED(MB1>>modoBusca,HIGH);
        updateLEDs();


    } else if(buttons == 0b10)
    {
        modoOperacao = (modoOperacao +1)%2;
        setLED(MO,LOW);
        setLED(MO1>>modoOperacao,HIGH);   
        updateLEDs();   

    } else if(buttons == 0b11)
    {
        //cria animação
        const uint8_t dir[3]= {LED_LEFT,LED_RIGHT,LED_FRONT};
        for(uint8_t j = 0; j<3;j++)
        {
            for(uint8_t i = 0; i<5;i++)
            {
                delay(200);
                setLED(dir[j],LOW);
                updateLEDs();
                delay(200);
                setLED(dir[j],HIGH);
                updateLEDs();
            }
        }
        delay(1000);
        setLED(LED_DIR,LOW);
        updateLEDs();
        if(modoOperacao == 1)
        {
            walkAlgorithm=executionAlgorithm;
        } else
        {
            bool (* const search[3]) () = {floodfillSearch,bfsSearch,dfsSearch};
            walkAlgorithm = search[modoBusca];
            
        }
        activatePID(true);
        setInstruction(CODES::NONE,MODES::EMPTY);
        baseState = walkState;
    }


}

/* walkState
* @brief estado de leitura de instrução e atuação, chamando os algorítimos de busca e execução
* @return void
*   - 01/05/2024: criado comentário, começado a documentar. - @walger-lucas
*   - 02/05/2024: adição de interface com movements.cpp. - @walger-lucas
*/
void walkState()
{
    if(readButtons() & 0b01)
    {
        baseState = beginState;
        activatePID(false);
    }
    resetButtons();
    if(instructMovement())
    {
        if(walkAlgorithm())
        {
            baseState = beginState;
            activatePID(false);
        }
    }

}


