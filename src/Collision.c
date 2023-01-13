/**
 * @file Collision.c
 * @author HERVE NGUYEN & GABRIEL RADONIAINA
 * @brief Collision module, deals with collisions between hypothetical circular entities of diameter of 1.0
 * @version 0.1
 * @date 2022-12-15
 * 
 * 
 */

#include "../include/Collision.h"
#define sqr(x) ((x) * (x))

/**
 * @brief Checks if the square at the given coordinate is a wall or out of bound (for collision check purposes)
 * 
 * @param target coordinate of the square to be checked
 * @param grid the grid
 * @return int 1 if it is a wall or out of bound, 0 otherwise
 */
static int isLimit(Coordinate target, Grid grid){
    if (target.x >= MAX_WIDTH || target.x < 0)
        return 1;
    if (target.y >= MAX_HEIGHT || target.y < 0)
        return 1;

    return grid.square[target.y][target.x].isWall;
}

/**
 * @brief Get the Coordinate of the adjacent square
 * to the current square where the "center" point is located 
 * (following the dirction given)
 * And store it's coordinates into 'target'
 * 
 * The center here would represent the center of the circle of an entity
 * 
 * @param center the center of the entity (it's coordinates)
 * @param target pointer to the struct to contain the coordinates of the corresponding square
 * @param d the direction to determine which adjacent square to chose
 */
static void getCoordinate(Point *center, Coordinate *target, Direction d){
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
}

/**
 * @brief Get the coordinates of the square related to the B case of collision
 * There is two sub-types in the type B collision.
 * The main difference being that the wall unit is at the "top" of the entity for one sub-type.
 * And the other was "below".
 * 
 * @param center the center of the entity (it's coordinates)
 * @param target pointer to the struct to contain the coordinates of the corresponding square
 * @param d the direction to determine which sub-type is selected (either up or down)
 */
static void getCoordinateB(Point *center, Coordinate *target, Direction d){
    assert(center);
    assert(target);
    assert(d == up || d == down);

    getCoordinate(center, target, d);

    if (d == up) {
        target->x += 1;
    }
    else {
        target->x -= 1;
    }
} 

/**
 * @brief Get the coordinates of the square related to the C case of collision
 * There is two sub-types in the type C collision.
 * The main difference being that the wall unit is at the "top" of the entity for one sub-type.
 * And the other was "below".
 * 
 * @param center the center of the entity (it's coordinates)
 * @param target pointer to the struct to contain the coordinates of the corresponding square
 * @param d the direction to determine which sub-type is selected (either up or down)
 */
static void getCoordinateC(Point *center, Coordinate *target, Direction d){
    assert(center);
    assert(target);
    assert(d == up || d == down);

    getCoordinate(center, target, d);

    if (d == up) {
        target->x -= 1;
    }
    else {
        target->x += 1;
    }
}

/**
 * @brief Tests if the entity described by the given Point is colliding with the adjacent
 * wall in front of it (from the given direction)
 * 
 * The square is implicitly a wall, this function won't be called if it wasn't.
 * 
 * The center of the entity will have it's coordinates readjusted if there is a collision.
 * 
 * @param center the center of the entity (it's coordinates)
 * @param d the direction to determine which adjacent square to chose
 * @return int 1 if it colliding, otherwise 0
 */
