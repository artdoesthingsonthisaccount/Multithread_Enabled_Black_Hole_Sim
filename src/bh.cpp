#include "bh.hpp"

#include <iostream>

bh::bh(){
//random generation with some guards to make sure they don't end up too close to close to eachother.
}
bh::bh(std::array<double, NUM_BH> _coords, std::array<double, NUM_BH> _cpd, double _m, double _r, double _s){
    coords = _coords;
    cartesian_pd = _cpd;
    mass = _m;
    radius = _r;
    spin = _s;
}



//theres no way its that easy
void bh::update_position(double time_nHz){
    for(int i=0; i<NUM_DIMENSIONS; i++){
        coords[i] += cartesian_pd[i] * (time_nHz/std::pow(10, -9));
    }

    //TODO: RENDER BLACK HOLE HERE
}
void bh::update_pdir(){
    //TODO: IMPLEMENT THIS FUNCTION
}

std::array<double, NUM_DIMENSIONS> bh::get_coords(void){
    return coords;
}
void bh::set_coords(std::array<double, NUM_DIMENSIONS> cc){
    coords = cc;
}
std::array<double, NUM_DIMENSIONS> bh::get_cartesian_pd(void){
    return cartesian_pd;
}
void bh::set_cartesian_pd(std::array<double, NUM_DIMENSIONS> cpd){
    cartesian_pd = cpd;
}
void bh::set_mass(double m){    
    mass = m;
}
double bh::get_mass(void){
    return mass;
}
void bh::set_radius(double r){
    radius = r;
}
double bh::get_radius(void){
    return radius;
}
void bh::set_spin(double s){
    spin = s;
}
double bh::get_spin(void){
    return spin;
}