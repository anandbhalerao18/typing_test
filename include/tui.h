#ifndef TUI_H
#define TUI_H

#include <ncurses.h>
#include<logic.h>

void init_ui() // init ncurses and setup the screen

int show_menu() // show the menu and return the user choice

void show_instructions(); // shows up the instrct screen

void run_typing_ui(char words[][32], init total_words); // main typing test ui

void show results(Result result);

void cleanup_ui();

#endif
