/**
 * @file Graphics.c
 * @author Herve Nguyen (herve.nguyen@edu.univ-eiffel.fr)
 * @brief 
 * @version 0.1
 * @date 2023-01-06
 * 
 * 
 */

#include "../include/Graphics.h"

/**
 * @brief Creates the window
 * 
 */
void createWindow(void){
    MLV_create_window("L3 S5 Project - Stealth Game", "Stealth Game", WINX, WINY);
}

/**
 * @brief Draw an entity (the type should describe which one)
 * 
 * type = 0 : player
 * otherwise : golem
 * 
 * @param position 
 * @param type 
 */
static void drawEntity(Point position, MLV_Color color){
    
    assert(0 <= position.x < (double)MAX_WIDTH);
    assert(0 <= position.y < (double)MAX_HEIGHT);

    MLV_draw_filled_circle(roundToInt(position.x * 20.0), roundToInt(position.y * 20.0), 20, color);
}

/**
 * @brief Draws the detection radius of the golem
 * 
 * @param position the positon of the golem
 */
static void drawDetectionRadius(Golem golem){
    Point position;

    position = golem.location;
    if (golem.panic)
        MLV_draw_circle(roundToInt(position.x * 20.0), roundToInt(position.y * 20.0), PANIC_RADIUS, MLV_COLOR_RED1);
    else
        MLV_draw_circle(roundToInt(position.x * 20.0), roundToInt(position.y * 20.0), DETECT_RADIUS, MLV_COLOR_BLUE1);
}

/**
 * @brief Draws the golem and it's detection radius
 * 
 * @param golem the golem
 */
void drawGolem(Golem golem){
    if (golem.panic)
        drawEntity(golem.location, MLV_COLOR_RED1);
    else
        drawEntity(golem.location, MLV_COLOR_BLUE1);
}

/**
 * @brief Draw the golems and their detection radii
 * 
 * @param golems the array of golems
 * @param arraySize the size of the golems array
 */
void drawGolems(Golem *golems, int arraySize){
    int i;

    assert(arraySize >= 0);
    assert(golems);

    /*
        Two separate loop because we don't want the detection radius of a golem to overwrite a part of another golem
    */
    for (i = 0; i < arraySize; i++){
        drawDetectionRadius(golems[i]);
    }
    for (i = 0; i < arraySize; i++){
        drawGolem(golems[i]);
    }
}

/**
 * @brief Draws the player
 * 
 * @param player the player
 */
void drawPlayer(Player player){
    drawEntity(player.location, MLV_COLOR_GOLD1);
}

/**
 * @brief Draw a grid within a certain subspace
 * 
 * @param x x coordinate of the top left corner of the subspace
 * @param y y coordinate of the top left corner of the subspace
 * @param width width of the subspace (in squares not pixel)
 * @param height height of the subspace (in squares not pixel)
 * @param color color of the lines
 */
void drawGridSubspace(int x, int y, int width, int height, MLV_Color color) {
    int i;

    assert(0 <= x);
    assert(x < MAX_WIDTH);
    assert(0 <= y);
    assert(y < MAX_HEIGHT);
    assert(x + width <= MAX_WIDTH);
    assert(y + height <= MAX_HEIGHT);

    for (i = x; i <= x + width; i++) {
        MLV_draw_line(i * 20, y, i * 20, y + height, color);
    }
    for (i = y; i <= y + height; i++) {
        MLV_draw_line(x, i * 20, x + width, i * 20, color);
    }
}

/**
 * @brief Draws the grid
 * 
 */
void drawGrid(){
    drawGridSubspace(0, 0, MAX_WIDTH, MAX_HEIGHT, MLV_COLOR_BLACK);
}

/**
 * @brief Draw the walls within a certain subspace
 * 
 * @param grid the grid (have information about possible existing walls)
 * @param x x coordinate of the top left corner of the subspace
 * @param y y coordinate of the top left corner of the subspace
 * @param width width of the subspace (in squares, not pixels)
 * @param height height of the subspace (in squares, not pixels)
 */
