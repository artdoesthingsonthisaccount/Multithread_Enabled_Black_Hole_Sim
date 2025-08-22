#include "bh.hpp"

#include <iostream>




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
// void bh::update_position(void){
//     for(int i=0; i<NUM_DIMENSIONS; i++){
//         coords[i] += cartesian_pd[i];
//     }
// }
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