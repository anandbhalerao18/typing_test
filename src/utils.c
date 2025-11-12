#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../include/utils.h"

void shuffle_words(char words[][MAX_WORD_LEN], int count) {
    if (count <= 1) return;

    static int seeded = 0;
    if (!seeded) {
        srand((unsigned)time(NULL));
        seeded = 1;
    }

    for (int i = count - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        if (i != j) {
            char tmp[MAX_WORD_LEN];
            strncpy(tmp, words[i], MAX_WORD_LEN);
            tmp[MAX_WORD_LEN - 1] = '\0';
            strncpy(words[i], words[j], MAX_WORD_LEN);
            words[i][MAX_WORD_LEN - 1] = '\0';
            strncpy(words[j], tmp, MAX_WORD_LEN);
            words[j][MAX_WORD_LEN - 1] = '\0';
        }
    }
}

int is_word_correct(const char *typed, const char *actual) {
    if (!typed || !actual) return 0;
    return (strcmp(typed, actual) == 0) ? 1 : 0;
}
