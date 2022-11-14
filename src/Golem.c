/**
 * @file Move.c
 * @author Gabiel Radoniaina (radoniaina@edu.univ-eiffel.fr)
 * @brief Source file for Move module
 * @version 0.1
 * @date 2022-11-07
 * 
 * 
 */

#include "../include/Golem.h"


static double randRange(double min, double max){
    assert(min > 0);
    assert(max >= min);
    return min + (rand() / RAND_MAX) * (max - min);
}

void initGolem(Golem * golem){
    golem->direction = rand() % 4;
    golem->detectionRadius = 4;
    golem->speed = randRange(0.3, 0.8);
    golem->panic = 0;
}
 

