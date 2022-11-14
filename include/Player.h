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

typedef struct {
   double x;
   double y;
} Point;

typedef struct {
    int detected;
    int mana;
    int invisible;
    double speed;
    double speed_max;
    Point location;
 } Player;

typedef enum {
    up, down, left, right
 } Direction;

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
 * @brief performs the acceleration
 * 
 * @param player player
 */
void accel(Player * player, int thrust);

/**
 * @brief uses invisibility
 * 
 * @param player player
 */
void useInvisibility(Player * player);

 #endif