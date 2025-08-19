#ifndef BRICKGAME_GUI_CONSOLE_COMMON_H_
#define BRICKGAME_GUI_CONSOLE_COMMON_H_

#include <ncurses.h>

#include <chrono>
#include <cmath>
#include <string>
#include <thread>

#include "../../../brick_game/common/Constants.h"

namespace s21 {

enum class ColorIndex {
  Red = 100,
  Green,
  Cyan,
  Purple,
  Yellow,
  Orange,
  Blue,
  Gray
};  // ColorIndex

enum class Choose { Snake, Tetris, Menu, Exit };  // Choose

class BaseView {
 public:
  virtual void Start() = 0;

  static void DrawBox(int topLeftY, int topLeftX, int bottomRightY,
                      int bottomRightX);

  static void GameFieldRendering(Choose currGame, int level, int score,
                                 int record);

  static void GameResultRendering(bool isVictory, int level, int score);

  static void PauseRendering(int level, int score);

  static void StartGameRendering();

  static UserAction GetAction();

  static Choose InitMenu();
  static void MenuRendering(std::size_t& selectedItem);
};  // BaseView

}  // namespace s21

#endif  // BRICKGAME_GUI_CONSOLE_COMMON_H_