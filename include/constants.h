#ifndef _CONSTANTS
#define _CONSTANTS
// WALL DISTANCE SENSIBILITY CONSTANTS (mm)
#define SIDE_WALL_DIST 60
#define FRONT_WALL_DIST 60
// WALL DISTANCE OFFSET CONSTANTS (mm)
#define TOF_OFFSET 10
//Diameter Wheels
#define DIAMETER 60.0 //(mm)
#define DISTANCE_WHEELS 110.0 //(mm)

//encoder constants
#define COUNTS_PER_ROT 406.3f

// minimal PWM
#define PWM_MINIMUM 15
#define PWM_MAX 255

//para pid dos motores
#define Kp 16
#define Kd 0.03
#define Ki 400

//para pid de controle de drift angular
#define Kp_theta 1.0f
#define Kd_theta 1.0f

//para pid de controle de drift ao rotacionar
#define Kp_x 1.0f
#define Kd_x 1.0f




#endif