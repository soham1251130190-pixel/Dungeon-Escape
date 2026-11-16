#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "sorting.h"

#define MAX_LEADERBOARD_ENTRIES 50
#define LEADERBOARD_FILE "data/leaderboard.txt"

// Leaderboard array structure
// Leaderboard maintains top player scores sorted in descending order using manual sorting.
typedef struct {
    LeaderboardEntry entries[MAX_LEADERBOARD_ENTRIES];
    int count;
} Leaderboard;

// Function prototypes
void initializeLeaderboard(Leaderboard *lb);
int loadLeaderboard(Leaderboard *lb, const char *filename);
int saveLeaderboard(const Leaderboard *lb, const char *filename);
void addLeaderboardScore(Leaderboard *lb, const char *name, int score);
void displayLeaderboard(const Leaderboard *lb);
void freeLeaderboard(Leaderboard *lb);

#endif // LEADERBOARD_H
