#ifndef SORTING_H
#define SORTING_H

#define MAX_PLAYER_NAME_LEN 50

// Leaderboard entry structure used in sorting algorithms
typedef struct {
    char name[MAX_PLAYER_NAME_LEN];
    int score;
} LeaderboardEntry;

// Manual sorting algorithm prototypes for Leaderboard (Descending Order)
// Sorting arranges player scores from highest to lowest.
void bubbleSort(LeaderboardEntry array[], int size);
void selectionSort(LeaderboardEntry array[], int size);
void insertionSort(LeaderboardEntry array[], int size);

#endif // SORTING_H
