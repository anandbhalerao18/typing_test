#include <stdio.h>
#include "../include/tui.h"
#include "../include/file_handler.h"

int main(void) {
    init_tui();

    while (1) {
        int sel = show_main_menu();
        if (!sel) break; // exit chosen

        
        char words[MAX_WORDS][MAX_WORD_LEN];
        int count = load_words("data/words.txt", words);
        if (count <= 0) {
            // Show simple error inside ncurses
            clear();
            mvprintw(4, 4, "Error: Could not load words from data/words.txt");
            mvprintw(6, 4, "Press any key to return to menu.");
            refresh();
            getch();
            continue;
        }

        
        Result res = run_typing_ui(words, count);
        show_results_screen(res);
    }

    cleanup_tui();
    return 0;
}
