#include "ray.hpp"

#include <iostream>



//TODO LIST:
//MAKE THE PRELOAD LINKED LIST A QUEUE INSTEAD



// bh a has less distance than bh b, wrt the ray head 
bool dist_cmp_less(bhdata_wrt_ray a, bhdata_wrt_ray b){
    return a.dist < b.dist;
}

static int ray_cnt = 0;
struct preloaded_ray_list_node * preloaded_ray_list;

ray::ray(std::array<double, NUM_DIMENSIONS> _coords, std::array<double, NUM_DIMENSIONS> _pdir) {
    ray_cnt++;
    pdirtype= USING_CARTESIAN_COORDS;
    coords = _coords;
    pdir = _pdir;

    if (ray_cnt >= NUM_RAYS){//then we should the heap building process until we find an optimization for it
        preload(this);
        return;
    }

    //this chunk of code needs to be studied and optimized
    vector<bhdata_wrt_ray> temp;
    for (int i = 0; i < NUM_BH; i++){
        if (!bhtab[i]) continue;
        struct bhdata_wrt_ray pbbh = {calc_dist(i), calc_redshift(i), i};
        temp.push_back(pbbh);
    }
    
    std::priority_queue ldist_pq(temp.begin(), temp.end(), dist_cmp_less);

}



/*
updates position as well as blackhole in range and
pdir based on if there IS a blackhole in range
*/
void ray::update_position(void){
    /*
    check if the nearest black hole is within range

    if it is, then we need to CHECK FOR DOUBLE BLACKHOLE BOUNDARY 
    and update the pdir to be polar (double blackhole boundary is when
    the ray is between two black holes, but I don't know what the solution to this would be. something to resolve with pdir)
    

    if it is not, then we need to check if it was before (whether or not the bh_in_range pointer was set or NULL)
    then, we have a few strategies for optimization how many times we have to edit blackholes in a heap each step.
    1. we can just update all of them...
    2. we can edit the first 3 blackholes in the heap every step, and update the others every 5-10 steps
    
    3. LATER we are building our own library for smart heap anyway. so maybe we can just wait till then for the optimization.


    Finally we can just deal with regular situations, such as moving in range of the black hole from blank space AND OFCOURSE UPDATE PDIR ACCORDINGLY
    (blackhole in range, and none set by pointer already -> pointer set), leaving a blackhole to blank space (pointer full and ray leaving blackhole range -> pointer NULLed)


    next we update the lights
    next we can progress (or propagate) the ray trail

    and finally we can increment the step
    */
    

}
// void ray::update_range_fields(void){


//     for (int i = 0; i < NUM_BH;i++){
//         if (!bhtab[i]) continue;

//         std::array<double, NUM_DIMENSIONS> bhc = bhtab[i]->get_coords();         
//         std::array<double, NUM_DIMENSIONS> rayc = ray::get_coords();

//         // double dist = 0.0;
//         // for (int j = 0; j < NUM_DIMENSIONS; j++){
//         //     dist =+ std::pow((bhc.at(j)-rayc.at(j)), 2);
//         // }
//         // dist = std::sqrt(dist);
        
//         if (dist <= POLAR_COMP_RAD) {
            
//         }
//     }
// }
//THIS ONE IS DEFINITELY PROBABLY WRONG
void ray::set_pdir(const int pdir){
    //TODO: FIX THIS SHIT

    if (get_pdirtype()==USING_POLAR_COORDS) { //this means we were already in a black holes range
        if (calc_dist(bh_in_range->get_coords()) > POLAR_COMP_RAD) {
            pdirtype = USING_CARTESIAN_COORDS; //switch to cartesian coords
            pdir = bh_in_range->get_cartesian_pd();
        }
        else {
            //we're still in polar coords, so we can just use the current pdir
        }
    }
    else {

    }
}
void update_pdir(void){

}

void ray::set_bh_ptr(class bh * bhptr){

    //resolve for if there was already something occupying the bh_in_range pointer

    bh_in_range = bhptr;
}

/*
this function needs work. polar pdir is not useful at all unless we have the location of the black hole
*/
std::array<double, NUM_DIMENSIONS> ray::get_pdir(void){
    //TODO: what if we're in polar coordinates? convert back?
}





class bh * ray::get_bh_ptr(){
    return bh_in_range;
}




double ray::calc_redshift(int bhtab_idx){
    //TODO
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
void preload(class ray * ray_ptr){ //could just use a vector instead of a linked list...
    
    struct preloaded_ray_list_node * curr = preloaded_ray_list;
    while (curr->next) curr = curr->next;

    struct preloaded_ray_list_node * new_ray_node = (struct preloaded_ray_list_node *) malloc(sizeof(struct preloaded_ray_list_node));
    new_ray_node->next = NULL;
    new_ray_node->ray_ptr = ray_ptr; 


}