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
#include "../include/Graphics.h"
#include <stdio.h>

void installWall(Grid *grid, int originX, int originY, int sizeX, int sizeY, int type);

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
 * @brief Generates the borders on the given grid.
 * 
 * @param grid Pointer to the Grid generate the borders
 */
void generateGridBorders(Grid *grid){
    int i;
    for (i = 0; i < MAX_HEIGHT; i++){
        squarePutWall(&(grid->square[i][0]));
        squarePutWall(&(grid->square[i][MAX_WIDTH - 1]));
    }
    for (i = 0; i < MAX_WIDTH; i++){
        squarePutWall(&(grid->square[0][i]));
        squarePutWall(&(grid->square[MAX_HEIGHT - 1][i]));
    }
}

/**
 * @brief Recursive function for generating walls in a subroom of the Grid.
 * 
 * Recursive function that follows a certain algorithm (see project subject in french)
 * 
 * @param square Pointer to a two-dimensional array of square, represents the Grid
 * @param originX x coordinate of the upper left square of the current subroom
 * @param originY y coordinate of the upper left square of the current subroom
 * @param sizeX horizontal size of the current subroom
 * @param sizeY vertical size of the current subroom
 */
void generateWallSubroom(Grid *grid, int originX, int originY, int sizeX, int sizeY){
    int random;
    /*
    fprintf(stderr, "generateWallSubroom : oX %d oY %d sX %d sY %d\n", originX, originY, sizeX, sizeY);
    */
    assert(sizeX <= MAX_WIDTH);
    assert(0 <= sizeX); 
    assert(sizeY <= MAX_HEIGHT);
    assert(0 <= sizeY);

    if ((sizeX <= 2 * MIN_SIDE + 1) && (sizeY <= 2 * MIN_SIDE + 1)){
        return;
    }
    
    if (sizeY < sizeX){
        if (sizeX <= 2 * MIN_SIDE + 1){
            return;
        }
        if (sizeX < 4 * MIN_SIDE){
            if ((random = rand() % 2)){
                return;
            }
        }
        installWall(grid, originX, originY, sizeX, sizeY, 1);
    }
    else {
        if (sizeY <= 2 * MIN_SIDE + 1){
            return;
        }
        if (sizeY < 4 * MIN_SIDE){
            if ((random = rand() % 2)){
                return;
            }
        }
        installWall(grid, originX, originY, sizeX, sizeY, 0);
    }


}


/**
 * @brief Subfunction that creates a wall in the given subroom
 * 
 * Recursive function that follows a certain algorithm (see project subject in french)
 * 
 * The wall is vertical or horizontal depending on the value of the integer : vertical
 * 
 * @param square Pointer to a two-dimensional array of square, represents the Grid
 * @param originX x coordinate of the upper left square of the current subroom
 * @param originY y coordinate of the upper left square of the current subroom
 * @param sizeX horizontal size of the current subroom
 * @param sizeY vertical size of the current subroom
 * @param type tells the function if the wall should be vertical or not (1 yes, 0 no)
 */
void installWall(Grid *grid, int originX, int originY, int sizeX, int sizeY, int type){
    int wallIndex, randomOpening, offset, i;
    int nmod, mod;
    int loop;

    assert(originX >= 0);
    assert(originX + sizeX <= MAX_WIDTH);
    assert(sizeX <= MAX_WIDTH);
    assert(originY >= 0);
    assert(originY + sizeY <= MAX_HEIGHT);
    assert(sizeY <= MAX_HEIGHT);

    if (type){
        assert(sizeX <= MAX_WIDTH);
        assert((2 * MIN_SIDE + 1) <= sizeX); 
        assert(sizeY <= MAX_HEIGHT);
        assert(MIN_SIDE <= sizeY);

    }
    else{
        assert(sizeX <= MAX_WIDTH);
        assert(MIN_SIDE <= sizeX); 
        assert(sizeY <= MAX_HEIGHT);
        assert((2 * MIN_SIDE + 1) <= sizeY);
    }

    /* Location of the opening */
    randomOpening = rand() % 2;
    offset = randomOpening * 3;

    mod = type ? sizeY : sizeX;
    nmod = type ? sizeX : sizeY;

    loop = 0;
    /* Determining the size of the subrooms, in other words the location of the wall */
    do {
        wallIndex = rand() % mod;
        loop++;
        if (loop == 100){
            /* Particular case */
            return;
        }
    } while(((wallIndex < MIN_SIDE) || (nmod - wallIndex - 1 < MIN_SIDE)));

    for (i = 0; i < mod - 3; i++){
        type ? squarePutWall(&(grid->square[originY + offset + i][originX + wallIndex]))
             : squarePutWall(&(grid->square[originY + wallIndex][originX + offset + i]));
    }
    if (type){
        generateWallSubroom(grid, originX, originY, wallIndex, sizeY);
        generateWallSubroom(grid, originX + wallIndex + 1, originY, sizeX - wallIndex - 1, sizeY);
    }
    else {
        generateWallSubroom(grid, originX, originY, sizeX, wallIndex);
        generateWallSubroom(grid, originX, originY + wallIndex + 1, sizeX, sizeY - wallIndex - 1);
    }
}

/**
 * @brief Generates walls the grid using a recursive function.
 * 
 * @param grid Pointer to a Grid object representing the grid to generate walls in.
 */
void generateWallGrid(Grid *grid){
    generateWallSubroom(grid, 1, 1, MAX_WIDTH - 2, MAX_HEIGHT - 2);
}

/**
 * @brief Initializes a grid with empty squares and generates walls in it and the borders.
 * 
 * @param grid Pointer to a Grid object to initialize and generate walls in.
 */
void initializeTerrain(Grid *grid){
    initEmptyGrid(grid);
    generateGridBorders(grid);
    generateWallGrid(grid);
}
