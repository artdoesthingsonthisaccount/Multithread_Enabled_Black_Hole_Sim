#include "ray.hpp"

#include <iostream>

//TODO:

//create a raytrail class with actual member fucntions that will be dedicated to managing the ray trail
//data structure and its graphics (basically everything you've written so far is just for the head.)

//set_pdir
//polar_to_rectangular_pdir_conversion
//calc_redshift
//update_position


static int ray_cnt = 0;
static std::queue<class ray *> preloaded_q;


// bh a has less distance than bh b, wrt the ray head 
bool dist_cmp_less(bhdata_wrt_ray a, bhdata_wrt_ray b){
    return a.dist < b.dist;
}

ray::ray(std::array<double, NUM_DIMENSIONS> _coords, std::array<double, NUM_DIMENSIONS> _pdir) {
    ray_cnt++;
    pdirtype= USING_CARTESIAN_COORDS;
    coords = _coords;
    pdir = _pdir;

    if (ray_cnt >= NUM_RAYS){//then we should the heap building process until we find an optimization for it
        preloaded_q.push(this);
        return;
    }

    //this chunk of code needs to be studied and optimized
    vector<bhdata_wrt_ray> temp;
    for (int i = 0; i < NUM_BH; i++){
        if (!bhtab[i]) continue;
        struct bhdata_wrt_ray pbbh = {calc_dist(i), calc_redshift(i), i};
        temp.push_back(pbbh);
    }
    
    std::priority_queue bhd_pq(temp.begin(), temp.end(), dist_cmp_less);
}



/*
updates position as well as blackhole in range and
pdir based on if there IS a blackhole in range
*/
void ray::update_position(void){
    /*
    update bookkeeping on nearest bh WITHIN RANGE (bh outside of the POLAR_COMP_DIST arent considered)


    Finally we can just deal with regular situations, such as moving in range of the black hole from blank space AND OFCOURSE UPDATE PDIR ACCORDINGLY
    (blackhole in range, and none set by pointer already -> pointer set), leaving a blackhole to blank space (pointer full and ray leaving blackhole range -> pointer NULLed)


    next we can progress (or propagate) the ray trail
    next we can calculate the new pdir based on position of all of the blackholes and the ray

    and finally we can increment the number of rays
    */
    

    if (!bh_in_range){ //no current bh in range
        if (calc_dist(bhd_pq.top().bhtab_idx) < POLAR_COMP_RAD){
            bh_in_range = bhtab[bhd_pq.top().bhtab_idx];


            if (get_pdirtype() == USING_POLAR_COORDS){
                //special case for if we were already in polar coordinates and there is no specified origin (bh)
                
                //delete ray here
                return; 
            }else{
                set_pdirtype(USING_POLAR_COORDS);
                //TODO: CONVERT TO POLAR_COORDINATES WRT BH HERE
            }
            
        }
    } else{ //there currently is a bh in range
        int bh_in_range_idx = 
        (int)((char *)(bh_in_range) -(char *)&bhtab)/sizeof(struct bh *); 

        if(bh_in_range_idx != bhd_pq.top().bhtab_idx){
            double closest_in_range_distance = calc_dist(bh_in_range_idx);
            double heap_top_distance = calc_dist(bh_in_range_idx);

            // closest_in_range_distance == heap_top_distance is a special case for if two bh are the same distance away from a ray
            if (closest_in_range_distance == heap_top_distance){
                return;
            }
            if (heap_top_distance < closest_in_range_distance){

                bh_in_range = bhtab[bhd_pq.top().bhtab_idx];
                closest_in_range_distance = heap_top_distance;
            }

            if (closest_in_range_distance > POLAR_COMP_RAD){

                //convert to rectangular coordinates    
                set_pdir(get_pdir_cartesian_explicit(bh_in_range));                
                set_pdirtype(USING_CARTESIAN_COORDS);
                bh_in_range = NULL;
            }

            
        }
    }

    //CODE FOR RECALCULATING HEAP HERE!!!!!!! 



    std::array<double, NUM_DIMENSIONS> new_head;
    //math for calculating new_head
    ray_trail.propagate_rt(new_head);


    //math for calculating new_pdir

    ray_cnt++;
}




