#include<leds.h>
#include<pins.h>

uint8_t led_data =0;

void setLED(uint8_t led, bool on)
{
    led_data = (on) ? led_data | led : led_data & (~led);
}
void updateLEDs()
{
    digitalWrite(RCLK,LOW); // seta para low LD (RCLK)
    //Escreve bit a bit na saída e da um pulso de CLK serial
    for(char i =0 ; i < 8; i++)
    {
        digitalWrite(SR, (led_data >> i) & 0b1); 
        digitalWrite(SRCLK,HIGH);
        digitalWrite(SRCLK,LOW);
    }
    //seta LD para HIGH, mostrando os valores carregados
    digitalWrite(RCLK,HIGH);
}

void setupLEDs()
{
    pinMode(RCLK,OUTPUT);
    pinMode(SRCLK,OUTPUT);
    pinMode(SR,OUTPUT);
    digitalWrite(RCLK,LOW);
    digitalWrite(SRCLK,LOW);
    digitalWrite(SR,LOW);
}