#ifndef BH_H
#define BH_H

#include <iostream>
#include <array>
#include <utility>

using namespace std;

class bh{
    public:
        std::pair<double, double> get_coords(void);
        void set_coords(std::pair<double, double> cc);
        std::pair<double, double> get_cartesian_pd(void);
        void set_cartesian_pd(std::pair<double, double> cpd);
    private:
        std::pair<double, double> coords;
        std::pair<double, double> cartesian_pd;
        

};

#endif