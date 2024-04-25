#include <PID.h>
#include <pins.h>
#include <constants.h>
#include <encoder.h>
#include <math.h>
#include <Arduino.h>
#define DIAMETER_INVERSED 1/DIAMETER
#define DISTANCE_WHEELS_INVERSED 1/DISTANCE_WHEELS
#define INVERSE_COUNTS_PER_ROT 1/COUNTS_PER_ROT
float ideal_f1=0,ideal_f2=0;//in Hz
void motor(uint8_t m_plus,uint8_t m_minus, float mod);
void setVW(float v, float w) //mm/s and rads/s
{
    float _v = v*DIAMETER_INVERSED;
    float _w = w*DIAMETER_INVERSED*DIAMETER_INVERSED*DISTANCE_WHEELS_INVERSED;
    float rotation_bias;
    if(w<0)
        rotation_bias = -sqrt(-_w)*0.5;
    else
        rotation_bias = sqrt(_w)*0.5;
    
    ideal_f1 = _v + rotation_bias;
    ideal_f2 = _v - rotation_bias;
}
float e1,e2;
float integral1=0,integral2=0;
float calcHz(int16_t* count)
{
    float f = *count*1000*INVERSE_COUNTS_PER_ROT;
    *count = 0;
    return f;
}

void PID()
{
    float f1,f2;
    float mod1,mod2;
    f1 = calcHz(&count_left);
    f2 = calcHz(&count_right);
    float e1n=ideal_f1-f1,e2n=ideal_f2-f2;
    integral1 += e1n;
    integral2 += e2n;

    
    mod1 = e1n*Kp + (e1n- e1)*1000.0*Kd + integral1*0.001*Ki;
    mod2 = e2n*Kp + (e2n - e2)*1000.0*Kd + integral2*0.001*Ki;

    if(ideal_f1 == 0.0)
        motor(MOTOR_ESQ_PLUS,MOTOR_ESQ_MINUS,0);
    if(ideal_f2 == 0.0)
        motor(MOTOR_DIR_PLUS,MOTOR_DIR_MINUS,0);
    motor(MOTOR_ESQ_PLUS,MOTOR_ESQ_MINUS,mod1);
    motor(MOTOR_DIR_PLUS,MOTOR_DIR_MINUS,mod2);

    
}

//SETS PWM of MOTOR
void motor(uint8_t m_plus,uint8_t m_minus, float mod)
{
    if(mod == 0.0)
    {
        digitalWrite(m_minus,LOW);
        digitalWrite(m_plus,LOW);
        return;
    }
    if(mod< 0)
    {
        mod = -mod;
        uint8_t aux = m_plus;
        m_plus = m_minus;
        m_minus = aux;
    }
    if(mod < PWM_MINIMUM)
    {
        digitalWrite(m_minus,LOW);
        digitalWrite(m_plus,LOW);
        return;
    }
    if(mod> PWM_MAX)
        mod = PWM_MAX;

    digitalWrite(m_minus,LOW);
    analogWrite(m_plus,(uint8_t) mod);


}

void resetIntegrals()
{
    integral1 = 0;
    integral2 = 0;
}

void setupPID()
{
    pinMode(MOTOR_DIR_MINUS,OUTPUT);
    pinMode(MOTOR_ESQ_MINUS,OUTPUT);
    pinMode(MOTOR_DIR_PLUS,OUTPUT);
    pinMode(MOTOR_ESQ_PLUS,OUTPUT);

    cli();//stop interrupts
    //set timer0 interrupt at 2kHz
    TCCR0A = 0;// set entire TCCR0A register to 0
    TCCR0B = 0;// same for TCCR0B
    TCNT0  = 0;//initialize counter value to 0
    // set compare match register for 2khz increments
    OCR0A = 124;// = (16*10^6) / (2000*64) - 1 (must be <256)
    // turn on CTC mode
    TCCR0A |= (1 << WGM01);
    // Set CS01 and CS00 bits for 64 prescaler
    TCCR0B |= (1 << CS01) | (1 << CS00);   
    // enable timer compare interrupt
    TIMSK0 |= (1 << OCIE0A);
    sei(); // return interrupts
    resetIntegrals();

}

ISR(TIMER0_COMPA_vect)
{
    PID();
}