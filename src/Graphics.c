/**
 * @file Graphics.c
 * @author HERVE NGUYEN & GABRIEL RADONIAINA
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
    MLV_create_window("L3 S5 Project - Stealth Game", "Stealth Game", GAME_WINX, GAME_WINY);
}

/**
 * @brief Draw an entity (the type should describe which one)
 * 
 * @param position 
 * @param color
 */
static void drawEntity(Point position, MLV_Color color){
    
    assert(position.x < (double)MAX_WIDTH);
    assert(0 <= position.x);
    assert(position.y < (double)MAX_HEIGHT);
    assert(0 <= position.y);

    MLV_draw_filled_circle(roundToInt(position.x * 20.0), roundToInt(position.y * 20.0), 10, color);
}

/**
 * @brief Draws the detection radius of the golem
 * 
 * The color and radius depends on the state of the golem (panic or not)
 * 
 * @param position the positon of the golem
 */
static void drawDetectionRadius(Golem golem){
    Point position;
    int radius;
    MLV_Color color;

    position = golem.location;
    radius = golem.panic ? PANIC_RADIUS : DETECT_RADIUS;
    color = golem.panic ? MLV_COLOR_RED1 : MLV_COLOR_BLUE1;

    MLV_draw_circle(roundToInt(position.x * 20.0), roundToInt(position.y * 20.0), radius * 20, color);
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
    MLV_Color color;
    
    color = player.invisible ? MLV_COLOR_GOLD4 : MLV_COLOR_GOLD1;
    drawEntity(player.location, color);
}

/**
 * @brief Draws the relic
 * 
 * @param player the relic
 */
void drawRelic(Relic relic){
    if (!relic.taken)
        drawEntity(relic.location, MLV_COLOR_MAGENTA1);
}

/**
 * @brief Draw the relics
 * 
 * @param golems the array of relics
 * @param arraySize the size of the relics array
 */
