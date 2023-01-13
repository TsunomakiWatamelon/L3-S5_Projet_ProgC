/**
 * @file Golem.h
 * @author HERVE NGUYEN & GABRIEL RADONIAINA
 * @brief Header file for the Golem module
 * @version 0.1
 * @date 2022-11-07
 * 
 */

#ifndef __Golem__
#define __Golem__

#define NDEBUG

#include "Entity.h"
#include "Collision.h"
#include "MathTools.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>




/**
 * @brief Initializes the golem at the given position
 * 
 * @param golem the golem's pointer
 * @param location the location that the golem will be set
 */
void initGolem(Golem * golem, Point location);

/**
 * @brief Moves the golem and check if it is colliding with a wall
 * 
 * @param golem the golem's pointer
 * @param grid the grid's pointer that has information about possible walls
 * @return int 1 if it has collided with a wall, 0 otherwise
 */
int moveGolem(Golem * golem, Grid * grid);

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
int inLineOfSight(Point entity1, Point entity2, Grid *grid);


/**
 * @brief Makes a golem patrol and detect the player if he is in it's detection range.
 * 
 * Depending on the situation and randomly, the golem can alter it's course in direction or speed or even both.
 * 
 * @param golem pointe the golem
 * @param player pointer to the player
 * @param grid pointer to the grid
 * @return int 1 if the player was detected, 0 otherwise
 */
int patrolGolem(Golem * golem, Player * player, Grid * grid);

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
int relicChecking(Golem * golem, Relic * relic, Grid * grid, int arraySize);

#endif