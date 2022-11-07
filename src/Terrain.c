/**
 * @file Terrain.c
 * @author Herve Nguyen (herve.nguyen@edu.univ-eiffel.fr)
 * @brief Source file for the Terrain module
 * @version 0.1
 * @date 2022-11-07
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
}

/**
 * @brief Main function for generating walls in the Grid.
 * 
 * Recursive function that follows a certain algorithm (see project subject in french)
 * 
 * @param square Two-dimensional array of square, represents the Grid
 * @param originX x coordinate of the upper left square of the current subroom
 * @param originY y coordinate of the upper left square of the current subroom
 * @param sizeX horizontal size of the current subroom
 * @param sizeY vertical size of the current subroom
 */
void generateWallSubroom(Square **square, int originX, int originY, int sizeX, int sizeY){
    int random;
    assert(sizeX < MAX_WIDTH);
    assert(0 <= sizeX); 
    assert(sizeY < MAX_HEIGHT);
    assert(0 <= sizeY);

    if ((sizeX < 2 * MIN_SIDE + 1) && (sizeY < 2 * MIN_SIDE + 1)){
        return;
    }
    
    if (sizeY < sizeX){
        if (sizeX < 4 * MIN_SIDE){
            if (random = rand() % 2){
                return;
            }
        }
        installWallVertical(square, originX, originY, sizeX, sizeY);
    }
    else {
        if (sizeY < 4 * MIN_SIDE){
            if (random = rand() % 2){
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
 * @param square Two-dimensional array of square, represents the Grid
 * @param originX x coordinate of the upper left square of the current subroom
 * @param originY y coordinate of the upper left square of the current subroom
 * @param sizeX horizontal size of the current subroom
 * @param sizeY vertical size of the current subroom
 */
void installWallVertical(Square **square, int originX, int originY, int sizeX, int sizeY){
    int randomSize;
    int randomOpening;
    int offset;
    int i;

    assert(sizeX < MAX_WIDTH);
    assert(MIN_SIDE <= sizeX); 
    assert(sizeY < MAX_HEIGHT);
    assert(MIN_SIDE <= sizeY);

    /* Determining the size of the subrooms, in other words the location of the wall */
    do {
        randomSize = rand() % sizeX;
    } while(!(randomSize - 1 > MIN_SIDE) || !(sizeX - (randomSize + 1) > MIN_SIDE));

    /* Location of the opening */
    randomOpening = random() % 2;
    offset = randomOpening * 3;

    for (i = 0; i < sizeY - 3; i++){
        squarePutWall(&(square[originY + randomOpening][originX + randomSize]));
    }

    generateWallSubroom(square, originX, originY, randomSize - 1, sizeY);
    generateWallSubroom(square, originX, originY + randomSize + 1, sizeX - (randomSize + 1), sizeY);

}

/**
 * @brief Subfunction that creates a horizontal wall in the given subroom
 * 
 * Recursive function that follows a certain algorithm (see project subject in french)
 * 
 * @param square Two-dimensional array of square, represents the Grid
 * @param originX x coordinate of the upper left square of the current subroom
 * @param originY y coordinate of the upper left square of the current subroom
 * @param sizeX horizontal size of the current subroom
 * @param sizeY vertical size of the current subroom
 */
void installWallHorizontal(Square **square, int originX, int originY, int sizeX, int sizeY){
    int randomSize;
    int randomOpening;
    int offset;
    int i;

    assert(sizeX < MAX_WIDTH);
    assert(MIN_SIDE <= sizeX); 
    assert(sizeY < MAX_HEIGHT);
    assert(4 * MIN_SIDE <= sizeY);

    /* Determining the size of the subrooms, in other words the location of the wall */
    do {
        randomSize = rand() % sizeY;
    } while(!(randomSize - 1 > MIN_SIDE) || !(sizeY - (randomSize + 1) > MIN_SIDE));

    /* Location of the opening */
    randomOpening = random() % 2;
    offset = randomOpening * 3;

    for (i = 0; i < sizeX - 3; i++){
        squarePutWall(&(square[originY + randomSize][originX + randomOpening]));
    }

    generateWallSubroom(square, originX, originY, sizeX, randomSize - 1);
    generateWallSubroom(square, originX, originY + randomSize + 1, sizeX, sizeY - (randomSize + 1));

}
