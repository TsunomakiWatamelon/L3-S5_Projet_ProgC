/**
 * @file Relic.h
 * @author HERVE NGUYEN (herve.nguyen@edu.univ-eiffel.fr)
 * @brief Header file for the Relic module
 * @version 0.1
 * @date 2023-01-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __relic__
#define __relic__

#include <Entity.h>
#include <assert.h>

/**
 * @brief Takes the relic, if it has not been taken already
 * 
 * @param relic pointer to the relic
 * @return int 1 if the relic has been taken by calling the function, 0 if it was already taken
 */
int takeRelic(Relic *relic);

/**
 * @brief Set the location of a given relic.
 * 
 * @param relic the given relic
 * @param location the new location
 */
void setLocation(Relic *relic, Point location);

#endif
