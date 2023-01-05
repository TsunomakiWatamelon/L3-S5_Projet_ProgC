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
#include "Collision.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>




int moveGolem(Golem * golem, Grid * grid);
void initGolem(Golem * golem, Point location);
int detection(Point golem, Point player, Grid *grid);

 #endif