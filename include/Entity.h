/**
 * @file Move.h
 * @author Gabiel Radoniaina (radoniaina@edu.univ-eiffel.fr)
 * @brief Header file for Move module
 * @version 0.1
 * @date 2022-11-07
 * 
 * 
 */

#ifndef __Entity__
#define __Entity__

typedef struct {
   double x;
   double y;
} Point;

typedef struct {
    int detected;
    int mana;
    double speed;
    double speed_max;
    Point location;
 } Entity;


 #endif