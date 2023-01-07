/**
 * @file Collision.h
 * @author Herve Nguyen (herve.nguyen@edu.univ-eiffel.fr)
 * @brief Header file for the Collision module
 * @version 0.1
 * @date 2022-12-15
 * 
 * 
 */

#ifndef collision
#define collision
#include "Entity.h"
#include "Terrain.h"
#include "MathTools.h"
#include <math.h>
#include <assert.h>

/**
 * @brief Checks if the supposed entity of radius 1 described by the point is colliding any walls
 * 
 * The entity's position will be adjusted if there is a collision, so that it's boundaries won't be crossing beyond the walls.
 * 
 * @param center 
 * @param grid 
 * @return int 1 if there is a collision, 0 otherwise
 */
int isCollision(Point *center, Grid grid);

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
int willCollide(Point center, Grid grid, Direction d, double distance);

#endif
