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
              || pointDistance(player->location, location[i]) <= DETECT_RADIUS + 20 /* To be far enough otherwise it's possible the player get caught instantly */
          );
    }

    for (i = 0; i < NB_GOLEM; i++){
        initGolem(&golemArray[i], location[i]);
    }
    for (i = NB_GOLEM; i < NB_GOLEM + NB_RELIC; i++){
        initRelic(&relicArray[i - NB_GOLEM], location[i]);
    }
}

static int mgksCheck(MLV_Keyboard_button key){
    return MLV_get_keyboard_state(key) == MLV_PRESSED;
}

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

int userIsThrusting(){
    return mgksCheck(MLV_KEYBOARD_LSHIFT) || mgksCheck(MLV_KEYBOARD_RSHIFT);
}

int userInvisible(Player * player){
    player->invisible = 0;
    if (mgksCheck(MLV_KEYBOARD_SPACE) && player->mana > 0) {
        player->mana--;
        player->invisible = 1;
        return 1;
    }
    return 0;
}

int patrolGolems(Grid * grid, Golem * golems, Player * player, Relic * relics){
    int i, res;

    res = 0;
    for (i = 0; i < NB_GOLEM; i++){
        res = res || patrolGolem(&(golems[i]), player, grid);
        relicChecking(&(golems[i]), relics, grid, NB_RELIC);
    }



    return res;
}

void takeManaFromSquare(Grid * grid, DepletedSquares * dSquare, int x, int y){
    assert(grid);
    assert(dSquare);
    assert(y < MAX_HEIGHT && x < MAX_WIDTH);
    assert(0 < y && 0 < x);

    grid->square[y][x].hasMana = 0;
    dSquare->depleted[dSquare->size] = &(grid->square[y][x]);
    dSquare->size++;
}

int restoreMana(Grid * grid, DepletedSquares * dSquare, Player player){
    int randint;
    assert(grid);
    assert(dSquare);

    if (dSquare->size > 0) {
        if (dSquare->size == 1){
            if (dSquare->depleted[0]->x == (int)player.location.x && dSquare->depleted[0]->y == (int)player.location.y)
                return 0;
            dSquare->depleted[0]->hasMana = 1;
        }
        else {
            do {
                randint = rand() % dSquare->size;
            } while(dSquare->depleted[randint]->x == (int)player.location.x && dSquare->depleted[randint]->y == (int)player.location.y);
            dSquare->depleted[randint]->hasMana = 1;
            memmove(&(dSquare->depleted[randint]), &(dSquare->depleted[randint + 1]), sizeof(Square *) * (dSquare->size - randint - 1));
        }
        dSquare->size--;
        return 1;
    }
    return 0;
}

int stealRelic(Player player, Relic *relics){
    int i, res;

    res = 0;
    for (i = 0; i < NB_RELIC; i++){
        if (pointDistance(relics[i].location, player.location) <= 1.0 && !relics[i].taken){
            relics[i].taken = 1;
            res = 1;
        }
    }
    return res;
}

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

void game(void){
    Grid grid;
    Player player;
    Golem golems[NB_GOLEM];
    Relic relics[NB_RELIC];
    Direction direction;
    DepletedSquares dSquare;
    int quit, directionActive, frameNumber, remainingRelics, alert;
    int manaUsed;
    int timeElapsed;
    struct timespec end_time, new_time, start_time;
    time_t frametime, extratime;

    quit = 0; directionActive = 0; direction = right; frameNumber = 0;
    remainingRelics = NB_RELIC; alert = 0;
    srand(time(NULL));
    srand48(time(NULL));
    initGame(&grid, &player, golems, relics);
    createWindow();
    drawTerrain(grid);
    clock_gettime(CLOCK_REALTIME, &start_time);
    manaUsed = 0;
    while(!quit){
        frameNumber++;
        clock_gettime(CLOCK_REALTIME, &end_time);

        timeElapsed = elapsed_time_ms(&start_time, &end_time);
        if (timeElapsed > 86399999)
            timeElapsed = 86399999;

        manaUsed += userInvisible(&player);
        if (grid.square[(int)player.location.y][(int)player.location.x].hasMana){
            takeManaFromSquare(&grid, &dSquare, (int)player.location.x, (int)player.location.y);
            player.mana += 1;
        }
        directionActive = getUserMove(directionActive, direction, &direction);
        if (directionActive){
            /* Accelerating at each frame is too fast */
            if (!(frameNumber % 3))
                manaUsed += accel(&player, userIsThrusting());
            move(&player, direction, &grid);
        }
        else
            resetSpeed(&player);

        if (stealRelic(player, relics))
            remainingRelics--;
        if (patrolGolems(&grid, golems, &player, relics)){
            drawGameOver();
            break;
        }

        if (!(frameNumber % 240)){
            if (manaUsed > 0){
                if (restoreMana(&grid, &dSquare, player))
                    manaUsed--;
            }
            drawTerrain(grid);
        }
        if (!(frameNumber % 60)){
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