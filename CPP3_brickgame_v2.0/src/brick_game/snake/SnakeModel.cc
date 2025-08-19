#include "SnakeModel.h"

namespace s21 {

SnakeModel::SnakeModel() : s_data_() {
  s_data_.bestScore = LoadScore("SnakeScore.txt");
}

SnakeModel::~SnakeModel() {
  SaveScore(s_data_.bestScore, "SnakeScore.txt");
  s_data_.snakeBodyCoord.clear();
}

void SnakeModel::updateData(UserAction action) {
  s_data_.isModified = false;
  SnakeGameData dataCast = s_data_;
  currTime_ = lastMovingTime_;
  if (s_data_.gameStatus != GameState::Pause) {
    currTime_ = GetCurrentTime();
  }

  Action func = snakeActionTable[static_cast<int>(s_data_.gameStatus)]
                                [static_cast<int>(action)];
  if (func) {
    (this->*func)();
  }

  if (s_data_.gameStatus == GameState::moving) {
    if (currTime_ - lastMovingTime_ > currDelay) {
      moveSnake();
    }
  }
  if (s_data_ != dataCast) s_data_.isModified = true;
}

SnakeGameData& SnakeModel::getModelData() { return s_data_; }

void SnakeModel::setGameDataDefault() {
  currDelay = GameSizes::IntervalMs[0];
  lastMovingTime_ = currTime_ = GetCurrentTime();
  s_data_.currScore = 0;
  s_data_.level = 1;
  s_data_.direction = Direction::up;
  s_data_.gameStatus = GameState::start;
  s_data_.snakeBodyCoord.clear();
  s_data_.snakeBodyCoord.reserve(200);

  s_data_.snakeBodyCoord.push_back({5, GameSizes::fieldHeight / 2});
  s_data_.snakeBodyCoord.push_back({5, GameSizes::fieldHeight / 2 + 1});
  s_data_.snakeBodyCoord.push_back({5, GameSizes::fieldHeight / 2 + 2});
  s_data_.snakeBodyCoord.push_back({5, GameSizes::fieldHeight / 2 + 3});

  updateFruitPos();
}

void SnakeModel::updateFruitPos() {
  std::random_device rd;
  std::default_random_engine gen(rd());
  std::uniform_int_distribution<int> width_distribution(
      0, GameSizes::fieldWidth - 1);
  std::uniform_int_distribution<int> height_distribution(
      0, GameSizes::fieldHeight - 1);

  s_data_.fruitCoord.x = width_distribution(gen);
  s_data_.fruitCoord.y = height_distribution(gen);

  for (const auto& i : s_data_.snakeBodyCoord) {
    if (s_data_.fruitCoord.x == i.x && s_data_.fruitCoord.y == i.y) {
      updateFruitPos();
    }
  }
}

void SnakeModel::moveSnake() {
  switch (s_data_.direction) {
    case Direction::up:
      moveHeadUp();
      break;
    case Direction::down:
      moveHeadDown();
      break;
    case Direction::left:
      moveHeadLeft();
      break;
    case Direction::right:
      moveHeadRight();
      break;
  }
}

void SnakeModel::moveSnakeBody() {
  for (auto i = s_data_.snakeBodyCoord.size(); i > 0; --i) {
    s_data_.snakeBodyCoord[i] = s_data_.snakeBodyCoord[i - 1];
  }
}

void SnakeModel::checkSnakeLife() {
  for (std::size_t i = 1; i < s_data_.snakeBodyCoord.size(); ++i) {
    if (s_data_.snakeBodyCoord[0] == s_data_.snakeBodyCoord[i]) {
      s_data_.gameStatus = GameState::collide;
    }
  }
  if (s_data_.snakeBodyCoord[0].x < 0 ||
      s_data_.snakeBodyCoord[0].x >= GameSizes::fieldWidth) {
    s_data_.gameStatus = GameState::collide;
  }

  if (s_data_.snakeBodyCoord[0].y < 0 ||
      s_data_.snakeBodyCoord[0].y >= GameSizes::fieldHeight) {
    s_data_.gameStatus = GameState::collide;
  }
}

void SnakeModel::checkSnakeEating() {
  if (s_data_.snakeBodyCoord[0] == s_data_.fruitCoord) {
    s_data_.snakeBodyCoord.push_back({-1, 1});
    s_data_.currScore++;
    if (s_data_.currScore % 5 == 0 && s_data_.level < 10) {
      s_data_.level++;
      currDelay = GameSizes::IntervalMs[s_data_.level - 1];
    }
    if (s_data_.currScore > s_data_.bestScore) {
      s_data_.bestScore = s_data_.currScore;
    }
    if (s_data_.currScore == 200) {
      s_data_.isVictory = true;
      s_data_.gameStatus = GameState::gameOver;
    }
    updateFruitPos();
  }
}

void SnakeModel::moveHeadLeft() {
  if (s_data_.direction == Direction::right) return;
  s_data_.direction = Direction::left;
  moveSnakeBody();
  s_data_.snakeBodyCoord[0].x -= 1;

  checkSnakeEating();
  checkSnakeLife();
  lastMovingTime_ = currTime_;
}

void SnakeModel::moveHeadRight() {
  if (s_data_.direction == Direction::left) return;
  s_data_.direction = Direction::right;
  moveSnakeBody();
  s_data_.snakeBodyCoord[0].x += 1;

  checkSnakeEating();
  checkSnakeLife();
  lastMovingTime_ = currTime_;
}

void SnakeModel::moveHeadUp() {
  if (s_data_.direction == Direction::down) return;
  s_data_.direction = Direction::up;
  moveSnakeBody();
  s_data_.snakeBodyCoord[0].y -= 1;

  checkSnakeEating();
  checkSnakeLife();
  lastMovingTime_ = currTime_;
}

void SnakeModel::moveHeadDown() {
  if (s_data_.direction == Direction::up) return;
  s_data_.direction = Direction::down;
  moveSnakeBody();
  s_data_.snakeBodyCoord[0].y += 1;

  checkSnakeEating();
  checkSnakeLife();
  lastMovingTime_ = currTime_;
}

void SnakeModel::spawn() { s_data_.gameStatus = GameState::moving; }

void SnakeModel::setPause() { s_data_.gameStatus = GameState::Pause; }

void SnakeModel::cancelPause() { s_data_.gameStatus = GameState::moving; }

void SnakeModel::exitGame() { s_data_.gameStatus = GameState::exit; }

void SnakeModel::collide() { s_data_.gameStatus = GameState::gameOver; }

void SnakeModel::startGame() { s_data_.gameStatus = GameState::spawn; }

void SnakeModel::gameOver() { s_data_.gameStatus = GameState::exit; }

}  // namespace s21