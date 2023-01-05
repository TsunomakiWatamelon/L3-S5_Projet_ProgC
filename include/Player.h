/**
 * @file Move.h
 * @author Gabiel Radoniaina (radoniaina@edu.univ-eiffel.fr)
 * @brief Header file for Move module
 * @version 0.1
 * @date 2022-11-07
 * 
 * 
 */

#ifndef __Player__
#define __Player__

#include "Entity.h"

 /**
 * @brief init player
 * 
 * @param player player
 */
void init_Player(Player * player);

/**
 * @brief performs the movement of the player
 * 
 * @param player player
 * @param direction direction(up, down, left, right)
 */
void move(Player * player, Direction direction);

/**
 * @brief performs an acceleration
 * 
 * @param player player
 * @param thrust 1 if player tries to thrust 0 otherwise
 * @return int mana used
 */
int accel(Player * player, int thrust);

/**
 * @brief tries to use the invisibility ability
 * 
 * @param player player
 * @return int mana used
 */
int useInvisibility(Player * player);

 #endif

