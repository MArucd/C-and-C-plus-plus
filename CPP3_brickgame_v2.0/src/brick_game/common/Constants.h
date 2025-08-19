#ifndef BRICKGAME_CONSTANTS_HH_
#define BRICKGAME_CONSTANTS_HH_

#include <iostream>
#include <vector>

namespace s21 {

namespace GameSizes {
constexpr int kDotSize = 30;
constexpr int fieldWidth = 10;
constexpr int fieldHeight = 20;
constexpr int sidePanelHeight = 5;
constexpr int windowHeight = 21;
constexpr int windowWidth = 22;
static constexpr int IntervalMs[] = {500, 420, 340, 260, 230,
                                     200, 180, 160, 140, 125};
};  // namespace GameSizes

enum class GameState { start, spawn, moving, collide, Pause, exit, gameOver };

enum class UserAction {
  noSig,
  left,
  right,
  down,
  up,
  spaceBtn,
  enterBtn,
  escBtn,
  tabBtn
};

struct Coordinates {
  Coordinates() : x(0), y(0) {}
  Coordinates(int x_, int y_) : x(x_), y(y_) {}
  bool operator==(const Coordinates &other) const {
    return (x == other.x && y == other.y);
  }
  int x;
  int y;
};

}  // namespace s21
#endif  // BRICKGAME_CONSTANTS_H_