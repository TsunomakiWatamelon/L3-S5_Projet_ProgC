/**
 * @file Move.h
 * @author Gabiel Radoniaina (radoniaina@edu.univ-eiffel.fr)
 * @brief Header file for Golem module
 * @version 0.1
 * @date 2022-11-07
 * 
 * 
 */

#ifndef __Golem__
#define __Golem__

#include "Entity.h"
#include "Collision.h"
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

#endif