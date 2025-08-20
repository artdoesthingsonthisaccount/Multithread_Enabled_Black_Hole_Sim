#ifndef RAY_H
#define RAY_H

// #ifndef NUM_RAYS
// #define NUM_RAYS 10
// #endif

#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
#include "config.h"
#include "globals.h"

using namespace std;

#define ENABLE 1
#define DISABLE 0

#define USING_CARTESIAN_COORDS 0
#define USING_POLAR_COORDS 1

struct bhdata_wrt_ray{
    double dist;
    double redshift;
    int bhtab_idx;
};

struct preloaded_ray_list_node {
    class ray * ray_ptr;
    struct preloaded_ray_list_node * next;
};


double calc_redshift(class ray * ray, int bhtab_idx);
double calc_dist(class ray * ray, int bhtab_idx);

class ray{
    public:
        //ray(std::pair<double,double> _coords); //infrastructure for "preloading" rays (at a specific position but) to start later 
        //never mind the above constructor he don't know what he saying 

        ray(std::pair<double, double> _coords, std::pair<double, double> _pdir); //decides whether ray gets preloaded based on
        ray(std::pair<double, double> _coords, std::pair<double, double> _pdir, int enable); //predecides whether to enable

        std::pair<double,double> get_coords(void);
        void set_coords(const std::pair<double, double> _coords);

        /*
        updates position as well as blackhole in range and
        pdir based on if there IS a blackhole in range
        */

        int get_enable(void);
        int set_enable(int enable);
        void update_position(void);
        void update_range_fields(void);
        void set_bh_ptr(class bh * bhptr);
        class bh * get_bh_ptr(void);

        int get_pdirtype(void);
        void set_pdirtype(int _pdirtype);
        
        std::pair<double, double> get_pdir(void);
        void set_pdir(const int pdir);
        void update_pdir(void);

    private:
        std::pair<double, double> coords;

        class bh * bh_in_range;
        vector<bhdata_wrt_ray>  bhdata;
        
        int pdirtype = USING_CARTESIAN_COORDS; //use cartesian by default. this value just encodes what we're currently using
        //use polar propagation direction (used wrt nearest black hole) if we're close enough to a black hole
        std::pair<double, double> pdir;
        std::vector<std::pair<double, double>> ray_trail;
};

#endif
