#include "../../inc/frontend.h"
#include "../../inc/tetris.h"

Field_t *create_field() {
  Field_t *field = (Field_t *)malloc(sizeof(Field_t));
  field->blocks = (int **)calloc(F_HEIGHT, sizeof(int *));
  for (int row = 0; row < F_HEIGHT; row++) {
    field->blocks[row] = (int *)calloc(F_WIDTH, sizeof(int));
  }
  return field;
}

Figure_t *create_figure() {
  Figure_t *figure = (Figure_t *)malloc(sizeof(Figure_t));
  figure->blocks = (int **)calloc(FIGURE_S, sizeof(int *));
  for (int row = 0; row < FIGURE_S; row++) {
    figure->blocks[row] = (int *)calloc(FIGURE_S, sizeof(int));
  }
  figure->y = 0;
  return figure;
}

Figure_t *get_figure() {
  Figure_t *figure = create_figure();

  int my_brick[7][FIGURE_S][FIGURE_S] = {

      {{0, 0, 0, 0, 0},
       {0, 0, 1, 0, 0},
       {0, 1, 1, 1, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}},

      {{0, 0, 0, 0, 0},
       {0, 1, 1, 0, 0},
       {0, 0, 1, 1, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}},

      {{0, 0, 0, 0, 0},
       {0, 0, 1, 1, 0},
       {0, 1, 1, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}},

      {{0, 0, 0, 0, 0},
       {0, 1, 0, 0, 0},
       {0, 1, 1, 1, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}},

      {{0, 0, 0, 0, 0},
       {0, 0, 0, 1, 0},
       {0, 1, 1, 1, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}},

      {{0, 0, 1, 0, 0},
       {0, 0, 1, 0, 0},
       {0, 0, 1, 0, 0},
       {0, 0, 1, 0, 0},
       {0, 0, 0, 0, 0}},

      {{0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 1, 1, 0},
       {0, 0, 1, 1, 0},
       {0, 0, 0, 0, 0}}

  };

  int random_brick = rand() % 7;
  if (random_brick == 6) {
    figure->rotatble = false;
  } else {
    figure->rotatble = true;
  }
  for (int i = 0; i < FIGURE_S; i++) {
    for (int j = 0; j < FIGURE_S; j++) {
      figure->blocks[i][j] = my_brick[random_brick][i][j];
    }
  }

  figure->color = random_brick + 2;

  return figure;
}

void get_new_figure(GameStatus_t *game) {
  free_figure(game->cur_figure);
  game->cur_figure = game->next_figure;
  game->cur_figure->x = FIGURE_X;
  game->cur_figure->y = -3;
  game->next_figure = get_figure();
}

void free_figure(Figure_t *figure) {
  if (figure) {
    if (figure->blocks) {
      for (int row = 0; row < FIGURE_S; row++) {
        if (figure->blocks[row]) {
          free(figure->blocks[row]);
        }
      }
      free(figure->blocks);
    }
    free(figure);
  }
}

void move_down(Figure_t *figure) { figure->y++; }

void move_left(Figure_t *figure) { figure->x--; }

void move_right(Figure_t *figure) { figure->x++; }

void move_action(Figure_t *figure) {
  if (figure->rotatble) {
    Figure_t *new_figure = create_figure();

    for (int row = 0; row < FIGURE_S; row++) {
      for (int col = 0; col < FIGURE_S; col++) {
        new_figure->blocks[col][row] = figure->blocks[row][FIGURE_S - col - 1];
      }
    }
    for (int row = 0; row < FIGURE_S; row++) {
      for (int col = 0; col < FIGURE_S; col++) {
        figure->blocks[col][row] = new_figure->blocks[col][row];
      }
    }
    free_figure(new_figure);
  }
}

int check_collision(GameStatus_t *game) {
  int check = 0;
  int pos_y = game->cur_figure->y;
  int pos_x = game->cur_figure->x;
  int **field = game->field->blocks;
  int **figure = game->cur_figure->blocks;

  for (int row = 0; row < FIGURE_S; row++) {
    for (int col = 0; col < FIGURE_S; col++) {
      int fgr = figure[row][col];

      if (fgr != 0) {
        if (pos_y + row < 0) {
          continue;
        } else if (check_corners(row, col, pos_y, pos_x)) {
          if (field[pos_y + row][pos_x + col] != 0) {
            check = 1;

            if (pos_y + row == 0) {
              game->actual_status = GameOver;
              break;
            }
            break;
          }
        } else {
          check = 1;
          break;
        }
      }
    }
    if (check) {
      break;
    }
  }

  return check;
}

int check_corners(int row, int col, int pos_y, int pos_x) {
  int check = 1;
  if ((row + pos_y > F_HEIGHT - 1 || row + pos_y < 0) ||
      (col + pos_x > F_WIDTH - 1 || col + pos_x < 0))
    check = 0;
  return check;
}

void place_figure(GameStatus_t *game) {
  int pos_y = game->cur_figure->y;
  int pos_x = game->cur_figure->x;

  for (int row = 0; row < FIGURE_S; row++) {
    for (int col = 0; col < FIGURE_S; col++) {
      int fgr = game->cur_figure->blocks[row][col];
      if (fgr != 0 && pos_y + row >= 0) {
        game->field->blocks[pos_y + row][pos_x + col] = fgr;
      }
    }
  }
}

int full_lines(GameStatus_t *game) {
  int check = 0;
  for (int row = F_HEIGHT - 1; row >= 0; row--) {
    while (check_lines(game->field, row)) {
      delete_lines(game->field, row);
      check++;
    }
  }
  return check;
}

int check_lines(Field_t *field, int row) {
  int check = 1;
  for (int col = 0; col < F_WIDTH; col++) {
    int block = field->blocks[row][col];
    if (block == 0) {
      check = 0;
    }
  }
  return check;
}

void delete_lines(Field_t *field, int row) {
  if (row == F_HEIGHT) {
    for (int col = 0; col < F_WIDTH; col++) field->blocks[row][col] = 0;
  } else {
    for (int i = row; i > 0; i--) {
      for (int col = 0; col < F_WIDTH; col++) {
        field->blocks[i][col] = field->blocks[i - 1][col];
      }
    }
  }
}

int update_score(int count) {
  int check = 0;
  if (count == 1)
    check = 100;
  else if (count == 2)
    check = 300;
  else if (count == 3)
    check = 700;
  else if (count >= 4)
    check = 1500;

  return check;
}

int write_record(int score) {
  FILE *f = fopen("build/record.txt", "w");
  if (f) {
    fprintf(f, "%d", score);
    fclose(f);
  }
  return 0;
}

int load_record() {
  FILE *f = fopen("build/record.txt", "r");
  int high_score = 0;
  if (f) {
    fscanf(f, "%d", &high_score);
    fclose(f);
  }
  return high_score;
}

void free_tetris(GameStatus_t *game) {
  if (game) {
    free_figure(game->cur_figure);
    free_figure(game->next_figure);
    free_field(game->field);
    free(game->game_info);
    free(game);
  }
}

void free_field(Field_t *field) {
  if (field) {
    if (field->blocks) {
      for (int row = 0; row < F_HEIGHT; row++) {
        if (field->blocks[row]) {
          free(field->blocks[row]);
        }
      }
      free(field->blocks);
    }
    free(field);
  }
}

void calculate_speed(GameStatus_t *game) {
  game->game_info->level = 1 + game->game_info->score / 600;
  if (game->game_info->level > 10) game->game_info->level = 10;

  game->game_info->speed = game->game_info->level * BASE_SPEED;
}