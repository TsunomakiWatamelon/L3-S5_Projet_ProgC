/**
 * @file Move.c
 * @author HERVE NGUYEN & GABRIEL RADONIAINA
 * @brief Golem module, has functions relating to the behavior of golems
 * @version 0.1
 * @date 2022-11-07
 * 
 * 
 */

#include "../include/Golem.h"


/**
 * @brief Initializes the golem at the given position
 * 
 * @param golem the golem's pointer
 * @param location the location that the golem will be set
 */
void initGolem(Golem * golem, Point location){
    golem->direction = rand() % 4;
    golem->speed = randRange(0.3, 0.8);
    golem->panic = 0;
    golem->location = location;
    golem->lostNb = 0;
}

/**
 * @brief Moves the golem and check if it is colliding with a wall
 * 
 * @param golem the golem's pointer
 * @param grid the grid's pointer that has information about possible walls
 * @return int 1 if it has collided with a wall, 0 otherwise
 */
int moveGolem(Golem * golem, Grid * grid){
    double speed;
    int collided;

    assert(golem);
    assert(grid);

    collided = 0;
    speed = golem->speed * V;
    if(golem->panic){
        speed = V;
    }
    /* We use a new location */
    switch(golem->direction){
        case up: golem->location.y -= speed; break;
        case down: golem->location.y += speed; break;
        case left: golem->location.x -= speed; break;
        case right: golem->location.x += speed; break;
    }
    
    /* It would be useless to check this in panic mode*/
    if (!golem->panic)
        collided = isCollision(&(golem->location), *grid);
    
    if (randRange(0.0, 1.0) <= (1.0 / 500.0)){
        golem->direction = getRandomDirection(golem->direction);
        golem->speed = randRange(0.3, 0.8);
    }

    return collided;
}

/**
 * @brief Modifies the order of the given x and y coordinates based on the type parameter.
 *
 * If type is 0, then the order of the x coordinates is focused on. Otherwise it's the order of the y coordinates/
 * If the coordinate of the player is less than the coordinate of the golem in the relevant dimension (x or y, depending on type), then the order of the coordinates is swapped.
 *
 * @param golem the golem's location
 * @param player the player's location
 * @param x0 a pointer to the x coordinate of the first point
 * @param y0 a pointer to the y coordinate of the first point
 * @param x1 a pointer to the x coordinate of the second point
 * @param y1 a pointer to the y coordinate of the second point
 * @param type 0 if the x coordinates should be modified, otherwise the y coordinates is modified
 */
static void setOrder(Point golem, Point player, double *x0, double *y0, double *x1, double *y1, int type){
    int cond;

    assert(golem.x >= 0.0 && golem.y >= 0.0);
    assert(player.x >= 0.0 && player.y >= 0.0);
    assert(x0);
    assert(x1);
    assert(y0);
    assert(y1);

    *x0 = golem.x, *y0 = golem.y;
    *x1 = player.x, *y1 = player.y;
    cond = type ? (player.y < golem.y) : (player.x < golem.x);

    if (cond){
        *x1 = golem.x, *y1 = golem.y;
        *x0 = player.x, *y0 = player.y;
    }
}

/**
 * @brief Calculates the squares crossed by a line drawn between a golem and a player.
 * 
 * @param golem the golem's position
 * @param player the player's position
 * @param target a pointer to a variable where the list of crossed squares will be stored
 * @param crossedLen a pointer to a variable where the length of the list of crossed squares will be stored
 */
static void getCrossedSquare(Point golem, Point player, Coordinate **target, int *crossedLen){
    int arrayLen;
    int a;
    double x0, x1, y0, y1, xa, ya;
    double pa;
    Coordinate *crossed;

    assert(golem.x >= 0.0 && golem.y >= 0.0);
    assert(player.x >= 0.0 && player.y >= 0.0);
    assert(crossedLen);
    assert(target);

    crossed = (Coordinate *) malloc(sizeof(Coordinate) * 120);
    *target = crossed;

    arrayLen = 0;

    setOrder(golem, player, &x0, &y0, &x1, &y1, 0);
    for (a = (int)x0 + 1; a < (int)x1; a++){
        pa = (a - x1) / (x0 - x1);
        if ((0.0 > pa) || (1.0 < pa))
            continue;
        ya = y1 + ((y0 - y1) / (x0 - x1)) * (a - x1);
        crossed[arrayLen].y = (int)ya;
        crossed[arrayLen].x = a;
        arrayLen++;
    }

    setOrder(golem, player, &x0, &y0, &x1, &y1, 1);

    for (a = (int)y0 + 1; a < (int)y1; a++){
        pa = (a - y1) / (y0 - y1);
        if ((0.0 > pa) || (1.0 < pa))
            continue;
        xa = x1 + ((x0 - x1) / (y0 - y1)) * (a - y1);
        crossed[arrayLen].y = a;
        crossed[arrayLen].x = (int)xa;
        arrayLen++;
    }

    *crossedLen = arrayLen;

}

