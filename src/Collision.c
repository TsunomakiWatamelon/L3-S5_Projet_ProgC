/**
 * @file Collision.c
 * @author Herve Nguyen (herve.nguyen@edu.univ-eiffel.fr)
 * @brief Source file for the Collision module
 * @version 0.1
 * @date 2022-12-15
 * 
 * 
 */

#include "../include/Collision.h"
#define sqr(x) ((x) * (x))

int isLimit(Coordinate target, Grid grid){
    if (target.x >= MAX_WIDTH || target.x < 0)
        return 1;
    if (target.y >= MAX_HEIGHT || target.y < 0)
        return 1;

    return grid.square[target.y][target.x].isWall;
}

int nextCoordinate(Point *center, Coordinate *target, Direction d){
    int x;
    int y;
    
    assert(target);

    x = center->x;
    y = center->y;
    if (d == left)
        x -= 1;
    else if (d == right)
        x += 1;
    else if (d == up)
        y -= 1;
    else
        y += 1;
    
    target->x = x;
    target->y = y;

    return 1;
}

static int isCollisionA_Vertical(Point *center, Direction d){
    double step, limit;
    double x, y;
    int absY, absX;

    assert((d == up || d == down));

    x = center->x;
    y = center->y;
    absX = (int)center->x;
    absY = (int)center->y;

    if (d == up){
        limit = absY - 0.5;
        if (center->y <= limit){
            center->y = limit;
            return 1;
        }
    }
    else {
        limit = absY + 0.5;
        if (center->y >= limit){
            center->y = limit;
            return 1;
        }
    }

    return 0;
}

static int isCollisionA_Horizontal(Point *center, Direction d){
    double step, limit;
    double x, y;
    int absY, absX;

    assert((d == left || d == right));

    x = center->x;
    y = center->y;
    absX = (int)center->x;
    absY = (int)center->y;

    if (d == left){
        limit = absX - 0.5;
        if (center->x <= limit){
            center->x = limit;
            return 1;
        }
    }
    else {
        limit = absX + 0.5;
        if (center->x >= limit){
            center->x = limit;
            return 1;
        }
    }

    return 0;
}

static int isCollisionA(Point *center, Direction d){
    if (d == left || d == right){
        return isCollisionA_Horizontal(center, d);
    }
    else {
        return isCollisionA_Vertical(center, d);
    }
    return 0;
}

static int isCollisionB_Vertical(Point *center, Direction d){
    double step, limit, delta;
    double x, y;
    int absY, absX;

    assert((d == up || d == down));

    x = center->x;
    y = center->y;
    absX = (int)center->x;
    absY = (int)center->y;

    if (d == up){
        delta = absX + 1.0 - x;
        limit = (absY - 1.0 + sqrt(0.25 - sqr(delta)));
        if ((x > absX + 0.5) &&
            y <= limit)
        {
            center->y = limit;
            return 1;
        }
    }

    else {
        delta = x - absX;
        limit = (absY + 1.0 - sqrt(0.25 - sqr(delta)));
        if ((x < absX + 0.5) &&
            (y >= limit))
        {
            center->y = limit;
            return 1;
        }
    }
}

static int isCollisionB_Horizontal(Point *center, Direction d){
    double step, limit, delta;
    double x, y;
    int absY, absX;

    assert((d == left || d == right));

    x = center->x;
    y = center->y;
    absX = (int)center->x;
    absY = (int)center->y;

    if (d == left){
        delta = absY + 1.0 - y;
        limit = (absX - 1.0 + sqrt(0.25 - sqr(delta)));
        if ((y > absY + 0.5) &&
            x <= limit)
        {
            center->x = limit;
            return 1;
        }
    }

    else {
        delta = y - absY;
        limit = (absX + 1.0 - sqrt(0.25 - sqr(delta)));
        if ((y < absY + 0.5) &&
            (x >= limit))
        {
            center->x = limit;
            return 1;
        }
    }
}

static int isCollisionB(Point *center, Direction d){
    if (d == left || d == right){
        return isCollisionA_Horizontal(center, d);
    }
    else {
        return isCollisionA_Vertical(center, d);
    }
    return 0;
}

static int isCollisionC_Vertical(Point *center, Direction d){
    double limit, delta;
    double x, y;
    int absY, absX;

    assert((d == up || d == down));

    x = center->x;
    y = center->y;
    absX = (int)center->x;
    absY = (int)center->y;

    if (d == up){
        delta = x - absX;
        limit = (absY - 1.0 + sqrt(0.25 - sqr(delta)));
        if ((x > absX + 0.5) &&
            y <= limit)
        {
            center->y = limit;
            return 1;
        }
    }

    else {
        delta = absX + 1.0 - x;
        limit = (absY + 1.0 - sqrt(0.25 - sqr(delta)));
        if ((x < absX + 0.5) &&
            (y >= limit))
        {
            center->y = limit;
            return 1;
        }
    }
}

static int isCollisionB_Horizontal(Point *center, Direction d){
    double step, limit, delta;
    double x, y;
    int absY, absX;

    assert((d == left || d == right));

    x = center->x;
    y = center->y;
    absX = (int)center->x;
    absY = (int)center->y;

    if (d == left){
        delta = y - absY;
        limit = (absX - 1.0 + sqrt(0.25 - sqr(delta)));
        if ((y > absY + 0.5) &&
            x <= limit)
        {
            center->x = limit;
            return 1;
        }
    }

    else {
        delta = absY + 1.0 - y;
        limit = (absX + 1.0 - sqrt(0.25 - sqr(delta)));
        if ((y < absY + 0.5) &&
            (x >= limit))
        {
            center->x = limit;
            return 1;
        }
    }
}

static int isCollisionC(Point *center, Direction d){
    return 0;
}

int isCollision(Point *center, Grid grid, Direction d){
    double radius;
    Coordinate targetA, targetB, targetC;

    radius = 1.0;

    nextCoordinate(center, &targetA, d);      
    targetB = targetA;
    targetC = targetA;
    if (directionIsHorizontal(d)){
        targetB.x -= 1;
        targetC.x -= 1;
    }
    else{
        targetB.y -= 1;
        targetC.y -= 1;
    }
    if (isLimit(targetA, grid) && isCollisionA(center, d))
        return 1;
    if (isLimit(targetB, grid) && isCollisionB(center, d))
        return 1;
    if (isLimit(targetC, grid) && isCollisionC(center, d))
        return 1;
    
        
}