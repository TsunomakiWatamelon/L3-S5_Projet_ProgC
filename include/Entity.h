/**
 * @file Entity.h
 * @author HERVE NGUYEN & GABRIEL RADONIAINA
 * @brief Header file for the Entity module
 * @version 0.1
 * @date 2023-01-10
 * 
 * 
 */

#ifndef __Entity__
#define __Entity__

#include "MathTools.h"
#include "Terrain.h"
#define V 0.016
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
   Point lostRelic[3];
   int lostNb;
} Golem;

typedef struct {
    int detected;
    int mana;
    int invisible;
    double speed;
    double speed_max;
    double speed_verstappen;
    Point location;
 } Player;

typedef struct {
   Point location;
   int taken;
} Relic;

#endif
