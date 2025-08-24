#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>
#include <array>
#include "config.h"
#include "bh.hpp"
#include "ray.hpp"


using namespace std;

int global_step = 0;

extern class bh * bhtab[NUM_BH];
extern class ray * raytab[NUM_RAYS];

#endif