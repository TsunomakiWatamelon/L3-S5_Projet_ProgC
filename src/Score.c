/**
 * @file Score.c
 * @author HERVE NGUYEN & GABRIEL RADONIAINA
 * @brief Score module, deals with saving/loading leaderboard files and manipulating leaderboards
 * @version 0.1
 * @date 2023-01-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include "../include/Score.h"

/**
 * @brief Write the content of a leaderboard into a binary file at the specified file path
 * 
 * @param filepath the filepath
 * @param leaderboard the pointer to the leaderboard
 */
void writeLeaderboardToBinaryFile(char* filepath, Leaderboard * leaderboard) {
    int i;
    FILE* file;

    file = fopen(filepath, "wb");

    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < leaderboard->size; i++)
        fwrite(&(leaderboard->scores[i]), sizeof(Score), 1, file);
    fclose(file);
}

/**
 * @brief Reads the content of a leaderboard from a binary file at the specifed file path
 * 
 * Saves the data at the address given in the arguments for the leaderboard
 * 
 * @param filepath the filepath
 * @param leaderboard the pointer to the leaderboard
 * @return int 0 if it couldn't read the file, 1 if it read successfully
 */
int readLeaderboardFromBinaryFile(char * filepath, Leaderboard * leaderboard) {
    FILE* file;
    Score score;
    file = fopen(filepath, "rb");

    if (file == NULL) {
        return 0;
    }
    
    while (fread(&score, sizeof(Score), 1, file) == 1) {
        memcpy(&(leaderboard->scores[leaderboard->size]), &score, sizeof(Score));
        leaderboard->size = leaderboard->size + 1;
        if (leaderboard->size == ARRAY_MAX)
            break;
    }
    fclose(file);
    return 1;
}

/**
 * @brief From two pointer to Score, compare their "manaUsed" field
 * 
 * @param a first pointer
 * @param b second pointer
 * @return int result of the comparison
 */
static int compareManaUsed(const void* a, const void* b) {
    Score* scoreA = (Score*)a;
    Score* scoreB = (Score*)b;
    return scoreA->manaUsed - scoreB->manaUsed;
}

/**
 * @brief From two pointer to Score, compare their "timeElapsed" field
 * 
 * @param a first pointer
 * @param b second pointer
 * @return int result of the comparison
 */
static int compareTime(const void* a, const void* b) {
    Score* scoreA = (Score*)a;
    Score* scoreB = (Score*)b;
    return scoreA->timeElapsed - scoreB->timeElapsed;
}

/**
 * @brief Add the value of a score into the leaderboard if they are good enough according to the comparison
 * 
 * @param leaderboard pointer to the leaderboard
 * @param name name
 * @param manaUsed manaUsed
 * @param timeElapsed timeElapsed
 * @param comparison pointer to the comparison function
 */
static void addScore(Leaderboard* leaderboard, char name[11], int manaUsed, int timeElapsed, int (*comparison)(const void *, const void *)) {
    Score newScore;
    
    memcpy(newScore.name, name, sizeof(char) * 11);
    newScore.manaUsed = manaUsed;
    newScore.timeElapsed = timeElapsed;

    if (leaderboard->size == ARRAY_MAX) {
        qsort(leaderboard->scores, leaderboard->size, sizeof(Score), comparison);
        if (comparison(&newScore, &(leaderboard->scores[ARRAY_MAX - 1])) < 0)
            memcpy(&(leaderboard->scores[ARRAY_MAX - 1]), &newScore, sizeof(Score));
    }
    else {
        memcpy(&(leaderboard->scores[leaderboard->size]), &newScore, sizeof(Score));
        leaderboard->size++;
    }
    qsort(leaderboard->scores, leaderboard->size, sizeof(Score), comparison);
}

/**
 * @brief Add the value of a score into the leaderboard if they are good enough (timeElapsed centered)
 * 
 * @param leaderboard pointer to the leaderboard
 * @param name name
 * @param manaUsed manaUsed
 * @param timeElapsed timeElapsed
 */
void addScoreTime(Leaderboard* leaderboard, char name[11], int manaUsed, int timeElapsed){
    addScore(leaderboard, name, manaUsed, timeElapsed, compareTime);
}

/**
 * @brief Add the value of a score into the leaderboard if they are good enough (manaUsed centered)
 * 
 * @param leaderboard pointer to the leaderboard
 * @param name name
 * @param manaUsed manaUsed
 * @param timeElapsed timeElapsed
 */
void addScoreMana(Leaderboard* leaderboard, char name[11], int manaUsed, int timeElapsed){
    addScore(leaderboard, name, manaUsed, timeElapsed, compareManaUsed);
}
