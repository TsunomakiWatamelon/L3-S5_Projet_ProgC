
/**
 * @file Move.h
 * @author Gabiel Radoniaina (radoniaina@edu.univ-eiffel.fr)
 * @brief Header file for Move module
 * @version 0.1
 * @date 2022-11-07
 * 
 * 
 */

#include <stdio.h>
#include "../include/Entity.h"

void init_Player(Entity * player){
    player->detected = 0;
    player->speed = 0.1;
    player->speed_max = 0.9;
    player->location.x = 2;
    player->location.y = 2;
}