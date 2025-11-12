#ifndef UTILS_H
#define UTILS_H

#include "file_handler.h" /* for MAX_WORD_LEN */

#include <stdlib.h>

/* Shuffle the array of words randomly */
void shuffle_words(char words[][MAX_WORD_LEN], int count);

/* Compare user input with correct word. Returns 1 if equal, 0 otherwise */
int is_word_correct(const char *typed, const char *actual);

#endif
