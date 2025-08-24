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
        bh();
        bh(std::array<double, NUM_BH> _coords, std::array<double, NUM_BH> _cpd, double _m, double _r, double _s);

        void update_position(double time_nHz);//updates wrt the time interval that was stepped (in nanoseconds)
        void update_pdir(void); //updates wrt the the positions of all the other black holes in bhtab

        std::array<double, NUM_DIMENSIONS> get_coords(void);
        void set_coords(std::array<double, NUM_DIMENSIONS> cc);
        std::array<double, NUM_DIMENSIONS> get_cartesian_pd(void);
        void set_cartesian_pd(std::array<double, NUM_DIMENSIONS> cpd);

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