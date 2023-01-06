#include "../include/Entity.h"
#include "../include/Collision.h"
#include "../include/Terrain.h"

int test_a(void){
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

int test_b(void){
    Point center;
    Grid grid;

    initEmptyGrid(&grid);

    squarePutWall(&(grid.square[2][0]));
    squarePutWall(&(grid.square[0][2]));

    /* neutral, no collision */
    center.x = 1.5;
    center.y = 1.5;
    if (isCollision(&center, grid) || (center.x != 1.5 || center.y != 1.5)){
        printf("test_b fail at test 1\n");
        return 0;
    }
        
    
    /* collision wall below, type 1 */
    center.x = 1.2;
    center.y = 1.6;
    if (!isCollision(&center, grid)){
        printf("test_b fail at test 2\n");
        return 0;
    }

    /* collision wall below, type 2 */
    center.x = 1.1;
    center.y = 1.55;
    if (!isCollision(&center, grid)){
        printf("test_b fail at test 3\n");
        return 0;
    }

    /* collision wall upwards, type 1 */
    center.x = 1.7;
    center.y = 1.2;
    if (!isCollision(&center, grid)){
        printf("test_b fail at test 4\n");
        return 0;
    }

    /* collision wall upwards, type 2 */
    center.x = 1.7;
    center.y = 1.05;
    if (!isCollision(&center, grid)){
        printf("test_b fail at test 5\n");
        return 0;
    }
    
    return 1;
}

int test_c(void){
    Point center;
    Grid grid;

    initEmptyGrid(&grid);

    squarePutWall(&(grid.square[2][2]));
    squarePutWall(&(grid.square[0][0]));

    /* neutral, no collision */
    center.x = 1.5;
    center.y = 1.5;
    if (isCollision(&center, grid) || (center.x != 1.5 || center.y != 1.5)){
        printf("test_c fail at test 1\n");
        return 0;
    }
        
    
    /* collision wall below, type 1 */
    center.x = 1.8;
    center.y = 1.6;
    if (!isCollision(&center, grid)){
        printf("test_c fail at test 2\n");
        return 0;
    }

    /* collision wall below, type 2 */
    center.x = 1.9;
    center.y = 1.55;
    if (!isCollision(&center, grid)){
        printf("test_c fail at test 3\n");
        return 0;
    }

    /* collision wall upwards, type 1 */
    center.x = 1.3;
    center.y = 1.2;
    if (!isCollision(&center, grid)){
        printf("test_c fail at test 4\n");
        return 0;
    }

    /* collision wall upwards, type 2 */
    center.x = 1.4;
    center.y = 1.05;
    if (!isCollision(&center, grid)){
        printf("test_c fail at test 5\n");
        return 0;
    }
    
    return 1;
}

int main(void){
    if (test_a())
        printf("test_a pass\n");
    if (test_b())
        printf("test_b pass\n");
    if (test_c())
        printf("test_c pass\n");
}
