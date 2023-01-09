/**
 * @file MathTools.c
 * @author HERVE NGUYEN & GABRIEL RADONIAINA
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
    assert(max >= min);
    return min + drand48() * (max - min);
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

/**
 * @brief Compares two points
 * 
 * @param a first point
 * @param b second point
 * @return int 1 if their values are equal, 0 otherwise
 */
int pointEquals(Point a, Point b){
    return ((a.x == b.x) && (a.y == b.y));
}

/**
 * @brief Checks if a point's value is in the given array
 * 
 * @param array the array of points
 * @param check the point to be searched in the array
 * @param len the length of the array
 * @return int 1 if it's value is present, 0 otherwise
 */
int pointInArray(Point * array, Point check, int len){
    int i;

    for (i = 0; i < len; i++){
        if (pointEquals(array[i], check))
            return 1;
    }
    return 0;
}

void getRandomPoint(Point * point, double x_max, double x_min, double y_max, double y_min){
    assert(point);
    assert(x_min > 0);
    assert(y_min > 0);

    point->x = randRange(x_min, x_max);
    point->y = randRange(y_min, y_max);
}

int positionArrayNotTouching(Point * array, int len){
    int i, j;

    assert(len >= 0);
    assert(array);

    for (i = 0; i < len; i++){
        for (j = i + 1; j < len; j++){
            if (distance(array[i].x, array[i].y, array[j].x, array[j].y) <= 1.0)
                return 0;
        }
    }
    return 1;
}

/**
 * @brief Get the modulo between 0 and b-1 of a.
 * 
 * @param a Dividend
 * @param b Divisor
 * 
 * @return Modulo between 0 and b-1 of a
 */
int goodModulo(int a, int b){
    assert(b > 0);
    if (a % b >= 0) return a % b;
    else return (a % b) + b;
}

/**
 * @brief Convert a number of microseconds to the corresponding number of hours.
 * 
 * @param nb_ms Number of microseconds
 * 
 * @return Number of hours
 */
int microsecondsToHours(int nb_ms){
    return goodModulo(nb_ms / (1000 * 60 * 60), 24);
}


/**
 * @brief Convert a number of microseconds to the corresponding number of minutes.
 * 
 * @param nb_ms Number of microseconds
 * 
 * @return Number of minutes
 */
int microsecondsToMinutes(int nb_ms){
    return goodModulo(nb_ms / (1000 * 60), 60);
}

/**
 * @brief Convert a number of microseconds to the corresponding number of centiseconds.
 * 
 * @param nb_ms Number of microseconds
 * 
 * @return Number of centiseconds
 */
int microsecondsToCentiseconds(int nb_ms){
    return goodModulo(nb_ms / 10, 100);
}

/**
 * @brief Convert a number of microseconds to the corresponding number of seconds.
 * 
 * @param nb_ms Number of microseconds
 * 
 * @return Number of seconds
 */
int microsecondsToSeconds(int nb_ms){
    return goodModulo(nb_ms / 1000, 60);
}
