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


void detection(Square * boxesCrossed, int * nbBoxCrossed, Point golem, Point player){
    int i, nb_x, nb_y, a;
    double x0, x1, y0, y1;
    double pa[120];  /*120 is maximum number of case that can be detected */
    x0 = golem.x, y0 = golem.y;
    x1 = player.x, y1 = player.y;
    if(player.x < golem.x){
        x1 = golem.x, y1 = golem.y;
        x0 = player.x, y0 = player.y;
    }
    nb_x = (int)x1 - (int)x0;
    nb_y = (int)y1 - (int)y0;
    
    *nbBoxCrossed = nb_x + nb_y;;
    a = (int)x0 +1;
    for(i = 0; i < nb_x; i++){
        pa[i] = (a - x0) / (x1 - x0);
        printf("%f\n", pa[i]);
        a++;
    }
    a = (int)y0 +1;

    printf("\n");
    for(i; i < *nbBoxCrossed; i++){
        pa[i] = (a - y0) / (y1 - y0);
        printf("%f\n", pa[i]);
        a++;
    }
    for(i=0; i < *nbBoxCrossed; i++){
        boxesCrossed[i].isWall = pa[i] * x1 + (1 - pa[i]) * x0;  /*horizontal position*/
        boxesCrossed[i].hasMana = pa[i] * y1 + (1 - pa[i]) * y0; /*vertical position*/
    }
}


