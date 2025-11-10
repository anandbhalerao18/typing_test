#ifndef LOGIC_H
#define LOGIC_H
#include <time.h>
// struct to store results
typedef struct {
    int correct;
    int incorrect;
    int totat;
    double accuracy;
    double wpm;
} Result;

Result start_test(char words[][32], init total_words);
#endif