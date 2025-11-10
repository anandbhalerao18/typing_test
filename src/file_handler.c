#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/file_handler.h"

int load_words(const char *filename, char words[][MAX_WORD_LEN]) {
    FILE *file = fopen(filename, "r");
    // err handling
    if(file == NULL){
        printf("error");
        return -1;
    }
    // read each word of the file till limit reached
    int count = 0;
    while(fscanf(file, "%31s", words[count]) == 1){
        count++;
        if (count >= MAX_WORDS){
            break;
        }
    }
    fclose(file);
    return count; // return total words loaded
}