#ifndef FRONTEND_H
#define FRONTEND_H

#include "tetris.h"

typedef struct WinCurses {
    WINDOW *winBoard;
    WINDOW *winBrick;
    WINDOW *winScore;
    WINDOW *winInput;
} WinCurses;

WinCurses *init_curses();

WinCurses *create_frontend();

void print_frontend(GameStatus_t *game, WinCurses *winGame);

void print_field(const Field_t *field, WINDOW *win);

void print_figure(Figure_t *figure, WINDOW *win);

void clear_figure(WINDOW *win, int y_pos, int x_pos);

void output_input(WINDOW *win);

void print_score(GameStatus_t *game, WINDOW *win);

void print_pause(WINDOW *win);

void init_colors();

void wait_start(WINDOW *win);

void game_over(WINDOW *win);

void free_curses(WinCurses *win);

#endif