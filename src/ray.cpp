

#include "ray.hpp"

#include <iostream>
#include <cmath>

#define c 3^8

static int ray_cnt = 0;
struct preloaded_ray_list_node * preloaded_ray_list;

ray::ray(std::pair<double, double> _coords, std::pair<double,double> _pdir){
    ray_cnt++;
    coords = _coords;
    pdir = _pdir;

    if (ray_cnt >= NUM_RAYS){//then we should the heap building process until we find an optimization for it
        set_enable(DISABLE);
        return;
    }

    for (int i = 0; i < NUM_BH; i++){
        if (!bhtab[i]) continue;
        struct bhdata_wrt_ray pbbh = {calc_dist(this, i), calc_redshift(this, i), i};
        bhdata.push_back(pbbh);//[learning] WTF is a temporary or rvalue and why is the signature of pushback so weird?

    }
    std::make_heap(bhdata.begin(), bhdata.end());

    
}

std::pair<double, double> ray::get_coords(void){
    return coords;
}
void ray::set_coords(const std::pair<double,double> _coords){
    coords.first = _coords.first;
    coords.second = _coords.second;
}

/*
updates position as well as blackhole in range and
pdir based on if there IS a blackhole in range
*/
void ray::update_position(void){
    //blackhole range check
    update_range_fields();

}
void ray::update_range_fields(void){


    for (int i = 0; i < NUM_BH;i++){
        if (!bhtab[i]) continue;

        std::pair<double, double> bhc = bhtab[i]->get_coords();         
        std::pair<double, double> rayc = ray::get_coords();

        double dist = std::sqrt(std::pow((bhc.first-rayc.first), 2) +std::pow((bhc.second-rayc.second),2));
        if (dist <= POLAR_COMP_RAD) {
        
            
        }
    }
}

void ray::set_bh_ptr(class bh * bhptr){

    //resolve for if there was already something occupying the bh_in_range pointer

    bh_in_range = bhptr;
}

class bh * ray::get_bh_ptr(){
    return bh_in_range;
}

/*
this function needs work. polar pdir is not useful at all unless we have the location of the black hole
*/
std::pair<double, double> ray::get_pdir(void){
    //TODO: what if we're in polar coordinates? convert back?
}


void set_pdir(const int pdir){

    if (get_pdirtype()==USING_POLAR_COORDS) {
        
    }
    else 
}
void update_pdir(void){

}

int get_pdirtype(){
    return pdirtype;
}
void set_pdirtype(int _pdirtype){
    pdirtype = _pdirtype;
}



double calc_redshift(class ray * ray, int bhtab_idx){
    //TODO
    return;
}
double calc_dist(class ray * ray, int bhtab_idx){
    std::pair<double, double> rc = ray->get_coords();
    std::pair<double, double> bhc= bhtab[bhtab_idx]->get_coords();
    return (std::sqrt(std::pow((bhc.first -rc.first),2) + std::pow((bhc.second-rc.second),2)));
}