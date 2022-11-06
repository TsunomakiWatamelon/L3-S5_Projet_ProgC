/**
 * @file Terrain.c
 * @author Herve Nguyen (herve.nguyen@edu.univ-eiffel.fr)
 * @brief Source file for the Terrain module
 * @version 0.1
 * @date 2022-11-06
 * 
 * 
 */

#include "../include/Terrain.h"

/**
 * @brief Initializes an empty grid
 * 
 * The grid will have no wall and should have mana on all it's squares.
 * 
 * @param grid Pointer to the Grid to initialize
 */
void initEmptyGrid(Grid *grid){
    int i, j;

    for (i = 0; i < MAX_HEIGHT; i++){
        for (j = 0; j < MAX_WIDTH; j++){
            grid->square[i][j].hasMana = 1;
            grid->square[i][j].isWall = 0;
        }
    }
}

