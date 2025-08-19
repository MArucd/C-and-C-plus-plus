#ifndef BRICKGAME_GUI_COMMON_CONSOLE_VIEW_H_
#define BRICKGAME_GUI_COMMON_CONSOLE_VIEW_H_

#include <ncurses.h>

#include "../snake/SnakeConsoleView.h"
#include "../tetris/TetrisConsoleView.h"
#include "BaseView.h"

namespace s21 {

class BrickGameConsoleView : public BaseView {
 public:
  explicit BrickGameConsoleView(SnakeController* s_c = nullptr,
                                TetrisController* t_c = nullptr);
  ~BrickGameConsoleView() = default;

  void Start() override;

 protected:
  static void InitNcurses();

 private:
  void MainLoop();

  SnakeConsoleView snakeView_;
  TetrisConsoleView tetrisView_;
  static void InitColors();
};

}  // namespace s21

#endif  // BRICKGAME_GUI_COMMON_CONSOLE_VIEW_H_
