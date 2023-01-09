/**
 * @file Game.c
 * @author HERVE NGUYEN (herve.nguyen@edu.univ-eiffel.fr)
 * @brief 
 * @version 0.1
 * @date 2023-01-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../include/Game.h"

/**
 * @brief Initializes Main data structures for the game
 * 
 * Golems : 5 (NB_GOLEM) with random starting positions (far enough from the player)
 * Relics : 3 (NB_RELIC) with random starting positions (far enough from the player)
 * 
 * The starting positions of Relics and Golems will not be in positions where there are walls
 * 
 * @param grid Pointer to the grid to initialize
 * @param player Pointer to the player to initialize
 * @param golemArray Array of Golems to be initialized individually
 * @param relicArray Array of Relics to be initialized individually
 */
void initGame(Grid * grid, Player * player, Golem * golemArray, Relic * relicArray){
    int i;
    Point location[NB_GOLEM + NB_RELIC];
    initializeTerrain(grid);

    init_Player(player);

    /* Settings the positions for the golems and relics */
    for (i = 0; i < NB_GOLEM + NB_RELIC; i++){
        do {
            getRandomPoint(&(location[i]), (double)MAX_WIDTH - 3.5, 1.5, (double)MAX_HEIGHT - 3.5, 1.5);
        } while (!positionArrayNotTouching(location, i + 1)
              || isCollision(&(location[i]), *grid)
              /* To be far enough otherwise it's possible the player get caught instantly, or it's too easy to catch the relic */
              || pointDistance(player->location, location[i]) <= DETECT_RADIUS + 20 
          );
    }

    for (i = 0; i < NB_GOLEM; i++){
        initGolem(&golemArray[i], location[i]);
    }
    for (i = NB_GOLEM; i < NB_GOLEM + NB_RELIC; i++){
        initRelic(&relicArray[i - NB_GOLEM], location[i]);
    }
}

/**
 * @brief Shortcut function that allows if a certain MLV_Keyboard_button is currently being pressed
 * 
 * @param key The key we trying to check
 * @return int 
 */
static int mgksCheck(MLV_Keyboard_button key){
    return MLV_get_keyboard_state(key) == MLV_PRESSED;
}

/**
 * @brief Tries to check all keys related to moving the player
 * 
 * Will return 1 if the user is actively presssing a related key
 * If that is the case, then the value pointed by 'pressed' will be set to the corresponding direction.
 * 
 * There are two special cases where multiples keys are simultaneously pressed.
 * 
 * The first case is where all the keys pressed do not correspond to the previous direction in the previous frame :
 *    - The rule of thumb would be to select the direction the most further down in the chain of "if"
 * The second case is where one of the multiple keys currently pressed corresponds to the direction of the previous frame :
 *    - The choice would then be to just keep that direction
 * 
 * If none of the keys below are pressed, then the function will return 0.
 * 
 * @param formerActive equal to 1 if in the previous frame, one of the keys related to that former direction was still pressed.
 * @param former direction the player was moving toward in the previous frame (in condition that formerActive is == 1)
 * @param pressed pointer to the direction chosen by the user for the current frame
 * @return int 1 if the user chose to move, otherwise 0
 */
int getUserMove(int formerActive, Direction former, Direction *pressed){
    int formerStillActive, moving;

    formerStillActive = 0;
    moving = 0;

    /* We can possibly refactor this but it'll maybe be rather unreadable */
    if( mgksCheck(MLV_KEYBOARD_UP) || mgksCheck(MLV_KEYBOARD_z)){
		if (formerActive && former == up)
            formerStillActive = 1;
        *pressed = up;
        moving = 1;
	}
    if( mgksCheck(MLV_KEYBOARD_DOWN) || mgksCheck(MLV_KEYBOARD_s)){
		if (formerActive && former == down)
            formerStillActive = 1;
        *pressed = down;
        moving = 1;
	}
    if( mgksCheck(MLV_KEYBOARD_LEFT) || mgksCheck(MLV_KEYBOARD_q)){
		if (formerActive && former == left)
            formerStillActive = 1;
        *pressed = left;
        moving = 1;
	}
    if( mgksCheck(MLV_KEYBOARD_RIGHT) || mgksCheck(MLV_KEYBOARD_d)){
		if (formerActive && former == right)
            formerStillActive = 1;
        *pressed = right;
        moving = 1;
	}
    
    if (formerStillActive)
        *pressed = former;
    
    return moving;
}

/**
 * @brief Tries to check if the user is attempting to "thrust", in other words "boost" it's speed and acceleration
 * 
 * @return int 1 if that is the case, otherwise 0
 */
int userIsThrusting(){
    return mgksCheck(MLV_KEYBOARD_LSHIFT) || mgksCheck(MLV_KEYBOARD_RSHIFT);
}

