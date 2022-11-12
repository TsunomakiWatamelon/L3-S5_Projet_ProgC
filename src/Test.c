/**
 * @file Test.c
 * @author Herve Nguyen (herve.nguyen@edu.univ-eiffel.fr)
 * @brief Test file for the Terrain module
 * @version 0.1
 * @date 2022-11-11
 * 
 * 
 */

#include "../include/Terrain.h"
#include <time.h>
#include <stdio.h>

void printGrid(Grid grid){
    int i, j;
    for (i = 0; i < MAX_HEIGHT; i++){
        printf("\n");
        for (j = 0; j < MAX_WIDTH; j++){
            if ((grid.square)[i][j].isWall){
                printf("1");
            }
            else
                printf("0");
        }
    }
    printf("\n");
}

int main(void){
    Grid grid;
    srand(time(NULL));
    initEmptyGrid(&grid);
    generateGridBorders(&grid);
    generateWallSubroom(&(grid.square), 1, 1, MAX_WIDTH - 2, MAX_HEIGHT - 2);
    printGrid(grid);
    return 0;
}