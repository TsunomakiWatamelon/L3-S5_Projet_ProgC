/**
 * @file Collision.c
 * @author Herve Nguyen (herve.nguyen@edu.univ-eiffel.fr)
 * @brief Source file for the Collision module
 * @version 0.1
 * @date 2022-12-15
 * 
 * 
 */

#include "../include/Collision.h"
#define sqr(x) ((x) * (x))

int isLimit(Coordinate target, Grid grid){
    if (target.x >= MAX_WIDTH || target.x < 0)
        return 1;
    if (target.y >= MAX_HEIGHT || target.y < 0)
        return 1;

    return grid.square[target.y][target.x].isWall;
}

int nextCoordinate(Point *center, Coordinate *target, Direction d){
    assert(center);
    assert(target);

    target->x = (int)center->x;
    target->y = (int)center->y;

    if (d == left) {
        target->x -= 1;
    }
    else if (d == right) {
        target->x += 1;
    }
    else if (d == up) {
        target->y -= 1;
    }
    else {
        target->y += 1;
    }
    return 1;
}

int isCollisionA(Point *center, Direction d) {
    double limit;
    int abs_x, abs_y;

    abs_x = (int)center->x;
    abs_y = (int)center->y;

    if (d == left || d == right) {
        /* Fetching the "limit" coordinate for the x axis */
        limit = abs_x + (d == left ? -1 : 1) * 0.5;
        if ((d == left && center->x <= limit) || (d == right && center->x >= limit)) {
            center->x = limit;
            return 1;
        }
    }
    else if (d == up || d == down) {
        /* Fetching the "limit" coordinate for the y axis */
        limit = abs_y + (d == up ? -1 : 1) * 0.5;
        if ((d == up && center->y <= limit) || (d == down && center->y >= limit)) {
            center->y = limit;
            return 1;
        }
    }
    return 0;
}
int isCollisionB(Point* center, Direction d) {
    int abs_x = (int)center->x;
    int abs_y = (int)center->y;
    double delta;
    double limit;

    if (d == up || d == down) {
        /* Calculating the delta between the wall cell and the entity */
        delta = (d == up) ? (abs_x + 1.0 - center->x) : (center->x - abs_x);
        /* Fetching the "limit" coordinate for the y axis */
        limit = (d == up) ? (abs_y - 1.0 + sqrt(0.25 - sqr(delta))) : (abs_y + 1.0 - sqrt(0.25 - sqr(delta)));

        if ((d == up && center->x > abs_x + 0.5 && center->y <= limit) ||
            (d == down && center->x < abs_x + 0.5 && center->y >= limit)) {
            center->y = limit;
            return 1;
        }
    }
    else if (d == left || d == right) {
        /* Calculating the delta between the wall cell and the entity */
        delta = (d == left) ? (abs_y + 1.0 - center->y) : (center->y - abs_y);
        /* Fetching the "limit" coordinate for the x axis */
        limit = (d == left) ? (abs_x - 1.0 + sqrt(0.25 - sqr(delta))) : (abs_x + 1.0 - sqrt(0.25 - sqr(delta)));

        if ((d == left && center->y > abs_y + 0.5 && center->x <= limit) ||
            (d == right && center->y < abs_y + 0.5 && center->x >= limit)) {
            center->x = limit;
            return 1;
        }
    }

    return 0;
}



int isCollisionC(Point* center, Direction d) {
    int abs_x = (int)center->x;
    int abs_y = (int)center->y;
    double delta;
    double limit;

    if (d == up || d == down) {
        /* Calculating the delta between the wall cell and the entity */
        delta = (d == up) ? (center->x - abs_x) : (abs_x + 1.0 - center->x);
        /* Fetching the "limit" coordinate for the y axis */
        limit = (d == up) ? (abs_y - 1.0 + sqrt(0.25 - sqr(delta))) : (abs_y + 1.0 - sqrt(0.25 - sqr(delta)));
        if ((d == up && center->x > abs_x + 0.5 && center->y <= limit) ||
            (d == down && center->x < abs_x + 0.5 && center->y >= limit)) {
            center->y = limit;
            return 1;
        }
    }
    else if (d == left || d == right) {
        /* Calculating the delta between the wall cell and the entity */
        delta = (d == left) ? (center->y - abs_y) : (abs_y + 1.0 - center->y);
        /* Fetching the "limit" coordinate for the x axis */
        limit = (d == left) ? (abs_x - 1.0 + sqrt(0.25 - sqr(delta))) : (abs_x + 1.0 - sqrt(0.25 - sqr(delta)));
        if ((d == left && center->y > abs_y + 0.5 && center->x <= limit) ||
            (d == right && center->y < abs_y + 0.5 && center->x >= limit)) {
            center->x = limit;
            return 1;
        }
    }

    return 0;
}



int isCollision(Point *center, Grid grid, Direction d){
    double radius;
    Coordinate targetA, targetB, targetC;

    radius = 1.0;

    nextCoordinate(center, &targetA, d);      
    targetB = targetA;
    targetC = targetA;
    if (directionIsHorizontal(d)){
        targetB.x -= 1;
        targetC.x -= 1;
    }
    else{
        targetB.y -= 1;
        targetC.y -= 1;
    }
    if (isLimit(targetA, grid) && isCollisionA(center, d))
        return 1;
    if (isLimit(targetB, grid) && isCollisionB(center, d))
        return 1;
    if (isLimit(targetC, grid) && isCollisionC(center, d))
        return 1; 
    return 0;
}

int willCollide(Point *center, Grid grid, Direction d, double speed){
    Point newPosition;
    double *modified;

    assert(center);

    newPosition = *center;
    if (d == left || d == right)
        modified = &(newPosition.x);
    else
        modified = &(newPosition.y);

    if (d == left || d == up)
        *modified -= speed * V;
    else
        *modified += speed * V;
    
    return isCollision(&newPosition, grid, d);
    
}