/**
 * @file Terrain.h
 * @author HERVE NGUYEN & GABRIEL RADONIAINA
 * @brief Header file for the Terrain module
 * @version 0.1
 * @date 2022-11-12
 * 
 * 
 */

#ifndef __terrain__
#define __terrain__

#define NDEBUG

#include <assert.h>
#include <stdlib.h>


#define MAX_HEIGHT 45
#define MAX_WIDTH 60
#define MIN_SIDE 9

/**
 * @brief Represents one "square" in the grid
 * 
 */
typedef struct square {
    int isWall;
    int hasMana;
    int x;
    int y;
} Square;

/**
 * @brief Represents the "grid", which is the playing field for the player. It contains an 2D array of squares that can have mana, be a wall, etc.
 * 
 */
typedef struct grid {
    Square square[MAX_HEIGHT][MAX_WIDTH];
} Grid;

/**
 * @brief Initializes an empty grid
 * 
 * The grid will have no wall and should have mana on all it's squares.
 * 
 * @param grid Pointer to the Grid to initialize
 */
void initEmptyGrid(Grid *grid);

/**
 * @brief Initializes a grid with empty squares and generates walls in it and the borders.
 * 
 * @param grid Pointer to a Grid object to initialize and generate walls in.
 */
void initializeTerrain(Grid *grid);

#endif
