#ifndef BH_H
#define BH_H

#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include "config.h"
#include "globals.h"

using namespace std;

class bh{
    public:
        std::array<double, NUM_DIMENSIONS> get_coords(void);
        void set_coords(std::array<double, NUM_DIMENSIONS> cc);
        std::array<double, NUM_DIMENSIONS> get_cartesian_pd(void);
        void set_cartesian_pd(std::array<double, NUM_DIMENSIONS> cpd);
        void update_position(void);
        void set_mass(double m);
        double get_mass(void);
        void set_radius(double r);
        double get_radius(void);
        void set_spin(double s);
        double get_spin(void);
        
    private:
        std::array<double, NUM_DIMENSIONS> coords;
        std::array<double, NUM_DIMENSIONS> cartesian_pd;
        double mass;
        double radius;
        double spin;

};

#endif