static int isCollisionA_aux(Point *center, Direction d) {
    double limit;
    int abs_x, abs_y;

    abs_x = (int)center->x;
    abs_y = (int)center->y;

    if (d == left || d == right) {
        /* Fetching the "limit" coordinate for the x axis */
        limit = abs_x + 0.5;
        if ((d == left && center->x < limit) || (d == right && center->x > limit)) {
            center->x = limit;
            return 1;
        }
    }
    else if (d == up || d == down) {
        /* Fetching the "limit" coordinate for the y axis */
        limit = abs_y + 0.5;
        if ((d == up && center->y < limit) || (d == down && center->y > limit)) {
            center->y = limit;
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Returns 1 if it is colliding with a wall around the entity (described by the Point) (left, right, up or down only, not diagonally)
 * 
 * The center of the entity will have it's coordinates readjusted if there is a(multiple) collision(s).
 * 
 * @param center the center of the entity (it's coordinates)
 * @param grid the grid, used to check if a wall among the squares around the entity
 * @return int 1 if it colliding, otherwise 0
 */
static int isCollisionA(Point* center, Grid grid){
    int collided;
    Coordinate targetA_up, targetA_down, targetA_left, targetA_right;
    Coordinate currentSquare;

    currentSquare.x = (int)center->x; currentSquare.y = (int)center->y;
    getCoordinate(center, &targetA_down, down);
    getCoordinate(center, &targetA_up, up);
    getCoordinate(center, &targetA_left, left);
    getCoordinate(center, &targetA_right, right);

    collided = 0;

    
    if (isLimit(currentSquare, grid))
        collided = 1;
    if (isLimit(targetA_up, grid)){
        collided = (collided || isCollisionA_aux(center, up));
    }
    if (isLimit(targetA_down, grid)){
        collided = (collided || isCollisionA_aux(center, down));
    }
    if (isLimit(targetA_left, grid)){
        collided = (collided || isCollisionA_aux(center, left));
    }
    if (isLimit(targetA_right, grid)){
        collided = (collided || isCollisionA_aux(center, right));
    }
    
    return collided;
}

/**
 * @brief Tests if the entity described by the given Point is colliding with the wall located at the places described by
 * the B type collision.
 * 
 * There is two possible place the collision would be checked.
 * Depending on the direction given. It checks only one location and not the other
 * 
 * The square is implicitly a wall, this function won't be called if it wasn't.
 * 
 * The center of the entity will have it's coordinates readjusted if there is a collision.
 * 
 * @param center the center of the entity (it's coordinates)
 * @param d the direction to determine which adjacent square to chose
 * @return int 1 if it colliding, otherwise 0
 */
static int isCollisionB_aux(Point* center, Direction location) {
    int abs_x, abs_y, cond;
    double limit;

    abs_x = (int)center->x;
    abs_y = (int)center->y;

    /* Not the direction where the entity is running into */
    /* But the location of the "wall" in regards of the collision rules */
    /* Example for B type in the subject is "down" */
    if (location == up || location == down) {
        /* Fetching the "limit" coordinate for the y axis */
        limit = (location == up) ?
                (abs_y + sqrt(0.25 - sqr(abs_x + 1.0 - center->x)))
              : (abs_y + 1.0 - sqrt(0.25 - sqr(center->x - abs_x)));
        /* Condition to check if there is a collision or not*/
        cond = (location == up) ?
               ((center->x > abs_x + 0.5) && (center->y < limit)) 
             : ((center->x < abs_x + 0.5) && (center->y > limit));
        if (cond) {
            center->y = limit;
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Returns 1 if it is colliding with a wall around the entity (described by the Point)
 * At possible places described by the B type collision.
 * 
 * The center of the entity will have it's coordinates readjusted if there is a(multiple) collision(s).
 * 
 * @param center the center of the entity (it's coordinates)
 * @param grid the grid, used to check if a wall at those described places
 * @return int 1 if it colliding, otherwise 0
 */
static int isCollisionB(Point* center, Grid grid){
    int collided;
    Coordinate targetB_up, targetB_down;

    getCoordinateB(center, &targetB_up, up);
    getCoordinateB(center, &targetB_down, down);

    collided = 0;

    if (isLimit(targetB_up, grid)){
        collided = isCollisionB_aux(center, up);
    }
    if (isLimit(targetB_down, grid)){
        collided = (collided || isCollisionB_aux(center, down));
    }
    return collided;
}

/**
 * @brief Tests if the entity described by the given Point is colliding with the wall located at the places described by
 * the C type collision.
 * 
 * There is two possible place the collision would be checked.
 * Depending on the direction given. It checks only one location and not the other
 * 
 * The square is implicitly a wall, this function won't be called if it wasn't.
 * 
 * The center of the entity will have it's coordinates readjusted if there is a collision.
 * 
 * @param center the center of the entity (it's coordinates)
 * @param d the direction to determine which adjacent square to chose
 * @return int 1 if it colliding, otherwise 0
 */
static int isCollisionC_aux(Point* center, Direction location) {
    int abs_x, abs_y, cond;
    double limit;

    abs_x = (int)center->x;
    abs_y = (int)center->y;

    /* Not the direction where the entity is running into */
    /* But the location of the "wall" in regards of the collision rules */
    /* Example for B type in the subject is "down" */
    if (location == up || location == down) {
        /* Fetching the "limit" coordinate for the y axis */
        limit = (location == up) ?
                (abs_y + sqrt(0.25 - sqr(center->x - abs_x)))
              : (abs_y + 1.0 - sqrt(0.25 - sqr(center->x - abs_x - 1.0)));
        /* Condition to check if there is a collision or not*/
        cond = (location == up) ?
               ((center->x < abs_x + 0.5) && (center->y < limit)) 
             : ((center->x > abs_x + 0.5) && (center->y > limit));
        if (cond) {
            center->y = limit;
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Returns 1 if it is colliding with a wall around the entity (described by the Point)
 * At possible places described by the C type collision.
 * 
 * The center of the entity will have it's coordinates readjusted if there is a(multiple) collision(s).
 * 
 * @param center the center of the entity (it's coordinates)
 * @param grid the grid, used to check if a wall at those described places
 * @return int 1 if it colliding, otherwise 0
 */
static int isCollisionC(Point* center, Grid grid){
    int collided;
    Coordinate targetC_up, targetC_down;

    getCoordinateC(center, &targetC_up, up);
    getCoordinateC(center, &targetC_down, down);

    collided = 0;

    if (isLimit(targetC_up, grid)){
        collided = isCollisionC_aux(center, up);
    }
    if (isLimit(targetC_down, grid)){
        collided = (collided || isCollisionC_aux(center, down));
    }
    return collided;
}


/**
 * @brief Checks if the supposed entity of radius 1 described by the point is colliding any walls
 * 
 * The entity's position will be adjusted if there is a collision, so that it's boundaries won't be crossing beyond the walls.
 * 
 * @param center 
 * @param grid 
 * @return int 1 if there is a collision, 0 otherwise
 */
int isCollision(Point *center, Grid grid){
    int collided;
    Coordinate targetA_up, targetA_down, targetA_left, targetA_right;

    getCoordinate(center, &targetA_down, down);
    getCoordinate(center, &targetA_up, up);
    getCoordinate(center, &targetA_left, left);
    getCoordinate(center, &targetA_right, right);

    collided = isCollisionA(center, grid);
    collided = collided || isCollisionB(center, grid);
    collided = collided || isCollisionC(center, grid);
    return collided;
}

/**
 * @brief Checks if the given entity will collide into a wall if going toward a certain direction for a certain unit of space
 * 
 * Returns 1 if it WILL be in collision with a wall, 0 otherwise
 * 
 * @param center the center position of the entity
 * @param grid the grid (have info about the possible existing walls)
 * @param d the direction of the move
 * @param distance the unit of distance to anticipate
 * @return int 1 if it WILL be in collision with a wall, 0 otherwise
 */
int willCollide(Point center, Grid grid, Direction d, double distance){
    Point newPosition;
    double *modified;

    newPosition = center;
    if (d == left || d == right)
        modified = &(newPosition.x);
    else
        modified = &(newPosition.y);

    if (d == left || d == up)
        *modified -= distance;
    else
        *modified += distance;
    
    return isCollision(&newPosition, grid);
    
}
