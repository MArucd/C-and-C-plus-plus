
#include "Tetromino.h"

namespace s21 {

Tetromino::Tetromino() {
  tCoords_.resize(4);
  SetRandomShape();
}

Tetromino::Tetromino(const Tetromino &other) {
  if (this != &other) {
    shape_ = other.shape_;
    tCoords_ = other.tCoords_;
  }
}

Tetromino &Tetromino::operator=(const Tetromino &other) {
  if (this != &other) {
    shape_ = other.shape_;
    tCoords_ = other.tCoords_;
  }
  return *this;
}

int Tetromino::GetMinX() {
  int res = tCoords_[0].x;
  for (int i = 0; i < 4; i++) {
    res = std::min(res, tCoords_[i].x);
  }
  return res;
}

int Tetromino::GetMaxX() {
  int res = tCoords_[0].x;
  for (int i = 0; i < 4; i++) {
    res = std::max(res, tCoords_[i].x);
  }
  return res;
}

int Tetromino::GetMinY() {
  int res = tCoords_[0].y;
  for (int i = 0; i < 4; i++) {
    res = std::min(res, tCoords_[i].y);
  }
  return res;
}

int Tetromino::GetMaxY() {
  int res = tCoords_[0].y;
  for (int i = 0; i < 4; i++) {
    res = std::max(res, tCoords_[i].y);
  }
  return res;
}

void Tetromino::Rotate() {
  if (shape_ == TetroShape::SquareShape) return;

  int center_x = GetMaxX() - 1;
  int center_y = GetMaxY() - 1;

  std::vector<Coordinates> newCoords(4);
  int rotationMatrix[2][2] = {{0, -1}, {1, 0}};

  for (int i = 0; i < 4; i++) {
    int x = tCoords_[i].x - (center_x);
    int y = tCoords_[i].y - (center_y);
    int newX = rotationMatrix[0][0] * x + rotationMatrix[0][1] * y + (center_x);
    int newY = rotationMatrix[1][0] * x + rotationMatrix[1][1] * y + (center_y);
    newCoords[i] = {newX, newY};
  }
  tCoords_ = newCoords;
  while (GetMinY() <= 0) {
    MoveDown();
  }
  while (GetMaxX() >= static_cast<int>(GameSizes::fieldWidth)) {
    MoveLeft();
  }
  while (GetMinX() < 0) {
    MoveRight();
  }
}

void Tetromino::SetRandomShape() {
  std::random_device rd;
  std::default_random_engine gen(rd());
  std::uniform_int_distribution<int> distribution(1, 7);
  auto rand_shape = static_cast<TetroShape>(distribution(gen));
  SetShape(rand_shape);
}

void Tetromino::SetShape(TetroShape s) {
  shape_ = s;
  for (int i = 0; i < 4; i++) {
    tCoords_[i].x = TetroCoords::coordsTable[static_cast<int>(s)][i][1] +
                    (GameSizes::fieldWidth / 2);
    tCoords_[i].y = TetroCoords::coordsTable[static_cast<int>(s)][i][0] - 1;
  }
  while (GetMinY() < 1) MoveDown();
}

void Tetromino::MoveDown() {
  if (GetMaxY() >= GameSizes::fieldHeight) return;
  for (auto &i : tCoords_) {
    i.y += 1;
  }
}

void Tetromino::MoveLeft() {
  if (GetMinX() < 1) return;
  for (auto &i : tCoords_) {
    i.x -= 1;
  }
}

void Tetromino::MoveRight() {
  if (GetMaxX() == GameSizes::fieldWidth - 1) return;
  for (auto &i : tCoords_) {
    i.x += 1;
  }
}

}  // namespace s21