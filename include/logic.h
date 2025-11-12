#ifndef LOGIC_H
#define LOGIC_H
#include <time.h>
// struct to store results
typedef struct {
    int correct;
    int incorrect;
    int total;
    double accuracy;
    double wpm;
} Result;

Result start_test(char words[][128], int total_words);
#endif