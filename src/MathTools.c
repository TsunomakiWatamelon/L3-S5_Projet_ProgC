
#include "../include/MathTools.h"

double randRange(double min, double max){
    assert(min > 0);
    assert(max >= min);
    return min + (rand() / RAND_MAX) * (max - min);
}


int getProbability(int probability){
    return rand() <  probability * ((double)RAND_MAX + 1.0);
}

int getRandomDirection(int direction){
    int newDirection;
    newDirection = direction;
    while(newDirection == direction){
        newDirection = rand() % 4;
    }
    return newDirection;
}

int roundToInt(double value){
    if (value < 0) {
        return (int)(value - 0.5);
    } else {
        return (int)(value + 0.5);
    }
}

/**
 * Clamps a value to a given range.
 *
 * @param value the value to clamp
 * @param min the minimum allowed value
 * @param max the maximum allowed value
 * @return the clamped value
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
