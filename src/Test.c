/**
 * @file Test.c
 * @author HERVE NGUYEN (herve.nguyen@edu.univ-eiffel.fr)
 * @brief 
 * @version 0.1
 * @date 2023-01-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../include/Test.h"

/**
 * @brief Testing the type A collisions
 * 
 * @return int 1 if success, otherwise 0
 */
static int collision_a(void){
    Point center;
    Grid grid;

    initEmptyGrid(&grid);

    squarePutWall(&(grid.square[1][1]));
    squarePutWall(&(grid.square[0][1]));
    squarePutWall(&(grid.square[1][0]));

    /* neutral, no collision */
    center.x = 0.5;
    center.y = 0.5;
    if (isCollision(&center, grid) || (center.x != 0.5 || center.y != 0.5))
        return 0;

    /* collision left side */
    center.x = 0.3;
    center.y = 0.5;
    if (!isCollision(&center, grid) || (center.x != 0.5 || center.y != 0.5))
        return 0;

    /* collision right side*/
    center.x = 0.7;
    center.y = 0.5;
    if (!isCollision(&center, grid) || (center.x != 0.5 || center.y != 0.5))
        return 0;

    /* collision downwards */
    center.x = 0.5;
    center.y = 0.3;
    if (!isCollision(&center, grid) || (center.x != 0.5 || center.y != 0.5))
        return 0;

    /* collision upwards */
    center.x = 0.5;
    center.y = 0.7;
    if (!isCollision(&center, grid) || (center.x != 0.5 || center.y != 0.5))
        return 0;

    return 1;
}

/**
 * @brief Testing the type B collisions
 * 
 * @return int 1 if success, otherwise 0
 */
int collision_b(void){
    Point center;
    Grid grid;

    initEmptyGrid(&grid);

    squarePutWall(&(grid.square[2][0]));
    squarePutWall(&(grid.square[0][2]));

    /* neutral, no collision */
    center.x = 1.5;
    center.y = 1.5;
    if (isCollision(&center, grid) || (center.x != 1.5 || center.y != 1.5)){
        printf("collision_b fail at test 1 : %f %f\n", center.x, center.y);
        return 0;
    }
        
    
    /* collision wall below, type 1 */
    center.x = 1.2;
    center.y = 1.6;
    if (!isCollision(&center, grid)){
        printf("collision_b fail at test 2\n");
        return 0;
    }

    /* collision wall below, type 2 */
    center.x = 1.1;
    center.y = 1.55;
    if (!isCollision(&center, grid)){
        printf("collision_b fail at test 3\n");
        return 0;
    }

    /* collision wall upwards, type 1 */
    center.x = 1.7;
    center.y = 1.2;
    if (!isCollision(&center, grid)){
        printf("collision_b fail at test 4\n");
        return 0;
    }

    /* collision wall upwards, type 2 */
    center.x = 1.7;
    center.y = 1.05;
    if (!isCollision(&center, grid)){
        printf("collision_b fail at test 5\n");
        return 0;
    }
    
    return 1;
}

/**
 * @brief Testing the type C collisions
 * 
 * @return int 1 if success, otherwise 0
 */
int collision_c(void){
    Point center;
    Grid grid;

    initEmptyGrid(&grid);

    squarePutWall(&(grid.square[2][2]));
    squarePutWall(&(grid.square[0][0]));

    /* neutral, no collision */
    center.x = 1.5;
    center.y = 1.5;
    if (isCollision(&center, grid) || (center.x != 1.5 || center.y != 1.5)){
        printf("collision_c fail at test 1\n");
        return 0;
    }
        
    
    /* collision wall below, type 1 */
    center.x = 1.8;
    center.y = 1.6;
    if (!isCollision(&center, grid)){
        printf("collision_c fail at test 2\n");
        return 0;
    }

    /* collision wall below, type 2 */
    center.x = 1.9;
    center.y = 1.55;
    if (!isCollision(&center, grid)){
        printf("collision_c fail at test 3\n");
        return 0;
    }

    /* collision wall upwards, type 1 */
    center.x = 1.3;
    center.y = 1.2;
    if (!isCollision(&center, grid)){
        printf("collision_c fail at test 4\n");
        return 0;
    }

    /* collision wall upwards, type 2 */
    center.x = 1.4;
    center.y = 1.05;
    if (!isCollision(&center, grid)){
        printf("collision_c fail at test 5\n");
        return 0;
    }
    
    return 1;
}




/**
 * @brief Runs the tests for the collisions
 * 
 * @return int 1
 */
int collisions(void){
    if (collision_a())
        printf("collision_a pass\n");
    else {
        printf("collision_a fail\n");
        return 0;
    }
    if (collision_b())
        printf("collision_b pass\n");
    else {
        printf("collision_b fail\n");
        return 0;
    }
    if (collision_c())
        printf("collision_c pass\n");
    else {
        printf("collision_c fail\n");
        return 0;
    }
    
    return 1;
}

void graphics(void){
    Grid grid;
    Player player;
    Golem golem;
    Point a, b;

    a.x = 2.4; a.y = 4.2;
    b.x = 5.2; b.y = 7.6;

    srand(time(NULL));
    createWindow();
    init_Player(&player);
    initGolem(&golem, a);
    initializeTerrain(&grid);
    drawTerrain(grid);
    redrawSubspacePlayer(player, grid);
    drawPlayer(player);
    drawGolems(&golem, 1);
    MLV_actualise_window();
    MLV_wait_seconds(15);
}

/**
 * @brief Runs the tests below and will show the results of each tests
 * 
 * @return int 1
 */
int test(void){
    collisions() ? printf("Result : Collisions pass\n") : printf("Result : Collisions fail\n");
    graphics();
    return 1;
}