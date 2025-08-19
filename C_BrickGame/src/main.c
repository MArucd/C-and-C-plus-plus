#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "inc/defines.h"
#include "inc/frontend.h"

#define _POSIX_C_SOURCE 199309L

int game_loop(WinCurses *winGame);

int main(){
  WinCurses *winGame = init_curses();
  game_loop(winGame);

  return 0;
}

int game_loop(WinCurses *winGame) {
  GameStatus_t *game = start_game();
  struct timespec sp_start, sp_end, ts1, ts2 = {0, 0};
  while (game->actual_status != Terminate) {
    clock_gettime(CLOCK_MONOTONIC, &sp_start);
    print_frontend(game, winGame);
    int ch = getch();
    user_input(game, ch);
    if (game->actual_status != Pause) {
      updateCurrentState(game);
    }

    clock_gettime(CLOCK_MONOTONIC, &sp_end);

    if (sp_end.tv_sec - sp_start.tv_sec <= 0 &&
        (ts2.tv_nsec = 33000000 - game->game_info->speed -
                       (sp_end.tv_nsec - sp_start.tv_nsec)) > 0) {
      nanosleep(&ts2, &ts1);
    }
    if (game->actual_status == GameOver) {
      int quit = getch();
      if (quit == 'q') break;
    }
  }
  if (game->actual_status == GameOver) getch();
  if (game) free_tetris(game);
  if (winGame) free_curses(winGame);
  return 0;
}