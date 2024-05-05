#include<encoder.h>
#include<pins.h>
#include<Arduino.h>
#include<constants.h>

//positive is cw and negative is ccw
volatile int32_t count_left=0,count_right=0;

//microseconds of last encoder interrupt, left and right
volatile unsigned long micros1=1,micros2=1;

//delta time in micros of last pair of interrupts
volatile long diff1=10000000,diff2=10000000;

void encoderCall(int16_t* count, uint8_t a_pin,uint8_t b_pin);
void encoderLeft();
void encoderRight();

void setupEncoders()
{
    pinMode(ENCODER_A_DIR,INPUT);
    pinMode(ENCODER_A_ESQ,INPUT);
    pinMode(ENCODER_B_DIR,INPUT);
    pinMode(ENCODER_B_ESQ,INPUT);
    attachInterrupt(digitalPinToInterrupt(ENCODER_A_ESQ),encoderLeft,CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENCODER_A_DIR),encoderRight,CHANGE);
}

/* @name encoderCall
* @brief handler para giro do encoder, atualizando variaveis globais
* @return void
* 
* @date alterações:
*   - 30/04/2024: criado comentário, começado a documentar. - @walger-lucas
*/
void encoderCall(volatile int32_t* count,volatile long* dif,volatile unsigned long* mics, uint8_t a_pin,uint8_t b_pin)
{
    bool negative = false;
    if(digitalRead(a_pin) == digitalRead(b_pin))
    {
        *count = *count - 1; //ccw
        negative = true;
    }
    else
        *count = *count + 1; //cw

    unsigned long aux = micros();
    *dif = (aux - *mics)*((negative)? -1 : 1);
    *mics = aux;
}
void encoderLeft()
{
    encoderCall(&count_left,&diff1,&micros1,ENCODER_A_ESQ,ENCODER_B_ESQ);
}
void encoderRight()
{
    encoderCall(&count_right,&diff2,&micros2,ENCODER_A_DIR,ENCODER_B_DIR);
}


float getV1()
{
    if(micros() -micros1> 10000)
        return 0;
    return 1000000.0f/406.9f/(float) diff1*DIAMETER*3.1415;
}
float getV2()
{
    if(micros() -micros2> 10000)
        return 0;
    return 1000000.0f/406.9f/(float) diff2*DIAMETER*3.1415;
}