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
#include <assert.h>

typedef struct {
    int x;
    int y;
} Coordinate;

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

#endif
