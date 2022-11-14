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
 * @brief Generates the borders on the given grid.
 * 
 * @param grid Pointer to the Grid generate the borders
 */
void generateGridBorders(Grid *grid);

/**
 * @brief Main function for generating walls in the Grid.
 * 
 * Recursive function that follows a certain algorithm (see project subject in french)
 * 
 * @param square Pointer to a two-dimensional array of square, represents the Grid
 * @param originX x coordinate of the upper left square of the current subroom
 * @param originY y coordinate of the upper left square of the current subroom
 * @param sizeX horizontal size of the current subroom
 * @param sizeY vertical size of the current subroom
 */
void generateWallSubroom(Square (*square)[MAX_HEIGHT][MAX_WIDTH], int originX, int originY, int sizeX, int sizeY);

/**
 * @brief Subfunction that creates a vertical wall in the given subroom
 * 
 * Recursive function that follows a certain algorithm (see project subject in french)
 * 
 * @param square Pointer to a two-dimensional array of square, represents the Grid
 * @param originX x coordinate of the upper left square of the current subroom
 * @param originY y coordinate of the upper left square of the current subroom
 * @param sizeX horizontal size of the current subroom
 * @param sizeY vertical size of the current subroom
 */
void installWallVertical(Square (*square)[MAX_HEIGHT][MAX_WIDTH], int originX, int originY, int sizeX, int sizeY);

/**
 * @brief Subfunction that creates a horizontal wall in the given subroom
 * 
 * Recursive function that follows a certain algorithm (see project subject in french)
 * 
 * @param square Pointer to a two-dimensional array of square, represents the Grid
 * @param originX x coordinate of the upper left square of the current subroom
 * @param originY y coordinate of the upper left square of the current subroom
 * @param sizeX horizontal size of the current subroom
 * @param sizeY vertical size of the current subroom
 */
void installWallHorizontal(Square (*square)[MAX_HEIGHT][MAX_WIDTH], int originX, int originY, int sizeX, int sizeY);



#endif