#include<encoder.h>
#include<pins.h>
#include<Arduino.h>
#include<constants.h>
//positive is cw and negative is ccw
int32_t count_left=0,count_right=0;
unsigned long micros1=1,micros2=1;
unsigned long diff1=1,diff2=1;
float f1=0,f2=0;
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

void encoderCall(int32_t* count,unsigned long* dif,unsigned long* mics, uint8_t a_pin,uint8_t b_pin)
{
    if(digitalRead(a_pin) == digitalRead(b_pin))
        *count = *count - 1; //ccw
    else
        *count = *count + 1; //cw

    unsigned long aux = micros();
    *dif = aux - *mics;
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
    return 1000000.0f/406.9f/(float) diff1*DIAMETER;
}
float getV2()
{
    return 1000000.0f/406.9f/(float) diff2*DIAMETER;
}