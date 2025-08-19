#ifndef TETRIS_H
#define TETRIS_H

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "defines.h"


typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;


typedef struct Field_t {
  int **blocks;
} Field_t;


typedef struct Figure_t {
  int **blocks;
  int x;
  int y;
  int color;
  bool rotatble;
} Figure_t;


typedef struct GameStatus_t {
  Field_t *field;
  GameInfo_t *game_info;
  Figure_t *cur_figure;
  Figure_t *next_figure;
  int actual_status;
  int ticks;
  int ticks_left;
  int action;
} GameStatus_t;

typedef enum {
  Start,
  Nosig,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action,
  GameOver
} UserAction_t;

GameStatus_t *start_game();

Field_t *create_field();

Figure_t *create_figure();

Figure_t *get_figure();

void move_down(Figure_t *figure);

void move_left(Figure_t *figure);

void move_right(Figure_t *figure);

void move_action(Figure_t *figure);

int check_collision(GameStatus_t *game);

int check_corners(int row, int col, int pos_y, int pos_x);

void place_figure(GameStatus_t *game);

void get_new_figure(GameStatus_t *game);

void free_figure(Figure_t *figure);

void fsm_bad(GameStatus_t *game);

void user_input(GameStatus_t *game, int hold);

void delete_lines(Field_t *field, int row);

int check_lines(Field_t *field, int row);

int full_lines(GameStatus_t *game);

int update_score(int count);

int write_record(int score);

int load_record();

void free_field(Field_t *field);

void free_tetris(GameStatus_t *game);

GameStatus_t *updateCurrentState(GameStatus_t *game);

void calculate_speed(GameStatus_t *game);

#endif
