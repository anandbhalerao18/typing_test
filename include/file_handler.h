#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H
#include <stdio.h>

#define MAX_WORDS 10000
#define MAX_WORD_LEN 128 // allows for the very long word you can add 32 or 64 according to your memory needs.

int load_words(const char *filename, char words[][MAX_WORD_LEN]);

#endif