void drawWallsSubspace(Grid grid, int x, int y, int width, int height) {
    int i, j;

    assert(0 <= x);
    assert(x < MAX_WIDTH);
    assert(0 <= y);
    assert(y < MAX_HEIGHT);
    assert(x + width <= MAX_WIDTH);
    assert(y + height <= MAX_HEIGHT);

    for (i = y; i < y + height; i++) {
        for (j = x; j < x + width; j++) {
            if (grid.square[i][j].isWall) {
                MLV_draw_filled_rectangle(i * 20, j * 20, 20, 20, MLV_COLOR_BLACK);
            }
        }
    }
}


/**
 * @brief Draw the walls
 * 
 * @param grid the grid (have information about possible existing walls)
 */
void drawWalls(Grid grid){
    drawWallsSubspace(grid, 0, 0, MAX_WIDTH, MAX_HEIGHT);
}

/**
 * @brief Draw the squares containing mana within a certain subspace
 * 
 * @param grid the grid containing information about the squares with mana
 * @param x x coordinate of the top left corner of the subspace
 * @param y y coordinate of the top left corner of the subspace
 * @param width width of the subspace (in squares, not pixels)
 * @param height height of the subspace (in squares, not pixels)
 */
void drawManaSubspace(Grid grid, int x, int y, int width, int height) {
    assert(0 <= x);
    assert(x < MAX_WIDTH);
    assert(0 <= y);
    assert(y < MAX_HEIGHT);
    assert(x + width <= MAX_WIDTH);
    assert(y + height <= MAX_HEIGHT);

    for (int i = y; i < y + height; i++) {
        for (int j = x; j < x + width; j++) {
            if (grid.square[i][j].hasMana) {
                MLV_draw_filled_rectangle(i * 20, j * 20, 20, 20, MLV_COLOR_WHITE);
            }
        }
    }
}

void drawMana(Grid grid){
    drawManaSubspace(grid, 0, 0, MAX_WIDTH, MAX_HEIGHT);
}

/**
 * @brief Wipes the subspace (paints it in grey completely)
 * 
 */
void wipeSubspace(int x, int y, int width, int height){
    MLV_draw_filled_rectangle(x, y, width * 20, height * 20, MLV_COLOR_GRAY0);
}

/**
 * @brief Wipes the whole field
 * 
 */
void wipeAll(void){
    wipeSubspace(0, 0, MAX_WIDTH, MAX_HEIGHT);
}

/**
 * @brief Initialize the field by wiping all previous drawings, drawing the squares containing mana, the walls, and the grid
 * 
 * @param grid the grid containing information about the squares with mana and the walls
 */
void initializeField(Grid grid){
    wipeAll();
    drawMana(grid);
    drawWalls(grid);
    drawGrid();
}

/**
 * @brief Redraw a certain subspace by wiping all previous drawings, drawing the squares containing mana, the walls, and the grid
 * 
 * @param grid the grid containing information about the squares with mana and the walls
 * @param x x coordinate of the top left corner of the subspace
 * @param y y coordinate of the top left corner of the subspace
 * @param width width of the subspace (in squares, not pixels)
 * @param height height of the subspace (in squares, not pixels)
 */
void redrawSubspace(Grid grid, int x, int y, int width, int height){
    wipeSubspace(x, y, width, height);
    drawManaSubspace(grid, x, y, width, height);
    drawWallsSubspace(grid, x, y, width, height);
    drawGridSubspace(x, y, width, height, MLV_COLOR_BLACK);
}

/**
 * Redraws the area surrounding a golem on the game field.
 *
 * @param golem the golem whose surrounding area should be redrawn
 * @param grid the grid containing information about the walls and mana
 */
void redrawSubspaceGolem(Golem golem, Grid grid) {
    int width, height;
    if (golem.panic) {
        width = 7;
        height = 7;
    } else {
        width = 5;
        height = 5;
    }
    int x = roundToInt(golem.location.x) - width / 2;
    int y = roundToInt(golem.location.y) - height / 2;
    x = clamp(x, 0, MAX_WIDTH - width);
    y = clamp(y, 0, MAX_HEIGHT - height);
    width = clamp(width, 0, MAX_WIDTH - x);
    height = clamp(height, 0, MAX_HEIGHT - y);
    redrawSubspace(grid, x, y, width, height);
}

/**
 * Clamps a value to a given range.
 *
 * @param value the value to clamp
 * @param min the minimum allowed value
 * @param max the maximum allowed value
 * @return the clamped value
 */
int clamp(int value, int min, int max) {
    if (value < min) {
        return min;
    }
    if (value > max) {
        return max;
    }
    return value;
}