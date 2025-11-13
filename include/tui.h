#ifndef TUI_H
#define TUI_H

#include <ncurses.h>
#include "logic.h"
#include "file_handler.h"

// Initialize ncurses and screen setup
void init_tui();

// Display the main menu (returns 1 if user starts test, 0 if exit)
int show_main_menu();

// Show simple typing instructions
void show_instructions();

// Run the typing test interface
Result run_typing_ui(char words[][MAX_WORD_LEN], int total_words);

// Show the results screen
void show_results_screen(Result result);

// Cleanup and restore terminal state
void cleanup_tui();

#endif
