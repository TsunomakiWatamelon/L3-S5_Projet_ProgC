
#ifndef __Entity__
#define __Entity__

#include "MathTools.h"
#include "Terrain.h"
#define V 0.05
#define DETECT_RADIUS 4
#define PANIC_RADIUS 6

typedef enum {
    up, down, left, right
 } Direction;

typedef struct {
   Direction direction;
   double speed;
   int panic;
   Point location;
} Golem;

typedef struct {
    int detected;
    int mana;
    int invisible;
    double speed;
    double speed_max;
    Point location;
 } Player;

typedef struct {
   Point location;
   int taken;
} Relic;

#endif
