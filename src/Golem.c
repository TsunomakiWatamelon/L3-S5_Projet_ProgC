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


void initGolem(Golem * golem, Point location){
    golem->direction = rand() % 4;
    golem->detectionRadius = 4.0;
    golem->speed = randRange(0.3, 0.8);
    golem->panic = 0;
    golem->location = location;
}


void moveGolem(Golem * golem){
    double x, y, speed;
    x = 0, y = 0;
    speed = golem->speed * V;
    if(golem->panic){
        speed = V;
    }
    switch(golem->direction){
        case up: golem->location.y -= speed; break;
        case down: golem->location.y += speed; break;
        case left: golem->location.x -= speed; break;
        case right: golem->location.x += speed; break;
    }
}
 

/*void patrolGolem(Golem * golem){

}*/




