
#ifndef __Entity__
#define __Entity__

#include "MathTools.h"
#include "Terrain.h"
#define V 1

typedef enum {
    up, down, left, right
 } Direction;

typedef struct {
   double x;
   double y;
} Point;

#endif