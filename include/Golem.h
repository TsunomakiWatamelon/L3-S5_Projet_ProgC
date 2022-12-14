/**
 * @file Move.h
 * @author Gabiel Radoniaina (radoniaina@edu.univ-eiffel.fr)
 * @brief Header file for Move module
 * @version 0.1
 * @date 2022-11-07
 * 
 * 
 */

#ifndef __Golem__
#define __Golem__

#include "Entity.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
   Direction direction;
   double detectionRadius;
   double speed;
   int panic;
   Point location;
} Golem;


void moveGolem(Golem * golem);
void initGolem(Golem * golem, Point location);

 #endif