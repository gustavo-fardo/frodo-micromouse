#include<states.h>
#include<buttons.h>
#include<PID.h>
#include<leds.h>

void beginState();
void walkState();

void (*baseState) () = beginState;

bool executionAlgorithm();
bool floodfillSearch();
bool dfsSearch();
bool bfsSearch();
bool (*walkAlgorithm)();

uint8_t modoBusca= 0;
uint8_t modoOperacao = 0;
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
        setLED(LED_DIR|LED_FRONT|LED_RIGHT,LOW);
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
        baseState = walkState;
    }


}


void walkState()
{
    if(readButtons() & 0b01)
    {
        baseState = beginState;
        activatePID(false);
    }
    resetButtons();

    ///função para controlar os movimentos
    //se busca, em algum momento ler as paredes
    // if acabou o último movimento {
    if(walkAlgorithm())
    {
        baseState = beginState;
        activatePID(false);
    }
    //}

}


bool executionAlgorithm()
{
    return false;
}
bool floodfillSearch()
{return false;}

bool dfsSearch()
{return false;}

bool bfsSearch()
{return false;}