/**
 * @brief Tries to check if the user is attempting to use it's "invisiblity" ability
 * 
 * Applies the power if the player has enough mana (the corresponding mana will be subtracted)
 * 
 * @param player Pointer to the player (to edit if necessary)
 * @return int [number of mana used] OR [1 if the player has used invisbility otherwise 0] (depends on the interpretation, the latter is used by us)
 */
int userInvisible(Player * player){
    player->invisible = 0;
    if (mgksCheck(MLV_KEYBOARD_SPACE) && player->mana > 0) {
        player->mana--;
        player->invisible = 1;
        return 1;
    }
    return 0;
}

/**
 * @brief In contrary to the similar named function from the Golem module, this one applies to an array of Golems.
 * 
 * In addition, it will also try to see if the golem has found that one of the relics in the given array of relics has been stolen.
 * 
 * @param grid Pointer to the grid
 * @param golems Array of golems
 * @param player Pointer to the player
 * @param relics Array of relics 
 * @return int 1 if the player has been spotted, otherwise 0
 */
int patrolGolems(Grid * grid, Golem * golems, Player * player, Relic * relics){
    int i, res;

    res = 0;
    for (i = 0; i < NB_GOLEM; i++){
        res = res || patrolGolem(&(golems[i]), player, grid);
        relicChecking(&(golems[i]), relics, grid, NB_RELIC);
    }

    return res;
}

/**
 * @brief Considering that the square from the given coordinate (which we assume are valid),
 * the function store information about that specific square (to dSquare) and remove the mana from it.
 * 
 * The information store will be useful for refill depleted squares later in the game.
 * 
 * @param grid Pointer to the grid
 * @param dSquare Pointer to a "DepletedSquares" which is a data structure using an array of pointer of squares
 * @param x x coordinate of the square whose mana will be stripped
 * @param y y coordinate of the square whose mana will be stripped
 */
void takeManaFromSquare(Grid * grid, DepletedSquares * dSquare, int x, int y){
    assert(grid);
    assert(dSquare);
    assert(y < MAX_HEIGHT && x < MAX_WIDTH);
    assert(0 < y && 0 < x);

    grid->square[y][x].hasMana = 0;
    dSquare->depleted[dSquare->size] = &(grid->square[y][x]);
    dSquare->size++;
}

/**
 * @brief Attempts to restore mana randomly to one square
 * 
 * @param grid Pointer to the grid
 * @param dSquare Pointer to a "DepletedSquares" which is a data structure using an array of pointer of squares
 * @param player player
 * @return int 1 if mana has been successfully been restored on one of the squares, otherwise 0.
 */
int restoreMana(Grid * grid, DepletedSquares * dSquare, Player player){
    int randint;
    assert(grid);
    assert(dSquare);

    if (dSquare->size > 0) {
        if (dSquare->size == 1){
            /* We do not restore the mana of the square just below the player, it'll be too easy */
            if (dSquare->depleted[0]->x == (int)player.location.x && dSquare->depleted[0]->y == (int)player.location.y)
                return 0;
            dSquare->depleted[0]->hasMana = 1;
        }
        else {
            do {
                randint = rand() % dSquare->size;
                /* We do not restore the mana of the square just below the player, it'll be too easy */
            } while(dSquare->depleted[randint]->x == (int)player.location.x && dSquare->depleted[randint]->y == (int)player.location.y);
            dSquare->depleted[randint]->hasMana = 1;
            /* Shifting the array to remove the reference to the square we just restored, and keep a continuous array with no "holes" */
            memmove(&(dSquare->depleted[randint]), &(dSquare->depleted[randint + 1]), sizeof(Square *) * (dSquare->size - randint - 1));
        }
        dSquare->size--;
        return 1;
    }
    return 0;
}

/**
 * @brief Tries to see if the player is currently in contact with a relic.
 * 
 * If that's the case then the relic will be "stolen" by the player
 * 
 * @param player player
 * @param relics array of existing relics
 * @return int 1 one relic has been stolen, otherwise 0.
 */
int stealRelic(Player player, Relic *relics){
    int i, res;

    res = 0;
    for (i = 0; i < NB_RELIC; i++){
        /* Both entities have a diameter of 1.0 */
        if (pointDistance(relics[i].location, player.location) <= 1.0 && !relics[i].taken){
            relics[i].taken = 1;
            res = 1;
            break;
        }
    }
    return res;
}

/**
 * @brief Decerements the value of panic for every golem that is currently in panic mode
 * 
 * It will stop at 0, this function should be called every (0 mod 60)th frame. (every second basically)
 * 
 * @param golems Array of golems
 * @return int 0 if no golems are in panic mode, otherwise 1 
 */
