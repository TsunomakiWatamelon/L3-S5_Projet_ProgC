/**
 * @file MathTools.h
 * @author HERVE NGUYEN & GABRIEL RADONIAINA
 * @brief Header file for the MathTools module
 * @version 0.1
 * @date 2023-01-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __MathTools__
#define __MathTools__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

typedef struct {
    int x;
    int y;
} Coordinate;

typedef struct {
   double x;
   double y;
} Point;

/**
 * @brief Generates a random value within a given range.
 *
 * @param min the minimum value
 * @param max the maximum value
 * @return the generated value
 */
double randRange(double min, double max);

/**
 * @brief Returns a boolean indicating whether an event occurs with a given probability.
 *
 * @param probability the probability of the event occurring, between 0 and 1
 * @return 1 if the event occurs, 0 otherwise
 */
int getProbability(double probability);

/**
 * @brief Returns a random direction different from a given direction.
 *
 * @param direction the current direction
 * @return the new random direction
 */
int getRandomDirection(int direction);

/**
 * @brief Rounds a double value to the nearest integer.
 *
 * @param value the value to round
 * @return the rounded value
 */
int roundToInt(double value);

/**
 * @brief Clamps a value to a given range.
 *
 * @param value the value to clamp
 * @param min the minimum allowed value
 * @param max the maximum allowed value
 * @return int the clamped value
 */
int clamp(int value, int min, int max);

/**
 * @brief Calculates the euclidian distance between two points represented by the couple (x1, y1) and (x2, y2)
 * 
 * @param x1 the x-coordinate of the first point
 * @param y1 the y-coordinate of the first point
 * @param x2 the x-coordinate of the second point
 * @param y2 the y-coordinate of the second point
 * @return double the distance
 */
double distance(double x1, double y1, double x2, double y2);

/**
 * @brief Calculates the euclidian distance between two points
 * 
 * @param a the irst point
 * @param b the second point
 * @return double the distance
 */
double pointDistance(Point a, Point b);

/**
 * @brief Compares two points
 * 
 * @param a first point
 * @param b second point
 * @return int 1 if their values are equal, 0 otherwise
 */
int pointEquals(Point a, Point b);

/**
 * @brief Checks if a point's value is in the given array
 * 
 * @param array the array of points
 * @param check the point to be searched in the array
 * @param len the length of the array
 * @return int 1 if it's value is present, 0 otherwise
 */
int pointInArray(Point * array, Point check, int len);

#endif
