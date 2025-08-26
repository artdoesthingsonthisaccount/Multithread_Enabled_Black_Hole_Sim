#ifndef CONFIG_H
#define CONFIG_H


//MACRO DEFINITIONS HERE FOR MAX LIMITS

#define SCENE_LENGTH 100000


#define c 3^8 //speed of light in km/s
#define G 3

#define NUM_RAYS 10 //macro for the number of Rays we want to simulate
#define NUM_BH 3

#define NUM_DIMENSIONS 3 //number of dimensions in the simulation

//radius in which to switch to polar coordinates and visa versa
#define POLAR_COMP_RAD 10


#define MAX_RAY_TRAIL_LEN 100 //length of the ray trail in number of points

#define GLOBAL_STEP_FREQUENCY 100 //frequency of each step in nHz



#endif