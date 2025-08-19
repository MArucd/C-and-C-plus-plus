#include "../../inc/frontend.h"

#include "../../inc/tetris.h"

WinCurses *init_curses() {
  initscr();  // инициализирует библиотеку curses и создает экранный буфер.
  keypad(stdscr,
         TRUE);  // включает обработку функциональных клавиш на клавиатуре.
  nodelay(stdscr, TRUE);  // делает операцию чтения с клавиатуры неблокирующей.
  raw();  // символы, вводимые с клавиатуры, немедленно передаются программе.
  noecho();  // отключает отображение вводимых символов на экране.
  cbreak();  // отключает буферизацию ввода, позволяя программе читать ввод
             // пользователя посимвольно, без ожидания нажатия клавиши Enter.
  curs_set(0);  // cкрывает курсор на экране.
  start_color();  // инициализирует функцию цвета в curses.
  init_colors();
  WinCurses *winGame = create_frontend();
  return winGame;
}

WinCurses *create_frontend() {
  WinCurses *winGame = (WinCurses *)malloc(sizeof(WinCurses));
  if (winGame == NULL) {
    return NULL;
  }
  winGame->winBoard = newwin(BOARD_HEIGHT, BOARD_WIDTH, Y_START, X_START);
  winGame->winBrick = newwin(NEXT_HEIGHT, NEXT_WIDTH, NEXT_Y, NEXT_X);
  winGame->winScore = newwin(SCORE_HEIGHT, SCORE_WIDTH, SCORE_Y, SCORE_X);
  winGame->winInput = newwin(INPUT_HEIGHT, INPUT_WIDTH, INPUT_Y, INPUT_X);

  refresh();

  box(winGame->winBoard, 0, 0);
  box(winGame->winBrick, 0, 0);
  box(winGame->winScore, 0, 0);
  box(winGame->winInput, 0, 0);
  return winGame;
}

void print_frontend(GameStatus_t *game, WinCurses *winGame) {
  if (game->actual_status == Start) {
    wait_start(winGame->winBoard);
    game->actual_status = Nosig;
  } else if (game->actual_status != Pause && game->actual_status != GameOver) {
    print_field(game->field, winGame->winBoard);
    output_input(winGame->winInput);
    print_score(game, winGame->winScore);
    print_figure(game->cur_figure, winGame->winBoard);
    clear_figure(winGame->winBrick, FIGURE_S, FIGURE_S);
    print_figure(game->next_figure, winGame->winBrick);

  } else if (game->actual_status == Pause) {
    print_pause(winGame->winBoard);
  } else if (game->actual_status == GameOver) {
    game_over(winGame->winBoard);
  }
  wrefresh(winGame->winBoard);
  wrefresh(winGame->winInput);
  wrefresh(winGame->winBrick);
  wrefresh(winGame->winScore);
}

void print_field(const Field_t *field, WINDOW *win) {
  for (int row = 0; row < F_HEIGHT; row++) {
    for (int col = 0; col < F_WIDTH; col++) {
      {
        if (field->blocks[row][col] == 0) {
          wbkgdset(win, COLOR_PAIR(1));
          mvwprintw(win, row + 1, 2 * col + 1, "%c", ' ');
          mvwprintw(win, row + 1, 2 * col + 2, "%c", ' ');
        } else {
          wbkgdset(win, COLOR_PAIR(6));
          mvwprintw(win, row + 1, 2 * col + 1, "%c", ' ');
          mvwprintw(win, row + 1, 2 * col + 2, "%c", ' ');
        }
      }
    }
  }
}

void print_figure(Figure_t *figure, WINDOW *win) {
  for (int row = 0; row < FIGURE_S; row++) {
    for (int col = 0; col < FIGURE_S; col++) {
      int y_pos = figure->y + row;
      int x_pos = figure->x + col;

      if (figure->blocks[row][col] != 0 && y_pos >= 0) {
        wbkgdset(win, COLOR_PAIR(figure->color));
        mvwprintw(win, y_pos + 1, 2 * x_pos + 1, "%c", ' ');
        mvwprintw(win, y_pos + 1, 2 * x_pos + 2, "%c", ' ');
      }
    }
  }
}

void clear_figure(WINDOW *win, int y_pos, int x_pos) {
  for (int row = 0; row <= y_pos; row++) {
    for (int col = 0; col <= x_pos; col++) {
      wbkgdset(win, COLOR_PAIR(1));
      mvwprintw(win, row + 1, 2 * col + 2, "%c", ' ');
      mvwprintw(win, row + 1, 2 * col + 1, "%c", ' ');
    }
  }
}

void output_input(WINDOW *win) {
  mvwprintw(win, 3, 3, "%s", "Quit(Q)");
  mvwprintw(win, 1, 3, "%s", "Pause(SPACE)");
  mvwprintw(win, 1, 20, "%s", "UP - Rotate");
  mvwprintw(win, 3, 20, "%s", "DOWN - Drop");
  mvwprintw(win, 5, 20, "%s", "<- -> - move");
  mvwprintw(win, 5, 3, "%s", "GIT GUD");
}

void wait_start(WINDOW *win) {
  mvwprintw(win, F_HEIGHT / 2 - 1, (F_WIDTH - 6), "PRESS ANY KEY");
  mvwprintw(win, F_HEIGHT / 2, (F_WIDTH - 4), "TO START!");
  wrefresh(win);
  nodelay(stdscr, FALSE);
  getch();
  nodelay(stdscr, TRUE);
}

void print_pause(WINDOW *win) {
  wbkgdset(win, COLOR_PAIR(0));
  mvwprintw(win, F_HEIGHT / 2 - 1, (F_WIDTH - 2), "PAUSE");
  wrefresh(win);
  nodelay(stdscr, FALSE);
  getch();
  nodelay(stdscr, TRUE);
}

void print_score(GameStatus_t *game, WINDOW *win) {
  mvwprintw(win, 1, 2, "%s", "level:");
  mvwprintw(win, 3, 2, "%d", game->game_info->level);

  mvwprintw(win, 5, 2, "%s", "score:");
  mvwprintw(win, 7, 2, "%d  ", game->game_info->score);

  mvwprintw(win, 9, 2, "%s", "record:");
  mvwprintw(win, 11, 2, "%d", game->game_info->high_score);
}

// 64 пары цветов
void init_colors() {
  int i, j, ck = 1;
  for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++) {
      init_pair(ck++, i, j);
    }
  }
  init_pair(0, COLOR_WHITE, COLOR_BLACK);
}

void free_curses(WinCurses *win) {
  if (win) free(win);
  endwin();
}

void game_over(WINDOW *win) {
  wbkgdset(win, COLOR_PAIR(0));
  mvwprintw(win, F_HEIGHT / 2 - 1, (F_WIDTH - 2), "GAME OVER!");
  wrefresh(win);
}