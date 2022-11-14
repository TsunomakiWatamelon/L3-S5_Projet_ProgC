/**
 * @file Move.c
 * @author Gabiel Radoniaina (radoniaina@edu.univ-eiffel.fr)
 * @brief Source file for Move module
 * @version 0.1
 * @date 2022-11-07
 * 
 * 
 */

#include <stdio.h>
#include "../include/Move.h"
#include "../include/Entity.h"

 void move(Entity * entity, Direction direction){
    switch (direction){
        case up: entity->location.y -= entity->speed;
        case down: entity->location.y += entity->speed;
        case left: entity->location.x -= entity->speed;
        case right: entity->location.x -= entity->speed;
    }
 }


