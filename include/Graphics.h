/**
 * @file Graphics.h
 * @author Herve Nguyen (herve.nguyen@edu.univ-eiffel.fr)
 * @brief Header file for the graphics module
 * @version 0.1
 * @date 2023-01-06
 * 
 * 
 */

#ifndef __graphics__
#define __graphics__

#include <MLV/MLV_all.h>
#include <stdio.h>
#include "Entity.h"
#include "assert.h"
#include "Terrain.h"

#define GAME_WINX 1200
#define GAME_WINY 1000

/**
 * @brief Creates the window
 * 
 */
void createWindow(void);

/**
 * @brief Draws the terrain by wiping all previous drawings, drawing the squares containing mana, the walls, and the grid
 * 
 * @param grid the grid containing information about the squares with mana and the walls
 */
void drawTerrain(Grid grid);

/**
 * @brief Redraw a certain subspace by wiping all previous drawings, drawing the squares containing mana, the walls, and the grid
 * 
 * @param grid the grid containing information about the squares with mana and the walls
 * @param x x coordinate of the top left corner of the subspace
 * @param y y coordinate of the top left corner of the subspace
 * @param width width of the subspace (in squares, not pixels)
 * @param height height of the subspace (in squares, not pixels)
 */
void redrawSubspace(Grid grid, int x, int y, int width, int height);

/**
 * @brief Draws the player
 * 
 * @param player the player
 */
void drawPlayer(Player player);

/**
 * @brief Draw the golems and their detection radii
 * 
 * @param golems the array of golems
 * @param arraySize the size of the golems array
 */
void drawGolems(Golem *golems, int arraySize);

/**
 * Redraws the area surrounding a player on the game field.
 *
 * @param player the player whose surrounding area should be redrawn
 * @param grid the grid containing information about the walls and mana
 */
void redrawSubspacePlayer(Player player, Grid grid);

/**
 * Redraws the area surrounding a golem on the game field.
 *
 * @param golem the golem whose surrounding area should be redrawn
 * @param grid the grid containing information about the walls and mana
 */
void redrawSubspaceGolem(Golem golem, Grid grid);

/**
 * Redraws the area surrounding an entity on the game field.
 *
 * @param x the x-coordinate of the center of the surrounding area
 * @param y the y-coordinate of the center of the surrounding area
 * @param grid the grid containing information about the walls and mana
 */
void redrawSubspaceEntity(int x, int y, int width, int height, Grid grid);

void drawEntities(Grid grid, Player player, Golem * golems, Relic * relics, int lenGolem, int lenRelics);

void drawInfo(int timeElapsed, int mana, int collected, int invisible, int boost, int alert);

void drawGameOver();



#endif