int golemPanicCooldown(Golem * golems){
    int i, stillPanic;
    stillPanic = 0;
    for (i = 0; i < NB_GOLEM; i++){
        if (golems[i].panic > 0){
            golems[i].panic--;
            stillPanic = 1;
        }
    }
    return stillPanic;
}

/**
 * @brief Calculates elapsed time in ms between start and end
 * 
 * @param start start time
 * @param end end time
 * 
 * @return The elapsed time in ms
 */
int elapsed_time_ms(const struct timespec *start, const struct timespec *end) {
    return (end->tv_sec - start->tv_sec) * 1000 + (end->tv_nsec - start->tv_nsec) / 1000000;
}

/**
 * @brief Main game algortithm.
 * 
 */
void game(void){
    /* Varaiable declarations */
    Grid grid; /* The grid */
    Player player; /* The player*/
    Golem golems[NB_GOLEM]; /* The array of golems */
    Relic relics[NB_RELIC]; /* The array of relics */
    Direction direction; /* The direction chosen by the player for a given frame (could be inactive) */
    DepletedSquares dSquare; /* Stores info about non-wall squares whose mana has been taken */
    int directionActive, frameNumber, remainingRelics, alert;
    int manaUsed, totalUsed; /* manaUsed is for a given frame whereas totalUsed is for score calculation */
    int timeElapsed; /* used to get time elapsed in ms for the chronometer */
    struct timespec end_time, new_time, start_time;
    time_t frametime, extratime;

    directionActive = 0; direction = right; frameNumber = 0;
    remainingRelics = NB_RELIC; alert = 0;
    totalUsed = manaUsed = 0;

    srand(time(NULL));
    srand48(time(NULL)); /* For drand48 */

    initGame(&grid, &player, golems, relics);
    createWindow();
    drawTerrain(grid);

    clock_gettime(CLOCK_REALTIME, &start_time);
    while(0){
        frameNumber++;
        clock_gettime(CLOCK_REALTIME, &end_time);

        timeElapsed = elapsed_time_ms(&start_time, &end_time);
        if (timeElapsed > 86399999) /* If it goes BEYOND 23h 59m 59s 99, then we set back the value to the said limit */
            timeElapsed = 86399999;

        manaUsed += userInvisible(&player); /* Checking invisiblity and applying if necessary */

        /* Take mana from the square just below the player if possible */
        if (grid.square[(int)player.location.y][(int)player.location.x].hasMana) {
            takeManaFromSquare(&grid,
                               &dSquare,
                               (int)player.location.x,
                               (int)player.location.y);
            player.mana += 1;
        }
        /* Get the move choice by the user */
        directionActive = getUserMove(directionActive, direction, &direction);
        /* Applying the move */
        if (directionActive){
            /* Accelerating at every frame is too fast so we do it at every 3 frame */
            if (!(frameNumber % 3))
                manaUsed += accel(&player, userIsThrusting());
            move(&player, direction, &grid);
        }
        else
            resetSpeed(&player); /* Reseting the speed if the user chose to not move */

        totalUsed += manaUsed;

        /* Check if the player has stolen a relic */
        if (stealRelic(player, relics))
            remainingRelics--;
        /* If all relics are stolen then proceed to the win page */
        if (remainingRelics == 0){
            drawWin("skt", timeElapsed, totalUsed);
            break;
        }
        /* If the player is spotted, show the gameover animation then quit the loop to quit the game */
        if (patrolGolems(&grid, golems, &player, relics)){
            drawGameOver();
            return;
        }

        /* Every 4 seconds restore the mana from one square, if the player has used some of the mana he took */
        if (!(frameNumber % 240)){
            /* This should also activate when the player is not doing anything
               if he has previously used a set amount of mana and that amount of mana is still not fully returned */
            if (manaUsed > 0){ 
                if (restoreMana(&grid, &dSquare, player))
                    manaUsed--;
            }
            /* Redraw the terrain */
            drawTerrain(grid);
        }
        /* Every second we decrement the panic value of all panicking golems */
        if (!(frameNumber % 60)){
            /* alert is used for the drawInfo function where we can have an alert message if a golem is panicking */
            alert = golemPanicCooldown(golems);
        }
        drawEntities(grid, player, golems, relics, NB_GOLEM, NB_RELIC);
        drawInfo(timeElapsed, player.mana, remainingRelics, player.invisible, userIsThrusting(), alert);
        clock_gettime(CLOCK_REALTIME, &new_time);
        frametime = new_time . tv_sec - end_time .tv_sec;
        frametime += (new_time. tv_sec - end_time.tv_sec) / 1.0E9;
        extratime = 1.0 / 60 - frametime;
        if (extratime > 0){
            MLV_wait_milliseconds((int)(extratime * 1000));
        }
        MLV_actualise_window();
    }
}