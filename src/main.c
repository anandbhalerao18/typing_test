#include <stdio.h>
#include "../include/file_handler.h"
#include "../include/logic.h"

int main(){
    char words[MAX_WORDS][MAX_WORD_LEN];
    int count = load_words("data/words.txt", words);

    if (count <= 0){
        printf("no words loaded \n");
        return 1;
    }
    Result result = start_test(words, count);
    printf("\n=== Test Finished ===\n");
    printf("Total Words Typed: %d\n", result.total);
    printf("Correct: %d\n", result.correct);
    printf("Incorrect: %d\n",result.incorrect);
    printf("Accuracy: %.2f%%\n", result.accuracy);
    printf("WPM: %.2f\n", result.wpm);
    return 0;
}