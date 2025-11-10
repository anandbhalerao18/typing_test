#ifndef UTILS_H
#define UTILS_H
#include <stdlib.h>
#include <string.h>
#include <time.h>

void shuffle_words(char words[][32], int count);
int is_word_correct(const char *typed, const char *actual);

#endif
