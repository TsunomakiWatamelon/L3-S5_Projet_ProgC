/**
 * @file Terrain.h
 * @author Herve Nguyen (herve.nguyen@edu.univ-eiffel.fr)
 * @brief Header file for the Terrain module
 * @version 0.1
 * @date 2022-11-12
 * 
 * 
 */

#ifndef terrain
#define terrain

#include <assert.h>
#include <stdlib.h>


#define MAX_HEIGHT 45
#define MAX_WIDTH 60
#define MIN_SIDE 9

typedef struct square {
    int isWall;
    int hasMana;
    int x;
    int y;
} Square;

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
 * @brief Sets the given square as a wall
 * 
 * The square will have no mana.
 * 
 * @param square Pointer to the square to set as a wall
 */
void squarePutWall(Square *square);

/**
 * @brief Initializes a grid with empty squares and generates walls in it and the borders.
 * 
 * @param grid Pointer to a Grid object to initialize and generate walls in.
 */
void initializeTerrain(Grid *grid);

#endif
