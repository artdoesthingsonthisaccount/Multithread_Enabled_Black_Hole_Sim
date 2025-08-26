#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>
#include <array>
#include "config.h"
#include "bh.hpp"
#include "ray.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <eigen3/Eigen/Dense>



using namespace std;

Eigen::MatrixXd weak_field_parameter = Eigen::MatrixXd::Identity(NUM_DIMENSIONS+1, NUM_DIMENSIONS + 1);
int global_step = 0;

GLFWwindow * scene;

extern class bh * bhtab[NUM_BH];
extern class ray * raytab[NUM_RAYS];

#endif