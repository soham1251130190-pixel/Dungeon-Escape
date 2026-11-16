#include <stdio.h>
#include <string.h>
#include "sorting.h"

// Helper to swap two leaderboard entries
static void swapEntries(LeaderboardEntry *a, LeaderboardEntry *b) {
    LeaderboardEntry temp = *a;
    *a = *b;
    *b = temp;
}

// Bubble Sort: Repeatedly steps through the list, compares adjacent elements, and swaps them if in wrong order.
// Sorts in descending order of scores (Highest -> Lowest).
void bubbleSort(LeaderboardEntry array[], int size) {
    if (array == NULL || size <= 1) return;

    for (int i = 0; i < size - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j].score < array[j + 1].score) {
                swapEntries(&array[j], &array[j + 1]);
                swapped = 1;
            }
        }
        if (!swapped) break; // Optimized Bubble Sort early exit
    }
}

// Selection Sort: Finds the maximum element in the unsorted portion and places it at the beginning.
void selectionSort(LeaderboardEntry array[], int size) {
    if (array == NULL || size <= 1) return;

    for (int i = 0; i < size - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < size; j++) {
            if (array[j].score > array[maxIdx].score) {
                maxIdx = j;
            }
        }
        if (maxIdx != i) {
            swapEntries(&array[i], &array[maxIdx]);
        }
    }
}

// Insertion Sort: Builds the sorted array one item at a time.
void insertionSort(LeaderboardEntry array[], int size) {
    if (array == NULL || size <= 1) return;

    for (int i = 1; i < size; i++) {
        LeaderboardEntry key = array[i];
        int j = i - 1;

        while (j >= 0 && array[j].score < key.score) {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }
}
