#include <PID.h>
#include <pins.h>
#include <constants.h>
#include <encoder.h>
#include <Arduino.h>
#include <tof.h>

#define DIAMETER_INVERSED 1/DIAMETER // inverse diameter of micromouse wheel.
#define DISTANCE_WHEELS_INVERSED 1/DISTANCE_WHEELS // inverted distance between wheels of micromouse
#define INVERSE_COUNTS_PER_ROT 1/COUNTS_PER_ROT // inverted counts per rotation of encoder


bool pid_on = false; //general switch PID
uint8_t pid_control = PID_DEFAULT; //stores configuration of PID
float e1=0,e2=0;    //LAST ERRORS OF MOTOR 1 AND 2
float integral1=0,integral2=0; //INTEGRAL ERROR OF THE MOTORS
float etheta=0,ex=0; // LAST THETA ERROR AND X ERROR
volatile uint8_t finished=0; // 0B1 WHEN ROTATION ENDED, 0B10 WHEN TRANSLATION ENDED ON AUTO_STOP MODE
float ideal_v=0,ideal_w=0;// Expected values in mm/s and rad/s
float ideal_x = 0, ideal_theta = 0; //Expected values in mm and rad, only valid to AUTO-STOP
float integral_theta = 0;
/* motor
* @brief Função seta motor dado com o valor de pwm igual a mod, alterando direções. 
* @addindex m_plus  pino M1 do motor
* @param m_minus  pino M2 do motor
* @param mod  valor de pwm entre -255.0 e 255.0, será convertido para char e dada a direção correta, valores positivos são horários.
* @param output pwm do motor é setado para abs(mod) com direção cw se mod>0 e ccw se mod<0
* @attention valores de abs(mod) < PWM_MINIMUM serão setados para 0, e valores de abs(mod) > PWM_MAXIMUM serão truncados.
* alterações:
*   - 30/04/2024: criado comentário, começado a documentar. - @walger-lucas
*/
void motor(uint8_t m_plus,uint8_t m_minus, float mod)
{
    uint8_t plus = m_plus,minus = m_minus;
    if(mod == 0.0)
    {
        digitalWrite(m_minus,LOW);
        digitalWrite(m_plus,LOW);
        return;
    }
    if(mod< 0)
    {
        mod = - mod;
        plus = m_minus;
        minus = m_plus;
    }
    if(mod < PWM_MINIMUM)
    {
        digitalWrite(m_minus,LOW);
        digitalWrite(m_plus,LOW);
        return;
    }
    if(mod> PWM_MAX)
        mod = PWM_MAX;
    digitalWrite(minus,LOW);
    analogWrite(plus,(uint8_t) mod);


}

void setPID(uint8_t control)
{
    pid_control = control;
}

void activatePID(bool on)
{
    pid_on = on;
}

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


bool moveEnded()
{
    uint8_t control = 0;
    if(pid_control & PID_AUTO_STOP_X)
        control|= 0b10;
    if(pid_control & PID_AUTO_STOP_THETA)
        control|= 0b1;
    if(control ==0)
        return false;
    return finished == control;
}
/* @name PID
* @brief realiza controle de todos os PIDs, realiza controle de fim automático do PID.
* @return void
* @date alterações:
*   - 30/04/2024: criado comentário, começado a documentar. - @walger-lucas
*   -08/05/2024: direção do motor esquerdo trocado, por um motor dever ter a direção contrária do outro. -@walger-lucas
*/
void PID()
{
    //sees if moves have ended when on auto stop
    if(pid_control & PID_AUTO_STOP_THETA && abs(ideal_theta) < abs(getTheta()))
    {
        ideal_w=0;
        finished |= 0b01; // seta fim do movimento angular
    }
    if(pid_control & PID_AUTO_STOP_X && abs(ideal_x) < abs(getX()))
    {
        ideal_v = 0;
        finished |= 0b10; // seta fim do movimento linear
    }

    //sets PD for drifts (not included I term, may add later )
    float modtheta = 0;
    float modx = 0;
    if(pid_control & PID_STRAIGHT)
    {
        
        float ethethan = -(count_left+count_right*REGULATOR_RIGHT);
        integral_theta += ethethan*0.01;
        modtheta = ethethan*Kp_theta+(ethethan-etheta)*Kd_theta*100+Ki_theta*integral_theta*0.01;
        etheta = ethethan;
    }else if (pid_control & PID_INPLACE)
    {
        float exn = - getX();
        integral_theta += 0.01*exn;
        modx += exn*Kp_x + (exn-ex)*Kd_x*100+ integral_theta*0.01*Ki_x;
        ex = exn;
    }
    //does pid of each motor
    float mod1,mod2;
    //calcula erros atuais
    float e1n=-ideal_v+ideal_w-getV1()+modtheta-modx;
    float e2n=ideal_v+ideal_w-getV2()+modtheta+modx;
    integral1 += e1n*0.01;
    integral2 += e2n*0.01;
    
    //sets pid for w and v control
    // MOD = e*Kp + de/dt * Kd + (S e dt) * Ki
    mod1 = e1n*Kp + (e1n- e1)*100*Kd + integral1*Ki;
    mod2 = e2n*Kp + (e2n - e2)*Kd*100 + integral2*Ki;
    e1 =e1n;
    e2 = e2n;




    //gives instructions to motors
    if(ideal_v-ideal_w == 0.0)
        motor(MOTOR_ESQ_PLUS,MOTOR_ESQ_MINUS,0);
    else
        motor(MOTOR_ESQ_PLUS,MOTOR_ESQ_MINUS,mod1);
   if(ideal_v+ideal_w  == 0.0)
        motor(MOTOR_DIR_PLUS,MOTOR_DIR_MINUS,0);
    else
        motor(MOTOR_DIR_PLUS,MOTOR_DIR_MINUS,mod2);
    
}

