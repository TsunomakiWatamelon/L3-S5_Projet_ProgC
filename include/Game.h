/**
 * @file Game.h
 * @author HERVE NGUYEN (herve.nguyen@edu.univ-eiffel.fr)
 * @brief 
 * @version 0.1
 * @date 2023-01-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __game__
#define __game__

#define _POSIX_C_SOURCE 199309L

#include "Entity.h"
#include "Collision.h"
#include "Terrain.h"
#include "Graphics.h"
#include "Player.h"
#include "Golem.h"
#include "Relic.h"
#include "MathTools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NB_GOLEM 5
#define NB_RELIC 3

typedef struct {
    Square *depleted[2700];
    int size;
} DepletedSquares;

void game(void);

#endif