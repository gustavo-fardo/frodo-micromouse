#include<encoder.h>
#include<pins.h>

//positive is cw and negative is ccw
int16_t count_left=0,count_right=0;
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

void encoderCall(int16_t* count, uint8_t a_pin,uint8_t b_pin)
{
    if(digitalRead(a_pin) == digitalRead(b_pin))
        *count = *count - 1; //ccw
    else
        *count = *count + 1; //cw
}
void encoderLeft()
{
    encoderCall(&count_left,ENCODER_A_ESQ,ENCODER_B_ESQ);
}
void encoderRight()
{
    encoderCall(&count_right,ENCODER_A_DIR,ENCODER_B_DIR);
}