void drawRelics(Relic *relics, int arraySize){
    int i;

    assert(arraySize >= 0);
    assert(relics);

    /*
        Two separate loop because we don't want the detection radius of a golem to overwrite a part of another golem
    */

    for (i = 0; i < arraySize; i++){
        drawRelic(relics[i]);
    }
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
        MLV_draw_line(i * 20, y * 20, i * 20, (y + height) * 20, color);
    }
    for (i = y; i <= y + height; i++) {
        MLV_draw_line(x * 20, i * 20, x * 20 + width * 20, i * 20, color);
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
                MLV_draw_filled_rectangle(j * 20, i * 20, 20, 20, MLV_COLOR_BLACK);
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
    int i, j;
    assert(0 <= x);
    assert(x < MAX_WIDTH);
    assert(0 <= y);
    assert(y < MAX_HEIGHT);
    assert(x + width <= MAX_WIDTH);
    assert(y + height <= MAX_HEIGHT);

    for (i = y; i < y + height; i++) {
        for (j = x; j < x + width; j++) {
            if (grid.square[i][j].hasMana) {
                MLV_draw_filled_rectangle(j * 20, i * 20, 20, 20, MLV_COLOR_WHITE);
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
    MLV_draw_filled_rectangle(x * 20, y * 20, width * 20, height * 20, MLV_COLOR_GRAY60);
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
void drawTerrain(Grid grid){
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
    assert(0 <= x);
    assert(x < MAX_WIDTH);
    assert(0 <= y);
    assert(y < MAX_HEIGHT);
    assert(x + width <= MAX_WIDTH);
    assert(y + height <= MAX_HEIGHT);

    wipeSubspace(x, y, width, height);
    drawManaSubspace(grid, x, y, width, height);
    drawWallsSubspace(grid, x, y, width, height);
    drawGridSubspace(x, y, width, height, MLV_COLOR_BLACK);
}

/**
 * Redraws the area surrounding an entity on the game field.
 *
 * @param x the x-coordinate of the center of the surrounding area
 * @param y the y-coordinate of the center of the surrounding area
 * @param grid the grid containing information about the walls and mana
 */
void redrawSubspaceEntity(int x, int y, int width, int height, Grid grid) {
    assert(0 <= x);
    assert(x < MAX_WIDTH);
    assert(0 <= y);
    assert(y < MAX_HEIGHT);

    x = clamp(x - width / 2, 0, MAX_WIDTH - width);
    y = clamp(y - height / 2, 0, MAX_HEIGHT - height);
    width = clamp(width, 0, MAX_WIDTH - x);
    height = clamp(height, 0, MAX_HEIGHT - y);
    redrawSubspace(grid, x, y, width, height);
}

/**
 * Redraws the area surrounding a player on the game field.
 *
 * @param player the player whose surrounding area should be redrawn
 * @param grid the grid containing information about the walls and mana
 */
void redrawSubspacePlayer(Player player, Grid grid) {
    int width, height, x, y;

    width = height = 10;

    x = roundToInt(player.location.x);
    y = roundToInt(player.location.y);
    redrawSubspaceEntity(x, y, width, height, grid);
}

/**
 * Redraws the area surrounding a golem on the game field.
 *
 * @param golem the golem whose surrounding area should be redrawn
 * @param grid the grid containing information about the walls and mana
 */
void redrawSubspaceGolem(Golem golem, Grid grid) {
    int width, height, x, y;

    width = golem.panic ? 14 : 13;
    height = width;
    
    x = roundToInt(golem.location.x);
    y = roundToInt(golem.location.y);
    redrawSubspaceEntity(x, y, width, height, grid);
}

/**
 * Redraws the area surrounding a relic on the game field.
 *
 * @param player the relic whose surrounding area should be redrawn
 * @param grid the grid containing information about the walls and mana
 */
void redrawSubspaceRelic(Relic relic, Grid grid) {
    int width, height, x, y;

    width = height = 3;

    x = roundToInt(relic.location.x);
    y = roundToInt(relic.location.y);
    redrawSubspaceEntity(x, y, width, height, grid);
}

/**
 * @brief Draw the given entities
 * 
 * @param grid The grid
 * @param player The player
 * @param golems The array of golems
 * @param relics The array of relics
 * @param lenGolem The length of the said array
 * @param lenRelics The length of the said array
 */
void drawEntities(Grid grid, Player player, Golem * golems, Relic * relics, int lenGolem, int lenRelics){
    int i;

    redrawSubspacePlayer(player, grid);

    for (i = 0; i < lenGolem; i++){
        redrawSubspaceGolem(golems[i], grid);
    }
    for (i = 0; i < lenRelics; i++){
        redrawSubspaceRelic(relics[i], grid);
    }

    for (i = 0; i < lenGolem; i++){
        drawDetectionRadius(golems[i]);
    }

    drawRelics(relics, lenRelics);
    drawGolems(golems, lenGolem);
    drawPlayer(player);
}

/**
 * @brief Get the string equivalent (in format HH : mm : ss : cc) of the time given in ms
 * 
 * @param timeString The resulting string (to be edited)
 * @param timeElapsed The time value in ms
 */
static void getTimeString(char timeString[12], int timeElapsed){
    assert(timeString);
    sprintf(timeString, "%02d:%02d:%02d:%02d",  microsecondsToHours(timeElapsed),
                                                microsecondsToMinutes(timeElapsed),
                                                microsecondsToSeconds(timeElapsed),
                                                microsecondsToCentiseconds(timeElapsed)
           );
}

/**
 * @brief Draw information about the current game such as the time elapsed, the abilities currently used, remaining relics etc.
 * 
 * @param timeElapsed Time elapsed in ms
 * @param mana Mana currently being held by the player
 * @param remaining Remaining relics to be stolen
 * @param invisible 1 if the invisiblity ability is active, or 0.
 * @param boost 1 if the thursing / boosting ability is active, or 0.
 * @param alert 1 one or more golem is(are) panicking, or 0.
 */
void drawInfo(int timeElapsed, int mana, int remaining, int invisible, int boost, int alert){
    char manaString[9];
    char timeString[12];
    char strCollect[3];
    MLV_Font * font;

    assert(timeElapsed >= 0);

    getTimeString(timeString, timeElapsed);
    sprintf(manaString, "%d", mana);
    sprintf(strCollect, "%d", remaining);

    MLV_draw_filled_rectangle(0, 900, 1200, 1000, MLV_COLOR_WHITE);

    font = MLV_load_font("./ressource/MGS2MENU.ttf", 20);

    MLV_draw_text_with_font(10, 920, "TIME :", font, MLV_COLOR_BLACK);
    MLV_draw_text_with_font(170, 920, timeString, font, MLV_COLOR_BLACK);
    MLV_draw_text_with_font(10, 960, "MANA :", font, MLV_COLOR_BLACK);
    MLV_draw_text_with_font(170, 960, manaString, font, MLV_COLOR_BLACK);

    MLV_draw_text_with_font(530, 920, "INVISIBLE", font, invisible ? MLV_COLOR_BLACK : MLV_COLOR_GRAY75);
    MLV_draw_text_with_font(530, 960, "LEFT :", font, MLV_COLOR_BLACK);
    MLV_draw_text_with_font(690, 960, strCollect, font, MLV_COLOR_BLACK);

    MLV_draw_text_with_font(930, 920, "BOOST", font, boost ? MLV_COLOR_BLACK : MLV_COLOR_GRAY75);
    MLV_draw_text_with_font(930, 960, "ALERT", font, alert ? MLV_COLOR_RED : MLV_COLOR_GRAY75);

    MLV_free_font(font);
    
    MLV_actualise_window();
}

/**
 * @brief Draws a game over animation
 * 
 */
void drawGameOver(){
    MLV_Font * font;
    int positionX, positionY;
    int width_text, height_text; 
    const char * gameOver = "GAME OVER";
    int width;
    width = GAME_WINX;
    font = MLV_load_font("./ressource/MGS1.ttf", 100);
    MLV_draw_filled_rectangle(0, 0, 60 * 20, 45 * 20, MLV_COLOR_GREY4);
    MLV_get_size_of_text_with_font(gameOver, &width_text, &height_text, font);
	positionX = (width-width_text)/2, positionY = GAME_WINY / 2;
    MLV_draw_text_with_font(positionX, positionY, "G", font, MLV_COLOR_AQUAMARINE1);
    MLV_actualise_window();
    MLV_wait_milliseconds(300);
    MLV_draw_text_with_font(positionX, positionY, "GA", font, MLV_COLOR_AQUAMARINE1);
    MLV_actualise_window();
    MLV_wait_milliseconds(300);
    MLV_draw_text_with_font(positionX, positionY, "GAM", font, MLV_COLOR_AQUAMARINE1);
    MLV_actualise_window();
    MLV_wait_milliseconds(300);
    MLV_draw_text_with_font(positionX, positionY, "GAME", font, MLV_COLOR_AQUAMARINE1);
    MLV_actualise_window();
    MLV_wait_milliseconds(300);
    MLV_draw_text_with_font(positionX, positionY, "GAME O", font, MLV_COLOR_AQUAMARINE1);
    MLV_actualise_window();
    MLV_wait_milliseconds(300);
    MLV_draw_text_with_font(positionX, positionY, "GAME OV", font, MLV_COLOR_AQUAMARINE1);
    MLV_actualise_window();
    MLV_wait_milliseconds(300);
    MLV_draw_text_with_font(positionX, positionY, "GAME OVE", font, MLV_COLOR_AQUAMARINE1);
    MLV_actualise_window();
    MLV_wait_milliseconds(300);
    MLV_draw_text_with_font(positionX, positionY, "GAME OVER", font, MLV_COLOR_AQUAMARINE1);
    MLV_actualise_window();
    MLV_wait_milliseconds(1500);
    MLV_free_font(font);
}

/**
 * @brief Draw a winning message animation
 * 
 * @param timeElapse time elapsed from the start of the game (in ms)
 * @param manaTotal total mana used by the player
 * 
 */
void drawWin(int timeElapsed, int manaTotal){
    MLV_Font * font, * font2;
    int positionX, positionY;
    int width_text, height_text; 
    char timeString[12];
    char manaString[9];
    const char * success = "SUCCESS";
    int width;
    width = GAME_WINX;
    font = MLV_load_font("./ressource/MGS1.ttf", 100);
    font2 = MLV_load_font("./ressource/MGS2MENU.ttf", 20);
    MLV_draw_filled_rectangle(0, 0, 60 * 20, 45 * 20, MLV_COLOR_GREY4);

    getTimeString(timeString, timeElapsed);
    sprintf(manaString, "%d", manaTotal);
    MLV_draw_text_with_font(40, 220, "TIME :", font2, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(210, 220, timeString, font2, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(580, 220, "MANA USED :", font2, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(880, 220, manaString, font2, MLV_COLOR_WHITE);

    MLV_get_size_of_text_with_font(success, &width_text, &height_text, font);
    positionX = (width-width_text)/2, positionY = GAME_WINY / 2;
    MLV_draw_text_with_font(positionX, positionY, "S", font, MLV_COLOR_AQUAMARINE1);
    MLV_actualise_window();
    MLV_wait_milliseconds(300);
    MLV_draw_text_with_font(positionX, positionY, "SU", font, MLV_COLOR_AQUAMARINE1);
    MLV_actualise_window();
    MLV_wait_milliseconds(300);
    MLV_draw_text_with_font(positionX, positionY, "SUC", font, MLV_COLOR_AQUAMARINE1);
    MLV_actualise_window();
    MLV_wait_milliseconds(300);
    MLV_draw_text_with_font(positionX, positionY, "SUCC", font, MLV_COLOR_AQUAMARINE1);
    MLV_actualise_window();
    MLV_wait_milliseconds(300);
    MLV_draw_text_with_font(positionX, positionY, "SUCCE", font, MLV_COLOR_AQUAMARINE1);
    MLV_actualise_window();
    MLV_wait_milliseconds(300);
    MLV_draw_text_with_font(positionX, positionY, "SUCCES", font, MLV_COLOR_AQUAMARINE1);
    MLV_actualise_window();
    MLV_wait_milliseconds(300);
    MLV_draw_text_with_font(positionX, positionY, "SUCCESS", font, MLV_COLOR_AQUAMARINE1);
    MLV_actualise_window();
    MLV_wait_milliseconds(300);
    MLV_draw_text_with_font(250, 850, "Press any key to continue", font2, MLV_COLOR_WHITE);
    MLV_actualise_window();
    MLV_wait_keyboard_or_mouse(NULL, NULL, NULL, NULL, NULL);


}

/**
 * @brief Asks if the user wants to save his score
 * 
 * @return int 1 if yes 0 otherwise
 */
int askSaveScore(){
	int x = 0, y = 0;
    int positionX;
    int width_text, height_text; 
    int width, choice;
    const char * msg = "Save to leaderboard ?";
    MLV_Font * font;

    width = GAME_WINX;
    font = MLV_load_font("./ressource/MGS2MENU.ttf", 20);
    MLV_draw_filled_rectangle(0, 0, 1200, 1000, MLV_COLOR_BLACK);

    MLV_get_size_of_text_with_font(msg, &width_text, &height_text, font);
    positionX = (width-width_text)/2;
    MLV_draw_text_with_font(positionX, 300, msg, font, MLV_COLOR_WHITE);

    MLV_free_font(font);
    font = MLV_load_font("./ressource/MGS2MENU.ttf", 20);

    MLV_draw_filled_rectangle(450, 450, 100, 100, MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle(650, 450, 100, 100, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(470, 470, "Y", font, MLV_COLOR_BLACK);
    MLV_draw_text_with_font(670, 470, "N", font, MLV_COLOR_BLACK);

    MLV_actualise_window();

	while(1){
        MLV_wait_mouse(&x, &y);
        if (450 <= y && y <= 550){
            if (450 <= x && x <= 550){
                choice = 1;
                break;
            }
                choice = 1;
            if (650 <= x && x <= 750){
                choice = 0;
                break;
            }
        }
    }

    MLV_free_font(font);

    return choice;
}

/**
 * @brief Asks the user to input his name (3 letters max are counted)
 * 
 * @param name the name that will be stored
 */
void askName(char name[11]){
    MLV_Font * font;
    int i;
    char *text;

    MLV_draw_filled_rectangle(0, 0, 1200, 1000, MLV_COLOR_BLACK);
    font = MLV_load_font("./ressource/MGS2MENU.ttf", 17);

    MLV_wait_input_box_with_font(
		450, 450,
		400, 100, 
		MLV_COLOR_GREY60, MLV_COLOR_BLACK,
		MLV_COLOR_WHITE, "Name : ",
        &text,
        font
    );
    
    for (i = 0; text[i] != '\0' && i < 9; i++){
        if (i == 10){
            name[i] = '\0';
            break;
        }
        name[i] = text[i];
    }
}

/**
 * @brief From two leaderboard (time centered and mana centered)
 * 
 * Draws the corresponding two leaderboard
 * 
 * @param time Time Leaderboard
 * @param mana Mana Leaderboard
 */
void drawLeaderboard(Leaderboard time, Leaderboard mana){
    char timeString[12];
    char manaString[9];
    int i;
    MLV_Font * font;

    MLV_draw_filled_rectangle(0, 0, 1200, 1000, MLV_COLOR_BLACK);
    font = MLV_load_font("./ressource/DS-DIGI.ttf", 20);
    
    /* Time leader board */
    MLV_draw_text_with_font(10, 10, "Time Leaderboard Top 10 :", font, MLV_COLOR_WHITE);
    for (i = 0; i < time.size; i++){
        sprintf(manaString, "%d", time.scores[i].manaUsed);
        getTimeString(timeString, time.scores[i].timeElapsed);
        MLV_draw_text_with_font(10, 50 + i * 30, "Name : ", font, MLV_COLOR_WHITE);
        MLV_draw_text_with_font(60, 50 + i * 30, time.scores[i].name, font, MLV_COLOR_WHITE);
        MLV_draw_text_with_font(200, 50 + i * 30, timeString, font, MLV_COLOR_WHITE);
        MLV_draw_text_with_font(400, 50 + i * 30, manaString, font, MLV_COLOR_WHITE);
        
    }
    MLV_draw_text_with_font(610, 10, "Mana Usage Leaderboard Top 10 :", font, MLV_COLOR_WHITE);
    for (i = 0; i < mana.size; i++){
        sprintf(manaString, "%d", mana.scores[i].manaUsed);
        getTimeString(timeString, mana.scores[i].timeElapsed);
        MLV_draw_text_with_font(610, 50 + i * 30, "Name : ", font, MLV_COLOR_WHITE);
        MLV_draw_text_with_font(660, 50 + i * 30, mana.scores[i].name, font, MLV_COLOR_WHITE);
        MLV_draw_text_with_font(800, 50 + i * 30, timeString, font, MLV_COLOR_WHITE);
        MLV_draw_text_with_font(1000, 50 + i * 30, manaString, font, MLV_COLOR_WHITE);
    }
    MLV_actualise_window();
    MLV_wait_keyboard_or_mouse(NULL, NULL, NULL, NULL, NULL);
}
