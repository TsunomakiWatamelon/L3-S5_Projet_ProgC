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
#include "Collision.h"

/**
 * @brief initalizes the player in game start conditions
 * 
 * @param player Pointer to the player
 */
void init_Player(Player * player);

/**
 * @brief performs the movement of the player
 * 
 * @param player player
 * @param direction direction(up, down, left, right)
 * @param grid pointer to the grid that has information about possible walls
 */
void move(Player * player, Direction direction, Grid *grid);

/**
 * @brief performs an acceleration
 * 
 * @param player Pointer to the player
 * @param thrust 1 if player tries to thrust 0 otherwise
 * @return int mana used
 */
int accel(Player * player, int thrust);

/**
 * @brief tries to use the invisibility ability
 * 
 * @param player Pointer to the player
 * @return int mana used
 */
int useInvisibility(Player * player);

/**
 * @brief Resets the speed of the player
 * 
 * @param player Pointer to the player
 */
void resetSpeed(Player * player);

 #endif

