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

int isCollision(Point *center, Grid grid, Direction d);

#endif