#ifndef BRICKGAME_MODEL_H_
#define BRICKGAME_MODEL_H_

#include <fstream>
#include <iostream>
#include <random>

#include "../common/BaseModel.h"

namespace s21 {
enum class Direction { up, down, right, left };

struct SnakeGameData {
  Coordinates fruitCoord;
  std::vector<Coordinates> snakeBodyCoord;
  Direction direction;
  bool isVictory;
  GameState gameStatus;
  int currScore;
  int bestScore;
  int level;

  bool isModified;

  SnakeGameData()
      : fruitCoord(),
        snakeBodyCoord(),
        direction(Direction::up),
        isVictory(false),
        gameStatus(GameState::start),
        currScore(0),
        bestScore(0),
        level(1),
        isModified(true) {}

  bool operator==(const SnakeGameData &other) const {
    return currScore == other.currScore && gameStatus == other.gameStatus &&
           fruitCoord == other.fruitCoord &&
           snakeBodyCoord == other.snakeBodyCoord;
  }

  bool operator!=(const SnakeGameData &other) const {
    return !(*this == other);
  }
};  // struct SnakeGameData

class SnakeModel : public BaseModel {
 public:
  SnakeModel();
  ~SnakeModel();

  void updateData(UserAction action);

  void setGameDataDefault();
  SnakeGameData &getModelData();

  using Action = void (SnakeModel::*)();

  const Action snakeActionTable[7][9] = {
      // Start
      {nullptr, nullptr, nullptr, nullptr, nullptr, &SnakeModel::startGame,
       &SnakeModel::startGame, &SnakeModel::exitGame, nullptr},
      // Spawn
      {&SnakeModel::spawn, &SnakeModel::spawn, &SnakeModel::spawn,
       &SnakeModel::spawn, &SnakeModel::spawn, &SnakeModel::spawn,
       &SnakeModel::spawn, &SnakeModel::spawn, &SnakeModel::spawn},
      // Move
      {nullptr, &SnakeModel::moveHeadLeft, &SnakeModel::moveHeadRight,
       &SnakeModel::moveHeadDown, &SnakeModel::moveHeadUp,
       &SnakeModel::setPause, nullptr, &SnakeModel::exitGame,
       &SnakeModel::setPause},
      // Collide
      {&SnakeModel::collide, &SnakeModel::collide, &SnakeModel::collide,
       &SnakeModel::collide, &SnakeModel::collide, &SnakeModel::collide,
       &SnakeModel::collide, &SnakeModel::collide, &SnakeModel::collide},
      // Pause
      {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
       &SnakeModel::cancelPause, &SnakeModel::exitGame,
       &SnakeModel::cancelPause},
      // Exit
      {&SnakeModel::exitGame, &SnakeModel::exitGame, &SnakeModel::exitGame,
       &SnakeModel::exitGame, &SnakeModel::exitGame, &SnakeModel::exitGame,
       &SnakeModel::exitGame, &SnakeModel::exitGame, &SnakeModel::exitGame},
      // GameOver
      {&SnakeModel::gameOver, &SnakeModel::gameOver, &SnakeModel::gameOver,
       &SnakeModel::gameOver, &SnakeModel::gameOver, &SnakeModel::gameOver,
       &SnakeModel::gameOver, &SnakeModel::gameOver, &SnakeModel::gameOver}};

 private:
  SnakeGameData s_data_;
  long long lastMovingTime_{};
  long long currTime_{};
  long long currDelay{};

  void updateFruitPos();
  void moveSnake();
  void checkSnakeLife();
  void checkSnakeEating();

  void moveHeadLeft();
  void moveHeadRight();
  void moveHeadDown();
  void moveHeadUp();
  void spawn();
  void setPause();
  void cancelPause();
  void exitGame();
  void collide();
  void startGame();
  void gameOver();
  void moveSnakeBody();

};  // class SnakeModel
}  // namespace s21

#endif  // BRICKGAME_MODEL_H_