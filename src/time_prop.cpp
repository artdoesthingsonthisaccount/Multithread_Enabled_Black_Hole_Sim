#include "time_prop.hpp"


using namespace std;




void step_loop(){
    while (global_step < SCENE_LENGTH) step();
}

void step(){
    
    for (int i = 0; i < NUM_BH; i++){
        bhtab[i]->update_position(1/GLOBAL_STEP_FREQUENCY);
    }
    for (int i = 0; i < NUM_BH; i++){
        bhtab[i]->update_pdir();
    }

    for (int i = 0; i< NUM_RAYS; i++){
        raytab[i]->update_state(1/GLOBAL_STEP_FREQUENCY);
    }
    global_step++;
}