//returns the cartesian pdir with respect to the true origin UNDER THE PRETEXT that we provide the

std::array<double, NUM_DIMENSIONS> ray::get_pdir_cartesian_explicit(struct bh * bh_of_prior_engagement){
    std::array<double, NUM_DIMENSIONS> bh_pd_offset;

    if (bh_of_prior_engagement){
        bh_pd_offset = bh_of_prior_engagement->get_cartesian_pd();
        

        //TODO: THE MATH HERE IS OFF
        if (pdirtype ==USING_POLAR_COORDS){//case in which we're already moving in circular coordinates to account for effects of the blackhole
            return polar_to_rectangular_pdir_conversion(get_pdir_standard()) + bh_pd_offset;
        }else if (pdirtype ==USING_CARTESIAN_COORDS) {//case in which we're moving in cartesian coordinates
            return get_pdir_standard() + bh_pd_offset;
        }
    }
    else{//case for no prior blackhole or just left
        
        if (pdirtype ==USING_CARTESIAN_COORDS){
            return get_pdir_standard();

        }else if (pdirtype == USING_POLAR_COORDS){
            
            /*
            worst case scenario. we left a blackhole range and set bh_in_range==NULL before we could switch coordinates
            from polar to cartesian. not that the current blackhole at the top of the heap is not actually the blackhole that we escaped.
            the most RECENT (or CURRENT) blackhole is always the one that was removed from the top of the heap and pointed to by bh_in_range.
            The good thing is the one we lost WAS the previous closest blackhole, so unless we're considering events like two blackholes colliding,
            in which case they are a lot closer together and it might not be clear which ones were/are closer, (we should consider 
            these events though), we should be able to just loop through the bhtab for a blackhole closer than the one at the current top
            */
            std::cout << "worst case scenario. please see comment" << std::endl;
            //worst case algo here
            double likely_second_closest_dist = calc_dist(bhd_pq.top().bhtab_idx);
            for (int i = 0; i < NUM_BH; i++){
                if (!bhtab[i]) continue;
                double dist = calc_dist(i);
                if (dist < likely_second_closest_dist){
                    bh_pd_offset = bhtab[i]->get_cartesian_pd();
                    break;
                }

            }

            //TODO: MATH HERE IS OFF
            return polar_to_rectangular_pdir_conversion(get_pdir_standard())+ bh_pd_offset;

        }

    }

}

//this just takes any polar coordinates and does the simple math of converting them to rectangular coordinates
std::array<double, NUM_DIMENSIONS> polar_to_rectangular_pdir_conversion(std::array<double, NUM_DIMENSIONS> polar_coords){
    std::array<double, NUM_DIMENSIONS> rectangular_coords;

    //TODO: implement this function properly  

}

//this calculates the redshift of the blackhole from the ray's perspective
double ray::calc_redshift(int bhtab_idx){
    //TODO: implement this function properly
    return;
}
double ray::calc_dist(int bhtab_idx){
    std::array<double, NUM_DIMENSIONS> rc = this->get_coords();
    std::array<double, NUM_DIMENSIONS> bhc= bhtab[bhtab_idx]->get_coords();

    double dist = 0.0;
    for (int i = 0; i<NUM_DIMENSIONS; i++) dist=+ std::pow((rc.at(i)),2);
    dist = std::sqrt(dist);
    return dist;
}
std::array<double, NUM_DIMENSIONS> ray::get_coords(void){
    return coords;
}
void ray::set_coords(const std::array<double,NUM_DIMENSIONS> _coord){
    coords = _coord;
}
int ray::get_pdirtype(){

    return pdirtype;
}
void ray::set_pdirtype(int _pdirtype){
    pdirtype = _pdirtype;
    return;
}
void ray::set_bh_ptr(class bh * bhptr){
    bh_in_range = bhptr;
}
class bh * ray::get_bh_ptr(void){
    return bh_in_range;
}
void ray::set_pdir(const std::array<double, NUM_DIMENSIONS> _pdir){
    pdir = _pdir;
}
std::array<double, NUM_DIMENSIONS> ray::get_pdir_standard(){
    return pdir;
}