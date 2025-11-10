#include <stdio.h>
#include "../include/file_handler.h"

int main(){
    char words[MAX_WORDS][MAX_WORD_LEN];
    int count = load_words("data/words.txt", words);

    if (count <= 0){
        printf("no words loaded \n");
        return 1;
    }
    printf("Loaded %d words: \n", count);
    for (int i = 0; i < count && i < 10; i++){
        printf("%s ", words[i]);
    }
    printf("\n");
    return 0;
}