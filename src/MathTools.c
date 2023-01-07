
/**
 * @file MathTools.c
 * @author HERVE NGUYEN (herve.nguyen@edu.univ-eiffel.fr)
 * @brief Source file for the MathTools module
 * @version 0.1
 * @date 2023-01-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../include/MathTools.h"

/**
 * @brief Generates a random value within a given range.
 *
 * @param min the minimum value
 * @param max the maximum value
 * @return the generated value
 */
double randRange(double min, double max){
    assert(min > 0);
    assert(max >= min);
    return min + (rand() / RAND_MAX) * (max - min);
}

/**
 * @brief Returns a boolean indicating whether an event occurs with a given probability.
 *
 * @param probability the probability of the event occurring, between 0 and 1
 * @return 1 if the event occurs, 0 otherwise
 */
int getProbability(double probability){
    return rand() <  probability * ((double)RAND_MAX + 1.0);
}

/**
 * @brief Returns a random direction different from a given direction.
 *
 * @param direction the current direction
 * @return the new random direction
 */
int getRandomDirection(int direction){
    int newDirection;
    newDirection = direction;
    while(newDirection == direction){
        newDirection = rand() % 4;
    }
    return newDirection;
}

/**
 * @brief Rounds a double value to the nearest integer.
 *
 * @param value the value to round
 * @return the rounded value
 */
int roundToInt(double value){
    if (value < 0) {
        return (int)(value - 0.5);
    } else {
        return (int)(value + 0.5);
    }
}

/**
 * @brief Clamps a value to a given range.
 *
 * @param value the value to clamp
 * @param min the minimum allowed value
 * @param max the maximum allowed value
 * @return int the clamped value
 */
int clamp(int value, int min, int max){
    if (value < min) {
        return min;
    }
    if (value > max) {
        return max;
    }
    return value;
}

/**
 * @brief Calculates the euclidian distance between two points represented by the couple (x1, y1) and (x2, y2)
 * 
 * @param x1 the x-coordinate of the first point
 * @param y1 the y-coordinate of the first point
 * @param x2 the x-coordinate of the second point
 * @param y2 the y-coordinate of the second point
 * @return double the distance
 */
double distance(double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

/**
 * @brief Calculates the euclidian distance between two points
 * 
 * @param a the irst point
 * @param b the second point
 * @return double the distance
 */
double pointDistance(Point a, Point b){
    return distance(a.x, a.y, b.x, b.y);
}
