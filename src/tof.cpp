#include <tof.h>
#include <VL53L0X.h>
#include <Wire.h>
#include <constants.h>
#include <pins.h>

float dist_left=0, dist_right=0, dist_front_left=0, dist_front_right=0;
float ldist_left=0, ldist_right=0, ldist_front_left=0, ldist_front_right=0;
bool wall_left=0,wall_front=0,wall_right=0;

//estruturas que guardam valor de medição dos sensores
VL53L0X sensor_left;
VL53L0X sensor_front_left;
VL53L0X sensor_front_right;
VL53L0X sensor_right;

#define PERCENTAGE_AVG 0.8
void readTOF()
{
    
    ldist_left = ldist_left*(1-PERCENTAGE_AVG) + (float) sensor_left.readRangeContinuousMillimeters()*PERCENTAGE_AVG;
    ldist_right = ldist_right*(1-PERCENTAGE_AVG) + (float) sensor_right.readRangeContinuousMillimeters()*PERCENTAGE_AVG;
    ldist_front_left =ldist_front_left*(1-PERCENTAGE_AVG) + (float) sensor_front_left.readRangeContinuousMillimeters()*PERCENTAGE_AVG;
    ldist_front_right = ldist_front_right*(1-PERCENTAGE_AVG) + (float) sensor_front_right.readRangeContinuousMillimeters()*PERCENTAGE_AVG;
    dist_left = ldist_left;
    dist_right = ldist_right;
    dist_front_left = ldist_front_left;
    dist_front_right = ldist_front_right;



    wall_front = (dist_front_left+dist_front_right <= FRONT_WALL_DIST*2) ? true : false;
    wall_left = (dist_left <= SIDE_WALL_DIST) ? true: false;
    wall_right = (dist_right<= SIDE_WALL_DIST) ? true: false;
}

void setupTOF()
{
    Wire.begin(); // inicializa I2C
    pinMode(XSHUT1,OUTPUT);
    pinMode(XSHUT2,OUTPUT);
    pinMode(XSHUT3,OUTPUT);
    digitalWrite(XSHUT1,LOW);
    digitalWrite(XSHUT2,LOW);
    digitalWrite(XSHUT3,LOW);
    //ativa sensor 1 por 1, mudando seu endereço original
    delay(10);
    sensor_left.setAddress(0x10);
    digitalWrite(XSHUT1,HIGH);
    delay(10);
    sensor_front_left.setAddress(0x20);
    digitalWrite(XSHUT2,HIGH);
    delay(10);
    sensor_front_right.setAddress(0x30);
    digitalWrite(XSHUT3,HIGH);
    delay(10);
    sensor_right.setAddress(0x40);
    //inicializa os sensores
    sensor_left.init();
    sensor_right.init();
    sensor_front_left.init();
    sensor_front_right.init();
    
    //seta timeout para os sensores
    sensor_left.setTimeout(10000);
    sensor_right.setTimeout(500);
    sensor_front_left.setTimeout(500);
    sensor_front_right.setTimeout(500);

    //seta modo de leitura continua
    sensor_left.startContinuous();
    sensor_right.startContinuous();
    sensor_front_left.startContinuous();
    sensor_front_right.startContinuous();
}