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

struct intPoint {
    int x;
    int y;
};


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
 

int patrolGolem(Golem * golem, Player * player, Grid * grid){
    
    if(golem->panic && anticipateCollision(golem->location, *grid, golem->direction, 1.0)){
        golem->direction = getRandomDirection(golem->direction);
        return;
    }
    if(moveGolem(golem, grid)){
        golem->direction = getRandomDirection(golem->direction);
        golem->speed = randRange(0.3, 0.8);
    }

    if (detection(golem->location, player->location, grid))
        return 1;
    
    return 0;
}

static void getCrossedSquare(Point golem, Point player, struct intPoint **target, int *crossedLen){
    int i, arrayLen;
    int a;
    double x0, x1, y0, y1, xa, ya;
    double pa;
    struct intPoint *crossed;

    crossed = (struct intPoint *) malloc(sizeof(struct intPoint) * 120);
    *target = crossed;

    arrayLen = 0;
    x0 = golem.x, y0 = golem.y;
    x1 = player.x, y1 = player.y;
    if(player.x < golem.x){
        x1 = golem.x, y1 = golem.y;
        x0 = player.x, y0 = player.y;
    }

    
    for (a = (int)x0; a <= (int)x1; a++){
        pa = (a - x1) / (x0 - x1);
        if (!(0 <= pa) || !(1 <= pa))
            continue;
        else{
            ya = y1 + ((y0 - y1) / (x0 - x1)) * (a - x1);
            crossed[arrayLen].y = (int)ya;
            crossed[arrayLen].x = a;
            arrayLen++;
        }
    }

    x0 = golem.x, y0 = golem.y;
    x1 = player.x, y1 = player.y;
    if(player.y < golem.y){
        x1 = golem.x, y1 = golem.y;
        x0 = player.x, y0 = player.y;
    }

    for (a = (int)y0; a <= (int)y1; a++){
        pa = (a - y1) / (y0 - y1);
        if (!(0 <= pa) || !(1 <= pa))
            continue;
        else{
            xa = x1 + ((x0 - x1) / (y0 - y1)) * (a - y1);
            crossed[arrayLen].y = a;
            crossed[arrayLen].x = (int)xa;
            arrayLen++;
        }
    }

    *crossedLen = arrayLen;

}

int detection(Point golem, Point player, Grid *grid){
    struct intPoint *crossed;
    int crossedLen, i;

    getCrossedSquare(golem, player, &crossed, &crossedLen);

    for (i = 0; i < crossedLen; i++){
        if (grid->square[crossed[i].y][crossed[i].x].isWall)
            return 1;
    }
    return 0;

}