#include "../../inc/tetris.h"

GameStatus_t *start_game(){
    GameStatus_t *game = (GameStatus_t *)malloc(sizeof(GameStatus_t));
    game->game_info = (GameInfo_t *)malloc(sizeof(GameInfo_t));
    game->field = create_field();

    game->ticks = 30;
    game->ticks_left = 30;

    srand((unsigned)time(NULL));
    game->cur_figure = get_figure();
    game->cur_figure->x = FIGURE_X;
    game->next_figure = get_figure();

    game->actual_status = Start;

    game->game_info->level = 1;
    game->game_info->high_score = load_record();
    game->game_info->score = 0;
    game->game_info->speed = 1;
    return game;
}

void fsm_bad(GameStatus_t *game){
    if (game->ticks_left <= 0) {
        game->ticks_left = game->ticks;
        move_down(game->cur_figure);

        if (check_collision(game)){
            game->cur_figure->y--;
            place_figure(game);
            int count = full_lines(game);
            game->game_info->score = game->game_info->score + update_score(count);
            calculate_speed(game);
            get_new_figure(game);
            if(check_collision(game)) game->actual_status = GameOver;

        }

    }
    else {
        switch (game->actual_status) {
            case Action: {
                move_action(game->cur_figure);
                if (check_collision(game)) for(int i = 0; i < 3; i++){
                    move_action(game->cur_figure);
                }
                break;
            }
            case Left: {
                move_left(game->cur_figure);
                if (check_collision(game)) move_right(game->cur_figure);
                break;
            }
            case Right: {
                move_right(game->cur_figure);
                if (check_collision(game)) move_left(game->cur_figure);
                break;
            }
            case Down: {
                move_down(game->cur_figure);
                if (check_collision(game)) {
                    game->cur_figure->y--;
                    place_figure(game);
                    int count = full_lines(game);
                    game->game_info->score = game->game_info->score + update_score(count);
                    calculate_speed(game);
                    get_new_figure(game);
                    if (check_collision(game)) game->actual_status = GameOver;
                }
            break;
            }
        }
    }
    game->ticks_left--;
}

void user_input(GameStatus_t *game, int hold) {
  switch (hold) {
    case KEY_UP:
      game->actual_status = Action;
      break;
    case KEY_DOWN:
      game->actual_status = Down;
      break;
    case KEY_LEFT:
      game->actual_status = Left;
      break;
    case KEY_RIGHT:
      game->actual_status = Right;
      break;
    case 'q':
      game->actual_status = Terminate;
      break;
    case ' ':
      if (game->actual_status == Pause)
        game->actual_status = Nosig;
      else if (game->actual_status != GameOver)
        game->actual_status = Pause;
      break;
    default:
      if (game->actual_status != GameOver) game->actual_status = Nosig;
      break;
  }
}

GameStatus_t *updateCurrentState(GameStatus_t *game) {
  if (game->actual_status != Terminate) fsm_bad(game);
  if (game->game_info->score > game->game_info->high_score) {
    game->game_info->high_score = game->game_info->score;
    write_record(game->game_info->high_score);
  }
  return game;
}