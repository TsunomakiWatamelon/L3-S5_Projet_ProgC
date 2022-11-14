
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
#include "../include/Player.h"

/**
 * @brief init player
 * 
 * @param player player
 */
void init_Player(Player * player){
    player->detected = 0;
    player->speed = 0.1;
    player->speed_max = 0.9;
    player->location.x = 2;
    player->location.y = 2;
    player->mana = 0;
    player->invisible = V;
}

/**
 * @brief performs the movement of the player
 * 
 * @param player player
 * @param direction direction(up, down, left, right)
 */
void move(Player * player, Direction direction){
    switch (direction){
        case up: player->location.y -= player->speed * V;
        case down: player->location.y += player->speed * V;
        case left: player->location.x -= player->speed * V;
        case right: player->location.x -= player->speed * V;
    }
 }

/**
 * @brief performs an acceleration
 * 
 * @param player player
 * @param thrust 1 if player tries to thrust 0 otherwise
 * @return int mana used
 */
int accel(Player * player, int thrust){
    int maxSpeed, acceleration, manaUsed;
    maxSpeed = player->speed_max;
    acceleration = 0.03; 
    manaUsed = 0;
    if(thrust && player->mana >= 2){
        maxSpeed = 1.2;
        /*acceleration value change when thrusting*/
        acceleration = 0.06;
        player->mana -= 2;
        manaUsed = 2;
    }
    if(player->speed < maxSpeed){
        player->speed += acceleration;
        if(player->speed > maxSpeed)
            player->speed = maxSpeed;
    }
    return manaUsed;
 }

/**
 * @brief tries to use the invisibility ability
 * 
 * @param player player
 * @return int mana used
 */
int useInvisibility(Player * player){
    if(player->mana == 0){
        player->invisible = 0;
        return 0;
    }
    player->invisible = 1;
    player->mana--;
    return 1;
}


