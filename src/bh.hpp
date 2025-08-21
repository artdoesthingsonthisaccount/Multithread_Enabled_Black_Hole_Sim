#ifndef BH_H
#define BH_H

#include <iostream>
#include <array>
#include <utility>

using namespace std;

class bh{
    public:
        std::array<double, NUM_DIMENSIONS> get_coords(void);
        void set_coords(std::array<double, NUM_DIMENSIONS> cc);
        std::array<double, NUM_DIMENSIONS> get_cartesian_pd(void);
        void set_cartesian_pd(std::array<double, NUM_DIMENSIONS> cpd);
    private:
        std::array<double, NUM_DIMENSIONS> coords;
        std::array<double, NUM_DIMENSIONS> cartesian_pd;
        

};

#endif