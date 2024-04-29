#include <PID.h>
#include <pins.h>
#include <constants.h>
#include <encoder.h>
#include <Arduino.h>
#include <tof.h>

#define DIAMETER_INVERSED 1/DIAMETER
#define DISTANCE_WHEELS_INVERSED 1/DISTANCE_WHEELS
#define INVERSE_COUNTS_PER_ROT 1/COUNTS_PER_ROT



uint8_t pid_control = PID_DEFAULT;
void setPID(uint8_t control)
{
    pid_control = control;
}

float ideal_v=0,ideal_w=0;//in Hz
float ideal_x = 0, ideal_theta = 0;
void motor(uint8_t m_plus,uint8_t m_minus, float mod);
void setVW(float v, float w) //mm/s and rads/s
{
    //v = (vl+vd)/2
    //w = (vd-vl)/D
    ideal_v = v;
    ideal_w = w*DISTANCE_WHEELS*0.5;
    
}
void setXTheta(float x, float theta)
{
    ideal_x = x;
    ideal_theta = theta;
}

float e1=0,e2=0;
float integral1=0,integral2=0;
float etheta=0,ex=0;
uint8_t finished=0;
bool MoveEnded()
{
    switch (pid_control & (PID_AUTO_STOP_X ||PID_AUTO_STOP_THETA))
    {
    case PID_AUTO_STOP_X:
        return pid_control == 0b10;
        break;
    case PID_AUTO_STOP_THETA:
        return pid_control == 0b01;
        break;
    
    default:
        return pid_control == 0b11;
        break;
    }
}
void PID()
{
    //sees if moves have ended when on auto stop
    if(pid_control & PID_AUTO_STOP_THETA && abs(ideal_theta) < abs(getTheta()))
    {
        ideal_w=0;
        finished |= 0b01;
    }
    if(pid_control & PID_AUTO_STOP_THETA && abs(ideal_x) < abs(getX()))
    {
        ideal_v = 0;
        finished |= 0b10;
    }

    float mod1,mod2;
    float e1n=ideal_v-ideal_w-getV1();
    float e2n=ideal_v+ideal_w-getV2();
    integral1 += e1n;
    integral2 += e2n;

    //sets pid for w and v control
    mod1 = e1n*Kp + (e1n- e1)*Kd + integral1*Ki;
    mod2 = e2n*Kp + (e2n - e2)*Kd + integral2*Ki;
    e1 =e1n;
    e2 = e2n;
    
    //sets PD for drifts (not included I term, may add later )
    float modtheta = 0;
    if(pid_control & PID_STRAIGHT)
    {
        float ethethan = -getTheta();
        modtheta = ethethan*Kp_theta+(ethethan-etheta)*Kd_theta;
        etheta = ethethan;
    } else if (pid_control & PID_INPLACE)
    {
        float exn = - getX();
        mod1 += exn*Kp_x + (exn-ex)*Kd_x;
        ex = exn;
    }



    
    //gives instructions to motors
    if(ideal_v-ideal_w == 0.0)
        motor(MOTOR_ESQ_PLUS,MOTOR_ESQ_MINUS,-modtheta);
    else
        motor(MOTOR_ESQ_PLUS,MOTOR_ESQ_MINUS,mod1-modtheta);
    if(ideal_v+ideal_w  == 0.0)
        motor(MOTOR_DIR_PLUS,MOTOR_DIR_MINUS,modtheta);
    else
        motor(MOTOR_DIR_PLUS,MOTOR_DIR_MINUS,mod2+modtheta);
    
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
    count_left = 0;
    count_right = 0;
}

void setupPID()
{
    pinMode(MOTOR_DIR_MINUS,OUTPUT);
    pinMode(MOTOR_ESQ_MINUS,OUTPUT);
    pinMode(MOTOR_DIR_PLUS,OUTPUT);
    pinMode(MOTOR_ESQ_PLUS,OUTPUT);

    cli();//stop interrupts
    TCCR1A = 0;// set entire TCCR1A register to 0
    TCCR1B = 0;// same for TCCR1B
    TCNT1  = 0;//initialize counter value to 0
    // set compare match register for 1hz increments
    OCR1A = 624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
    // turn on CTC mode
    TCCR1B |= (1 << WGM12);
    // Set CS10 and CS12 bits for 1024 prescaler
    TCCR1B |= (1 << CS12);  
    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);
    sei(); // return interrupts
    resetIntegrals();

}

ISR(TIMER0_COMPA_vect)
{
    PID();
}
//x andado desde o ultimo reset em mm
float getX()
{
    return (count_left+count_right)*0.5f*DIAMETER*INVERSE_COUNTS_PER_ROT;
}
//theta andado desde o ultimo reset em radianos
float getTheta()
{
    if(pid_control & PID_USE_TOF)
    {
        if(wall_front && !(wall_left && wall_right))
        {
            return (dist_front_right-dist_front_left)/(float)(dist_front_left+dist_front_right)*2;
        }
        if(wall_left && wall_right)
        {
            return (dist_right-dist_left)/(float)(dist_left+dist_right)*2;
        }
    }
    return (count_right-count_left)*DIAMETER*INVERSE_COUNTS_PER_ROT*DISTANCE_WHEELS_INVERSED;
}