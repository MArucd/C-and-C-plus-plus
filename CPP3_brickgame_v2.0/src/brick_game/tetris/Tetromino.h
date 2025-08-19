#ifndef BRICKGAME_TETRIS_TETROMINO_H_
#define BRICKGAME_TETRIS_TETROMINO_H_

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>

#include "../common/Constants.h"

namespace s21 {

enum struct TetroShape {
  NoShape,
  ZShape,
  SShape,
  LineShape,
  TShape,
  SquareShape,
  LShape,
  MirroredLShape
};

namespace TetroCoords {
static constexpr int coordsTable[8][4][2] = {
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}},     // NoShape
    {{0, -1}, {0, 0}, {-1, 0}, {-1, 1}},  // ZShape
    {{0, -1}, {0, 0}, {1, 0}, {1, 1}},    // SShape
    {{0, -1}, {0, 0}, {0, 1}, {0, 2}},    // LineShape
    {{-1, 0}, {0, 0}, {1, 0}, {0, 1}},    // TShape
    {{0, 0}, {1, 0}, {0, 1}, {1, 1}},     // SquareShape
    {{-1, -1}, {0, -1}, {0, 0}, {0, 1}},  // LShape
    {{1, -1}, {0, -1}, {0, 0}, {0, 1}}    // MirroredLShape
};
};

class Tetromino {
 public:
  Tetromino();
  Tetromino(const Tetromino &other);
  Tetromino &operator=(const Tetromino &other);

  std::vector<Coordinates> GetCoords() { return tCoords_; }

  bool operator==(const Tetromino &other) const {
    return shape_ == other.shape_ && tCoords_ == other.tCoords_;
  }

  bool operator!=(const Tetromino &other) const { return !(*this == other); }

  void SetShape(TetroShape s);
  void SetRandomShape();

  TetroShape GetShape() { return shape_; }
  void Rotate();
  void MoveDown();
  void MoveLeft();
  void MoveRight();

  int GetMinX();
  int GetMaxX();
  int GetMinY();
  int GetMaxY();

 private:
  TetroShape shape_;
  std::vector<Coordinates> tCoords_;
};  // Tetrominint
}  // namespace s21

#endif  // BRICKGAME_TETRIS_TETROMINO_H_