/**
 * @file MathTools.h
 * @author HERVE NGUYEN & GABRIEL RADONIAINA
 * @brief 
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
#include <math.h>

double randRange(double min, double max);
int getProbability(int probability);
int roundToInt(double value);

/**
 * Clamps a value to a given range.
 *
 * @param value the value to clamp
 * @param min the minimum allowed value
 * @param max the maximum allowed value
 * @return the clamped value
 */
int clamp(int value, int min, int max);

#endif
