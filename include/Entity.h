/**
 * @file Entity.h
 * @author HERVE NGUYEN & GABRIEL RADONIAINA
 * @brief Header file for common data structure between the player, golems and relics.
 * @version 0.1
 * @date 2023-01-10
 * 
 * 
 */

#ifndef __Entity__
#define __Entity__

#define NDEBUG

#include "MathTools.h"
#include "Terrain.h"

/**
 * @brief Reference speed for the golem and the player, their speed is linked to this value
 * 
 */
#define V 0.016

/**
 * @brief Radius of detection for a normal golem
 * 
 */
#define DETECT_RADIUS 4
/**
 * @brief Radius of detection for a panicking golem
 * 
 */
#define PANIC_RADIUS 6

/**
 * @brief Enum that represents one of the 4 directions
 * 
 */
typedef enum {
    up, down, left, right
 } Direction;

/**
 * @brief Represents the golem and contains informations decribiting it
 * 
 */
typedef struct {
   Direction direction;
   double speed;
   int panic;
   Point location;
   Point lostRelic[3];
   int lostNb;
} Golem;

/**
 * @brief Represents the player and contains informations decribiting it
 * 
 */
typedef struct {
    int detected;
    int mana;
    int invisible;
    double speed;
    double speed_max;
    /**
     * @brief a "pun" around the current F1 World Champion, represents the maximum speed but during the boost / thrust phase
     * 
     */
    double speed_verstappen;
    Point location;
 } Player;

/**
 * @brief Represents a relic
 * 
 */
typedef struct {
   Point location;
   int taken;
} Relic;

#endif
