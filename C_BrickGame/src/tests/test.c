#include <check.h>
#include <stdio.h>

#include "../inc/tetris.h"

START_TEST(fsm_test_1) {
  GameStatus_t *game = start_game();
  ck_assert_int_eq(game->actual_status, Start);
  updateCurrentState(game);
  user_input(game, ' ');
  ck_assert_int_eq(game->actual_status, Pause);
  user_input(game, ' ');
  ck_assert_int_eq(game->actual_status, Nosig);
  game->actual_status = Terminate;
  free_tetris(game);
}
END_TEST

START_TEST(tetris_test_1) {
  ck_assert_int_eq(update_score(1), 100);
  ck_assert_int_eq(update_score(2), 300);
  ck_assert_int_eq(update_score(3), 700);
  ck_assert_int_eq(update_score(4), 1500);
}
END_TEST

START_TEST(tetris_test_2) {
  GameStatus_t *game = start_game();
  ck_assert_int_eq(game->game_info->score, 0);
  ck_assert_int_eq(game->game_info->level, 1);
  game->game_info->score = 600;
  calculate_speed(game);
  ck_assert_int_eq(game->game_info->level, 2);
  game->game_info->score = 15000;
  game->game_info->high_score = 10000;
  calculate_speed(game);
  updateCurrentState(game);
  ck_assert_int_eq(game->game_info->level, 10);
  free_tetris(game);
}
END_TEST

START_TEST(tetris_test_3) {
  GameStatus_t *game = start_game();
  game->cur_figure->x = 3;
  game->cur_figure->y = 13;
  game->actual_status = Down;
  updateCurrentState(game);

  int row = 0;
  int result = check_lines(game->field, row);
  ck_assert_int_eq(result, 0);
  delete_lines(game->field, row);
  free_tetris(game);
}

START_TEST(fsm_test_2) {
  GameStatus_t *game = start_game();
  ck_assert_int_eq(game->actual_status, Start);
  game->actual_status = Nosig;
  for (int x = 0; x < 10; x++) {
    move_down(game->cur_figure);
    move_action(game->cur_figure);
    updateCurrentState(game);
    user_input(game, KEY_LEFT);
    updateCurrentState(game);
    ck_assert_int_eq(game->actual_status, Left);
    user_input(game, KEY_RIGHT);
    updateCurrentState(game);
    ck_assert_int_eq(game->actual_status, Right);
    user_input(game, KEY_DOWN);
    updateCurrentState(game);
    ck_assert_int_eq(game->actual_status, Down);
  }
  user_input(game, KEY_UP);
  updateCurrentState(game);
  ck_assert_int_eq(game->actual_status, Action);
  user_input(game, Nosig);
  updateCurrentState(game);
  ck_assert_int_eq(game->actual_status, Nosig);
  user_input(game, 'q');
  ck_assert_int_eq(game->actual_status, Terminate);
  free_tetris(game);
}

START_TEST(tetris_test_4) {
  GameStatus_t *game = start_game();
  game->cur_figure->x = 2;
  game->cur_figure->y = 12;
  while (!check_collision(game)) {
    fsm_bad(game);
  }
  ck_assert_int_eq(game->actual_status, GameOver);
  free_tetris(game);
}

START_TEST(tetris_test_5) {
  GameStatus_t *game = start_game();
  game->actual_status = GameOver;
  user_input(game, ' ');
  ck_assert_int_eq(game->actual_status, GameOver);
  free_tetris(game);
}

int main() {
  Suite *s1 = suite_create("test_suite");
  TCase *tc1_1 = tcase_create("test_suite");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, fsm_test_1);
  tcase_add_test(tc1_1, fsm_test_2);
  tcase_add_test(tc1_1, tetris_test_1);
  tcase_add_test(tc1_1, tetris_test_2);
  tcase_add_test(tc1_1, tetris_test_3);
  tcase_add_test(tc1_1, tetris_test_4);
  tcase_add_test(tc1_1, tetris_test_5);

  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}