/**
 * @brief Checks if the entities are in the line of sight of each other
 * 
 * They are in each other's line of sight if the line drawn between the two does not cross a wall
 * 
 * @param entity1 the entity1's point
 * @param entity2 the entity2's point
 * @param grid the grid which has information about possible walls
 * @return int 1 if the player is it's line of sight, 0 otherwise
 */
int inLineOfSight(Point entity1, Point entity2, Grid *grid){
    Coordinate *crossed;
    int crossedLen, i, res;

    assert(grid);

    getCrossedSquare(entity1, entity2, &crossed, &crossedLen);

    res = 1;
    for (i = 0; i < crossedLen; i++){
        if (crossed[i].y < 0 || MAX_HEIGHT <= crossed[i].y){
            continue;
        }
        if (crossed[i].x < 0 || MAX_WIDTH <= crossed[i].x){
            continue;
        }
        if (grid->square[crossed[i].y][crossed[i].x].isWall){
            res = 0;
            break;
        }
    }
    free(crossed);
    return res;
}

/**
 * @brief Determines if a golem has detected the object.
 * 
 * A golem is able to detect the object if they are within a certain radius of each other and if the object is in the golem's line of sight (free of any wall blocking it)
 * The radius of detection depends on the state of the golem (if it is in panic mode or not)
 * 
 * @param golem the golem to check for detection
 * @param object the position of the object
 * @param grid the grid which has information about possible walls
 * @return int 1 if the golem has detected the object, 0 otherwise
 */
static int detection(Golem golem, Point object, Grid *grid){

    assert(grid);

    /* We subtract 0.5 to include cases where a small part of entity (always of diameter 1.0) enters the detection range */
    if ((pointDistance(golem.location, object) - 0.5) < (golem.panic ? (double)PANIC_RADIUS : (double)DETECT_RADIUS)){
        if (inLineOfSight(golem.location, object, grid))
            return 1;
    }
    return 0;
}

/**
 * @brief Makes a golem patrol and detect the player if he is in it's detection range.
 * 
 * Depending on the situation and randomly, the golem can alter it's course in direction or speed or even both.
 * 
 * @param golem pointer the golem
 * @param player pointer to the player
 * @param grid pointer to the grid
 * @return int 1 if the player was detected, 0 otherwise
 */
int patrolGolem(Golem * golem, Player * player, Grid * grid){

    assert(golem);
    assert(player);
    assert(grid);

    if (golem->panic && willCollide(golem->location, *grid, golem->direction, 1.0)){
        golem->direction = getRandomDirection(golem->direction);
    }
    if (moveGolem(golem, grid)){
        golem->direction = getRandomDirection(golem->direction);
        golem->speed = randRange(0.3, 0.8);
    }

    if (detection(*golem, player->location, grid) && !(player->invisible)){
        player->detected = 1;
        return 1;
    }
    
    return 0;
}

/**
 * @brief For a given golem, makes him check every relic (in the array).
 * 
 * If for a specific relic, the golem finds out for the first time that it has been stolen. The function will return 1.
 * Here, the function will return 1 on the first detection of theft (to not have simultaneous multiple detection which would makes the game easier)
 * 
 * @param golem pointer to the golem
 * @param relic array of relic to be checked
 * @param grid pointer to the grid
 * @param arraySize size of the array of relic
 * @return int 1 if a relic is discovered to be stolen, 0 otherwise
 */
int relicChecking(Golem * golem, Relic * relic, Grid * grid, int arraySize){
    int i;

    assert(golem);
    assert(relic);
    assert(grid);
    assert(arraySize >= 0);

    for (i = 0; i < arraySize; i++){
        if (detection(*golem, relic[i].location, grid) && relic[i].taken){
            /* Check if the golem is already aware that this specific relic is has been stolen */
            /* Avoid having the panic mode being tripped excessively */
            if (!pointInArray(golem->lostRelic, relic->location, golem->lostNb)){
                golem->lostRelic[golem->lostNb] = relic->location;
                golem->lostNb++;
                golem->panic = 30;
                return 1;
            }
        }
    }

    return 0;
}
