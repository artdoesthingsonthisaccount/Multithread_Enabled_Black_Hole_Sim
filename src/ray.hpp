#ifndef RAY_H
#define RAY_H

#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include "config.h"
#include "globals.h"

using namespace std;


#define USING_CARTESIAN_COORDS 0
#define USING_POLAR_COORDS 1

struct bhdata_wrt_ray{
    double dist;
    double redshift;
    int bhtab_idx;
};



bool dist_cmp_less(bhdata_wrt_ray a, bhdata_wrt_ray b);

class ray{
    public:
        //ray(std::pair<double,double> _coords); //infrastructure for "preloading" rays (at a specific position but) to start later 
        //never mind the above constructor he don't know what he saying 

        ray(std::array<double, NUM_DIMENSIONS> _coords, std::array<double, NUM_DIMENSIONS> _pdir); //decides whether ray gets preloaded based on
        ray(std::array<double, NUM_DIMENSIONS> _coords, std::array<double, NUM_DIMENSIONS> _pdir, int enable); //predecides whether to enable

        std::array<double, NUM_DIMENSIONS> get_coords(void);
        void set_coords(std::array<double, NUM_DIMENSIONS> _coords);

        /*
        updates position as well as blackhole in range and
        pdir based on if there IS a blackhole in range
        */


        double calc_redshift(int bhtab_idx); //calculates the redshift of the ray wrt the black hole at bhtab_idx
        double calc_dist(int bhtab_idx); //calculates the distance between the ray and the black hole at bhtab_idx


        void preload(); //queues a ray in the preloading list (ok next thing we are doing is making this a queue instead)
        void update_position(void);
        void set_bh_ptr(class bh * bhptr);
        class bh * get_bh_ptr(void);

        int get_pdirtype(void);
        void set_pdirtype(int _pdirtype);
        
        std::array<double, NUM_DIMENSIONS> get_pdir_cartesian_explicit(struct bh * bh_of_prior_engagement);
        std::array<double, NUM_DIMENSIONS> get_pdir_standard(void);
        void set_pdir(const std::array<double, NUM_DIMENSIONS>_pdir);

    private:
        std::array<double, NUM_DIMENSIONS> coords; //coordinates of the ray
        class bh * bh_in_range;
        std::priority_queue<bhdata_wrt_ray>  bhd_pq; //priority queue for black holes that are closer wrt the ray head

        /*
        use cartesian by default. this value just encodes what we're currently using use polar 
        propagation direction (used wrt nearest black hole) if we're close enough to a black hole
        otherwise use cartesian propagation direction. (0 for cartesian, 1 for polar)
        */
        int pdirtype = USING_CARTESIAN_COORDS; 
        std::array<double, NUM_DIMENSIONS> pdir;

        rt ray_trail;//new way to keep track of ray trail
};



//the RAY part handles placing the graphics for the head of the ray (one signal point) while the raytrail
//class deals with "removing" the back. this raytrail class will basically allow it to inch forward with the head. 
// in the future I'll implement somehting to account for the dynamic bending of the rays due to the movement of the blackholes.



class rt {
    public:
        void propagate_rt(std::array<double, NUM_DIMENSIONS> new_head);
        //way more room for improvement
    private:
        std::vector<std::array<double, NUM_DIMENSIONS>> ray_trail;
};





#endif