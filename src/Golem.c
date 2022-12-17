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


int moveGolem(Golem * golem, Grid * grid){
    double x, y, speed;
    Point newLocation;
    int collided;
    newLocation = golem->location;
    x = 0, y = 0;
    speed = golem->speed * V;
    if(golem->panic){
        speed = V;
    }
    switch(golem->direction){
        case up: newLocation.y -= speed; break;
        case down: newLocation.y += speed; break;
        case left: newLocation.x -= speed; break;
        case right: newLocation.x += speed; break;
    }
    
    collided = isCollision(&newLocation, *grid, golem->direction);
    golem->location = newLocation;
    return collided;
}
 

void patrolGolem(Golem * golem, Grid * grid){
    
    if(golem->panic && anticipateCollision(golem->location, *grid, golem->direction, 1.0)){
        golem->direction = getRandomDirection(golem->direction);
        return;
    }
    if(moveGolem(golem, grid)){
        golem->direction = getRandomDirection(golem->direction);
        golem->speed = randRange(0.3, 0.8);
    }

}




