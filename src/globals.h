#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>
#include <array>
#include "config.h"
#include "bh.hpp"
#include "ray.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>


using namespace std;

int global_step = 0;

GLFWwindow * scene;

extern class bh * bhtab[NUM_BH];
extern class ray * raytab[NUM_RAYS];

#endif