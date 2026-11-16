#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leaderboard.h"
#include "sorting.h"

// Initialize the leaderboard array
void initializeLeaderboard(Leaderboard *lb) {
    if (lb == NULL) return;
    lb->count = 0;
}

// Load scores from text file into leaderboard array
int loadLeaderboard(Leaderboard *lb, const char *filename) {
    if (lb == NULL) return 0;
    lb->count = 0;

    const char *path = (filename != NULL) ? filename : LEADERBOARD_FILE;
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        // Populate default records for academic demo if file is not yet created
        addLeaderboardScore(lb, "Rahul", 900);
        addLeaderboardScore(lb, "Om", 700);
        addLeaderboardScore(lb, "Soham", 500);
        addLeaderboardScore(lb, "Aryan", 300);
        saveLeaderboard(lb, path);
        return 1;
    }

    char line[128];
    while (fgets(line, sizeof(line), file) != NULL && lb->count < MAX_LEADERBOARD_ENTRIES) {
        char name[MAX_PLAYER_NAME_LEN];
        int score = 0;

        // Parse line format: "Name Score" or "Name,Score"
        if (sscanf(line, "%49s %d", name, &score) == 2 || sscanf(line, "%49[^,],%d", name, &score) == 2) {
            strncpy(lb->entries[lb->count].name, name, MAX_PLAYER_NAME_LEN - 1);
            lb->entries[lb->count].name[MAX_PLAYER_NAME_LEN - 1] = '\0';
            lb->entries[lb->count].score = score;
            lb->count++;
        }
    }

    fclose(file);

    // Sort active entries using manual Bubble Sort
    bubbleSort(lb->entries, lb->count);
    return 1;
}

// Save scores from leaderboard array to text file
int saveLeaderboard(const Leaderboard *lb, const char *filename) {
    if (lb == NULL) return 0;

    const char *path = (filename != NULL) ? filename : LEADERBOARD_FILE;
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        printf("[!] Warning: Could not open '%s' to save leaderboard scores.\n", path);
        return 0;
    }

    for (int i = 0; i < lb->count; i++) {
        fprintf(file, "%s %d\n", lb->entries[i].name, lb->entries[i].score);
    }

    fclose(file);
    return 1;
}

// Add a player score, maintain size limit, and sort array
void addLeaderboardScore(Leaderboard *lb, const char *name, int score) {
    if (lb == NULL || name == NULL) return;

    if (lb->count < MAX_LEADERBOARD_ENTRIES) {
        strncpy(lb->entries[lb->count].name, name, MAX_PLAYER_NAME_LEN - 1);
        lb->entries[lb->count].name[MAX_PLAYER_NAME_LEN - 1] = '\0';
        lb->entries[lb->count].score = score;
        lb->count++;
    } else {
        // Replace lowest score if new score is higher
        if (score > lb->entries[lb->count - 1].score) {
            strncpy(lb->entries[lb->count - 1].name, name, MAX_PLAYER_NAME_LEN - 1);
            lb->entries[lb->count - 1].name[MAX_PLAYER_NAME_LEN - 1] = '\0';
            lb->entries[lb->count - 1].score = score;
        }
    }

    // Sort leaderboard entries descending by score using manual Bubble Sort
    bubbleSort(lb->entries, lb->count);
}

// Display sorted leaderboard rankings in a formatted table
void displayLeaderboard(const Leaderboard *lb) {
    printf("\n========================================\n");
    printf("        DUNGEON ESCAPE LEADERBOARD\n");
    printf("========================================\n");

    if (lb == NULL || lb->count == 0) {
        printf("  No leaderboard entries available.\n");
        printf("========================================\n\n");
        return;
    }

    printf("  %-5s  %-20s  %-10s\n", "Rank", "Adventurer", "Score");
    printf("  --------------------------------------\n");
    for (int i = 0; i < lb->count; i++) {
        printf("  #%-4d  %-20s  %-10d\n", i + 1, lb->entries[i].name, lb->entries[i].score);
    }
    printf("========================================\n\n");
}

// Clean up leaderboard resources
void freeLeaderboard(Leaderboard *lb) {
    if (lb == NULL) return;
    lb->count = 0;
}
