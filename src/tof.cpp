#include <tof.h>
#include <VL53L0X.h>
#include <Wire.h>
#include <constants.h>
#include <pins.h>

int16_t dist_left=0, dist_right=0, dist_front_left=0, dist_front_right=0;
bool wall_left=0,wall_front=0,wall_right=0;

//estruturas que guardam valor de medição dos sensores
VL53L0X sensor_left;
VL53L0X sensor_front_left;
VL53L0X sensor_front_right;
VL53L0X sensor_right;


void readTOF()
{
    dist_left = sensor_left.readRangeContinuousMillimeters()- TOF_OFFSET;
    dist_right = sensor_right.readRangeContinuousMillimeters()- TOF_OFFSET;
    dist_front_left = sensor_front_left.readRangeContinuousMillimeters()- TOF_OFFSET;
    dist_front_right = sensor_front_right.readRangeContinuousMillimeters()-TOF_OFFSET;

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
    sensor_left.setTimeout(500);
    sensor_right.setTimeout(500);
    sensor_front_left.setTimeout(500);
    sensor_front_right.setTimeout(500);

    //seta modo de leitura continua
    sensor_left.startContinuous();
    sensor_right.startContinuous();
    sensor_front_left.startContinuous();
    sensor_front_right.startContinuous();
}