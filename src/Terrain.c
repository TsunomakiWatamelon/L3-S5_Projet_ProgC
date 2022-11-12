/**
 * @file Terrain.c
 * @author Herve Nguyen (herve.nguyen@edu.univ-eiffel.fr)
 * @brief Source file for the Terrain module
 * @version 0.1
 * @date 2022-11-12
 * 
 * 
 */

#include "../include/Terrain.h"
#include <stdio.h>

/**
 * @brief Initializes an empty grid
 * 
 * The grid will have no wall and should have mana on all it's squares.
 * 
 * @param grid Pointer to the Grid to initialize
 */
void initEmptyGrid(Grid *grid){
    int i, j;

    assert(grid != NULL);

    for (i = 0; i < MAX_HEIGHT; i++){
        for (j = 0; j < MAX_WIDTH; j++){
            grid->square[i][j].hasMana = 1;
            grid->square[i][j].isWall = 0;
        }
    }
}

/**
 * @brief Sets the given square as a wall
 * 
 * The square will have no mana.
 * 
 * @param square Pointer to the square to set as a wall
 */
void squarePutWall(Square *square){
    assert(square != NULL);


    square->isWall = 1;
    square->hasMana = 0;
    /* fprintf(stderr,"usdapekora\n"); */
}

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
void generateWallSubroom(Square (*square)[MAX_HEIGHT][MAX_WIDTH], int originX, int originY, int sizeX, int sizeY){
    int random;
    /*
    fprintf(stderr, "generateWallSubroom : oX %d oY %d sX %d sY %d\n", originX, originY, sizeX, sizeY);
    */
    assert(sizeX <= MAX_WIDTH);
    assert(0 <= sizeX); 
    assert(sizeY <= MAX_HEIGHT);
    assert(0 <= sizeY);

    if ((sizeX < 2 * MIN_SIDE + 1) && (sizeY < 2 * MIN_SIDE + 1)){
        return;
    }
    
    if (sizeY < sizeX){
        if (sizeX < 4 * MIN_SIDE){
            if ((random = rand() % 2)){
                return;
            }
        }
        installWallVertical(square, originX, originY, sizeX, sizeY);
    }
    else {
        if (sizeY < 4 * MIN_SIDE){
            if ((random = rand() % 2)){
                return;
            }
        }
        installWallHorizontal(square, originX, originY, sizeX, sizeY);
    }


}

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
void installWallVertical(Square (*square)[MAX_HEIGHT][MAX_WIDTH], int originX, int originY, int sizeX, int sizeY){
    int wallIndex;
    int randomOpening;
    int offset;
    int i;

    assert(sizeX <= MAX_WIDTH);
    assert(2 * MIN_SIDE + 1 <= sizeX); 
    assert(sizeY <= MAX_HEIGHT);
    assert(MIN_SIDE <= sizeY);

    /* Determining the size of the subrooms, in other words the location of the wall */
    do {
        wallIndex = rand() % sizeX;
    } while(!(wallIndex - 1 >= MIN_SIDE) || !(sizeX - wallIndex >= MIN_SIDE));

    /* Location of the opening */
    randomOpening = rand() % 2;
    offset = randomOpening * 3;

    for (i = 0; i < sizeY - 3; i++){
        squarePutWall(&((*square)[originY + offset + i][originX + wallIndex]));
    }
    generateWallSubroom(square, originX, originY, wallIndex, sizeY);
    generateWallSubroom(square, originX + wallIndex + 1, originY, sizeX - wallIndex - 1, sizeY);

}

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
void installWallHorizontal(Square (*square)[MAX_HEIGHT][MAX_WIDTH], int originX, int originY, int sizeX, int sizeY){
    int wallIndex;
    int randomOpening;
    int offset;
    int i;

    assert(sizeX <= MAX_WIDTH);
    assert(MIN_SIDE <= sizeX); 
    assert(sizeY <= MAX_HEIGHT);
    assert(2 * MIN_SIDE + 1 <= sizeY);

    /* Determining the size of the subrooms, in other words the location of the wall */
    do {
        wallIndex = rand() % sizeY;
    } while(!(wallIndex - 1 >= MIN_SIDE) || !(sizeY - wallIndex >= MIN_SIDE));

    /* Location of the opening */
    randomOpening = rand() % 2;
    offset = randomOpening * 3;

    for (i = 0; i < sizeX - 3; i++){
        squarePutWall(&((*square)[originY + wallIndex][originX + offset + i]));
    }
    generateWallSubroom(square, originX, originY, sizeX, wallIndex);
    generateWallSubroom(square, originX, originY + wallIndex + 1, sizeX, sizeY - wallIndex - 1);
}
