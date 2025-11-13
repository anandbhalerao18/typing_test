#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../include/tui.h"
#include "../include/file_handler.h"
#include "../include/utils.h"
#include "../include/logic.h"

// init

void init_tui() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    nodelay(stdscr, FALSE);
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_CYAN, COLOR_BLACK);   // title
        init_pair(2, COLOR_GREEN, COLOR_BLACK);  // correct
        init_pair(3, COLOR_RED, COLOR_BLACK);    // incorrect
        init_pair(4, COLOR_YELLOW, COLOR_BLACK); // highlight
        init_pair(5, COLOR_WHITE, COLOR_BLACK);  // normal text
    }
    clear();
    refresh();
}

void cleanup_tui() {
    endwin();
}

// hhelpers

static void draw_title() {
    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(1, 2, "⚡ Typing Speed Test (TUI) by Anand Bhalerao ⚡");
    attroff(COLOR_PAIR(1) | A_BOLD);
}

static void draw_centered(int row, const char *txt, int color_pair, int attr) {
    int cols = getmaxx(stdscr);
    int x = (cols - (int)strlen(txt)) / 2;
    if (color_pair) attron(COLOR_PAIR(color_pair));
    if (attr) attron(attr);
    mvprintw(row, x, "%s", txt);
    if (attr) attroff(attr);
    if (color_pair) attroff(COLOR_PAIR(color_pair));
}

// main menu

int show_main_menu() {
    const char *options[] = {"Start Typing Test", "Instructions", "Exit"};
    const int n = 3;
    int highlight = 0;
    int ch;

    while (1) {
        clear();
        draw_title();
        mvprintw(3, 2, "Use UP/DOWN and ENTER to select.");
        for (int i = 0; i < n; ++i) {
            if (i == highlight) {
                attron(A_REVERSE | COLOR_PAIR(4));
                mvprintw(6 + i, 6, "%s", options[i]);
                attroff(A_REVERSE | COLOR_PAIR(4));
            } else {
                mvprintw(6 + i, 6, "%s", options[i]);
            }
        }
        refresh();

        ch = getch();
        switch (ch) {
            case KEY_UP: highlight = (highlight - 1 + n) % n; break;
            case KEY_DOWN: highlight = (highlight + 1) % n; break;
            case 10: // ENTER
                if (highlight == 0) return 1;
                if (highlight == 1) { show_instructions(); break; }
                if (highlight == 2) return 0;
            default: break;
        }
    }
}

//INSTRUCTIONS 

void show_instructions() {
    clear();
    draw_title();
    mvprintw(4, 4, "Instructions:");
    mvprintw(6, 6, "1) You have 60 seconds to type as many words as possible.");
    mvprintw(7, 6, "2) Type the word shown and press ENTER after each word.");
    mvprintw(8, 6, "3) Green = correct, Red = incorrect.");
    mvprintw(9, 6, "4) When time is up, results will be displayed.");
    mvprintw(11, 6, "Press any key to return to the main menu...");
    refresh();
    getch();
}

//TYPING TEST 

Result run_typing_ui(char words[][MAX_WORD_LEN], int total_words) {
    Result result = {0};
    if (total_words <= 0) return result;

    shuffle_words(words, total_words);
    const int TIME_LIMIT = 60;
    time_t start_time = time(NULL);
    int word_index = 0;
    char input[MAX_WORD_LEN];
    int ch;

    nodelay(stdscr, TRUE);  // non-blocking input
    curs_set(1);

    while (1) {
        double elapsed = difftime(time(NULL), start_time);
        if (elapsed >= TIME_LIMIT) break;

        // === UI Update ===
        clear();
        draw_title();
        mvprintw(3, 2, "Time left: %d sec", TIME_LIMIT - (int)elapsed);
        mvprintw(5, 2, "Word:");
        attron(COLOR_PAIR(4) | A_BOLD);
        mvprintw(5, 9, "%s", words[word_index]);
        attroff(COLOR_PAIR(4) | A_BOLD);

        mvprintw(7, 2, "Type: %s", input);
        mvprintw(9, 2, "Progress: Typed=%d  Correct=%d  Incorrect=%d", 
                 result.total, result.correct, result.incorrect);

        // Show WPM live
        mvprintw(11, 2, "WPM: %.1f   Accuracy: %.1f%%",
                 (double)result.correct * (60.0 / (elapsed + 1)),
                 (result.total > 0) ? (double)result.correct / result.total * 100.0 : 0.0);

        mvprintw(13, 2, "Press ESC to abort test early.");
        refresh();

        //Typing logic
        timeout(200); // refresh every 200ms to update timer
        ch = getch();
        if (ch == 27) break;  // ESC pressed
        else if (ch == '\n') {
            if (strlen(input) > 0) {
                result.total++;
                if (is_word_correct(input, words[word_index])) {
                    result.correct++;
                    attron(COLOR_PAIR(2));
                    mvprintw(15, 2, " Correct!");
                    attroff(COLOR_PAIR(2));
                } else {
                    result.incorrect++;
                    attron(COLOR_PAIR(3));
                    mvprintw(15, 2, "Incorrect!");
                    attroff(COLOR_PAIR(3));
                }
                memset(input, 0, sizeof(input));
                word_index = (word_index + 1) % total_words;
                napms(300); // brief pause to show feedback
            }
        } else if (ch == KEY_BACKSPACE || ch == 127) {
            int len = strlen(input);
            if (len > 0) input[len - 1] = '\0';
        } else if (ch != ERR && strlen(input) < MAX_WORD_LEN - 1) {
            int len = strlen(input);
            input[len] = (char)ch;
            input[len + 1] = '\0';
        }
    }

    //Compute final results 
    result.accuracy = (result.total > 0)
                        ? ((double)result.correct / result.total) * 100.0
                        : 0.0;
    result.wpm = (double)result.correct * (60.0 / TIME_LIMIT);

    nodelay(stdscr, FALSE);
    curs_set(0);
    return result;
}

//RESULTS SCREEN 

void show_results_screen(Result result) {
    clear();
    draw_title();

    attron(COLOR_PAIR(2) | A_BOLD);
    mvprintw(4, 4, "======= Test Results =======");
    attroff(COLOR_PAIR(2) | A_BOLD);

    mvprintw(6, 6, "Total typed : %d", result.total);
    mvprintw(7, 6, "Correct     : %d", result.correct);
    mvprintw(8, 6, "Incorrect   : %d", result.incorrect);
    mvprintw(9, 6, "Accuracy    : %.2f%%", result.accuracy);
    mvprintw(10,6, "WPM         : %.2f", result.wpm);

    mvprintw(13, 4, "Press ENTER to return to main menu or ESC to exit.");
    refresh();

    int ch;
    while (1) {
        ch = getch();
        if (ch == 10) break;  // Enter -> return
        if (ch == 27) {       // ESC -> exit app
            cleanup_tui();
            exit(0);
        }
    }
}
