/**
 * @file Score.h
 * @author HERVE NGUYEN & GABRIEL RADONIAINA
 * @brief Header file for the Terrain module
 * @version 0.1
 * @date 2023-01-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __score__
#define __score__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_MAX 10

/**
 * @brief Data structure used to store information about a score and pass them to other functions
 * 
 */
typedef struct {
    char name[11];
    int manaUsed;
    int timeElapsed;
} Score;

/**
 * @brief Represents a leaderboard, holds up to 10 scores
 * 
 */
typedef struct {
    Score scores[ARRAY_MAX];
    int size;
} Leaderboard;

/**
 * @brief Write the content of a leaderboard into a binary file at the specified file path
 * 
 * @param filepath the filepath
 * @param leaderboard the pointer to the leaderboard
 */
void writeLeaderboardToBinaryFile(char* filepath, Leaderboard * leaderboard);

/**
 * @brief Reads the content of a leaderboard from a binary file at the specifed file path
 * 
 * Saves the data at the address given in the arguments for the leaderboard
 * 
 * @param filepath the filepath
 * @param leaderboard the pointer to the leaderboard
 * @return int 0 if it couldn't read the file, 1 if it read successfully
 */
int readLeaderboardFromBinaryFile(char * filepath, Leaderboard * leaderboard);

/**
 * @brief Add the value of a score into the leaderboard if they are good enough (timeElapsed centered)
 * 
 * @param leaderboard pointer to the leaderboard
 * @param name name
 * @param manaUsed manaUsed
 * @param timeElapsed timeElapsed
 */
void addScoreTime(Leaderboard* leaderboard, char name[11], int manaUsed, int timeElapsed);

/**
 * @brief Add the value of a score into the leaderboard if they are good enough (manaUsed centered)
 * 
 * @param leaderboard pointer to the leaderboard
 * @param name name
 * @param manaUsed manaUsed
 * @param timeElapsed timeElapsed
 */
void addScoreMana(Leaderboard* leaderboard, char name[11], int manaUsed, int timeElapsed);


#endif