void resetIntegrals()
{
    integral1 = 0;
    integral2 = 0;
    integral_theta =0;

}

void resetFinished()
{
    finished=0;
}

void resetCounts()
{
    count_left = 0;
    count_right = 0;
}
void normalizeCounts()
{
    int theta = count_left+count_right;
    if(pid_control && PID_USE_TOF)
    {
        if(wall_front || wall_right || wall_left)
            theta = getTheta()*(1.0/(DIAMETER*3.1416*INVERSE_COUNTS_PER_ROT*DISTANCE_WHEELS_INVERSED));
    }
    
    count_left = 0;
    count_right = 0;
}

void setupPID()
{
    setupEncoders();
    pinMode(MOTOR_DIR_MINUS,OUTPUT);
    pinMode(MOTOR_ESQ_MINUS,OUTPUT);
    pinMode(MOTOR_DIR_PLUS,OUTPUT);
    pinMode(MOTOR_ESQ_PLUS,OUTPUT);

    cli();//stop interrupts
    TCCR1A = 0;// set entire TCCR1A register to 0
    TCCR1B = 0;// same for TCCR1B
    TCNT1  = 0;//initialize counter value to 0
    // set compare match register for 1hz increments
    OCR1A = 624;// = (16*10^6) / (100*1024) - 1 (must be <65536)
    // turn on CTC mode
    TCCR1B |= (1 << WGM12);
    // Set CS10 and CS12 bits for 1024 prescaler
    TCCR1B |= (1 << CS12);  
    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);
    sei(); // return interrupts
    resetIntegrals();

}

//INTERRUP HANDLER
ISR(TIMER1_COMPA_vect)
{
    if(pid_on)
        PID();
    else
    {
        motor(MOTOR_DIR_PLUS,MOTOR_DIR_MINUS,0);
        motor(MOTOR_ESQ_PLUS,MOTOR_ESQ_MINUS,0);
    }
}

float getX()
{
    //x = (v1+v2)/2 = (c1+c2)*Diametro_rodas*pi/(counts_por_rotação*2)
    return (-count_left+count_right*REGULATOR_RIGHT)*0.5f*DIAMETER*INVERSE_COUNTS_PER_ROT*3.1415;
}

float getTheta()
{
    //se com pid utiliza a diferença entre os sensores, priorizando utilizar os sensores frontais caso possível
    // theta = (v2-v1)/Distancia_Rodas = (c2-c1)*Diametro_Rodas*pi/(counts_por_rotação*Distancia_Rodas)
    if(pid_control & PID_USE_TOF)
    {
        if(wall_front && !(wall_left && wall_right))
        {
            return (dist_front_right-dist_front_left)/(float)(dist_front_left+dist_front_right)*2;
        } else
        if(wall_left && wall_right)
        {
            return (dist_right-dist_left)/(float)(dist_left+dist_right)*2;
        }
    }
    return (count_right*REGULATOR_RIGHT+count_left)*DIAMETER*3.1416*INVERSE_COUNTS_PER_ROT*DISTANCE_WHEELS_INVERSED;
}