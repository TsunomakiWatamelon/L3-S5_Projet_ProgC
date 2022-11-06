/**
 * @file Terrain.h
 * @author Herve Nguyen (herve.nguyen@edu.univ-eiffel.fr)
 * @brief Header file for the Terrain module
 * @version 0.1
 * @date 2022-11-06
 * 
 * 
 */

#ifndef terrain
#define terrain

#define MAX_HEIGHT 60
#define MAX_WIDTH 35

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



#endif