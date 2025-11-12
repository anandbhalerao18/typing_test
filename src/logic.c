#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/logic.h"
#include "../include/utils.h"

Result start_test(char words[0][128],int total_words){
    Result result = {0};
    if (total_words == 0){
        printf("no words loaded for test");
        return result;
    }

    shuffle_words(words, total_words);
    printf("Typing test started! you have 60 seconds \n");
    printf("Type each word and press ENTER.\n\n");

    // start timer
    time_t start_time = time(NULL);
    time_t current_time;
    char typed[128];
    int word_index = 0;
    // loop until 60 sec have passed 
    while(1){
        current_time = time(NULL);
        double elapsed = difftime(current_time, start_time);
        if(elapsed >= 60.0){
            break;
        }
        printf("[%d sec] Word: %s\n", (int)elapsed, words[word_index]);
        printf("Type: ");
        scanf("%31s", typed);
        result.total++;
        // compare with actual
        if (is_word_correct(typed, words[word_index])){
            result.correct++;
        }
        else{
            result.incorrect++;
        }
        //move to the next word 
        word_index = (word_index + 1) % total_words;
    }
    // calculate the final results
    result.accuracy = (result.total > 0)
                        ? ((double)result.correct / result.total) * 100.0
                        : 0.0;
    result.wpm = (double)result.correct; // since time is 1min
    return result;


    

}
