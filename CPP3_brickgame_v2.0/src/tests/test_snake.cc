#include <gtest/gtest.h>

#include <thread>

#include "../brick_game/snake/SnakeModel.h"

class SnakeGameTest : public ::testing::Test {
 protected:
  s21::SnakeModel snakeModel;
  s21::SnakeGameData *snakeGameData;
};

TEST_F(SnakeGameTest, MoveSnakeUp) {
  snakeModel.setGameDataDefault();
  s21::SnakeGameData *snakeGameData = &snakeModel.getModelData();
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::start);
  snakeModel.updateData(s21::UserAction::spaceBtn);
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::spawn);
  snakeModel.updateData(s21::UserAction::noSig);
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::moving);
  snakeModel.updateData(s21::UserAction::up);
  EXPECT_EQ(snakeGameData->direction, s21::Direction::up);
  snakeModel.updateData(s21::UserAction::escBtn);
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::exit);
}

TEST_F(SnakeGameTest, MoveSnakeLeft) {
  snakeModel.setGameDataDefault();
  s21::SnakeGameData *snakeGameData = &snakeModel.getModelData();
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::start);
  snakeModel.updateData(s21::UserAction::spaceBtn);
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::spawn);
  snakeModel.updateData(s21::UserAction::noSig);
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::moving);
  snakeModel.updateData(s21::UserAction::left);
  EXPECT_EQ(snakeGameData->direction, s21::Direction::left);
  snakeModel.updateData(s21::UserAction::escBtn);
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::exit);
}

TEST_F(SnakeGameTest, MoveSnakeRight) {
  snakeModel.setGameDataDefault();
  s21::SnakeGameData *snakeGameData = &snakeModel.getModelData();
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::start);
  snakeModel.updateData(s21::UserAction::spaceBtn);
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::spawn);
  snakeModel.updateData(s21::UserAction::noSig);
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::moving);
  snakeModel.updateData(s21::UserAction::right);
  EXPECT_EQ(snakeGameData->direction, s21::Direction::right);
  snakeModel.updateData(s21::UserAction::escBtn);
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::exit);
}

TEST_F(SnakeGameTest, MoveSnakeAround) {
  snakeModel.setGameDataDefault();
  s21::SnakeGameData *snakeGameData = &snakeModel.getModelData();
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::start);
  snakeModel.updateData(s21::UserAction::spaceBtn);
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::spawn);
  snakeModel.updateData(s21::UserAction::noSig);
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::moving);
  snakeModel.updateData(s21::UserAction::right);
  EXPECT_EQ(snakeGameData->direction, s21::Direction::right);
  snakeModel.updateData(s21::UserAction::down);
  EXPECT_EQ(snakeGameData->direction, s21::Direction::down);
  snakeModel.updateData(s21::UserAction::left);
  EXPECT_EQ(snakeGameData->direction, s21::Direction::left);
  snakeModel.updateData(s21::UserAction::up);
  EXPECT_EQ(snakeGameData->direction, s21::Direction::up);
  snakeModel.updateData(s21::UserAction::escBtn);
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::exit);
}

TEST_F(SnakeGameTest, AutoMovingUp) {
  snakeModel.setGameDataDefault();
  s21::SnakeGameData *snakeGameData = &snakeModel.getModelData();
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::start);
  snakeModel.updateData(s21::UserAction::spaceBtn);
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::spawn);
  snakeModel.updateData(s21::UserAction::noSig);
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::moving);
  snakeModel.updateData(s21::UserAction::noSig);
  std::this_thread::sleep_for(std::chrono::milliseconds(510));
  snakeModel.updateData(s21::UserAction::noSig);
  snakeModel.updateData(s21::UserAction::escBtn);
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::exit);
}

TEST_F(SnakeGameTest, AutoMovingLeft) {
  snakeModel.setGameDataDefault();
  s21::SnakeGameData *snakeGameData = &snakeModel.getModelData();
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::start);
  snakeModel.updateData(s21::UserAction::spaceBtn);
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::spawn);
  snakeModel.updateData(s21::UserAction::noSig);
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::moving);
  snakeModel.updateData(s21::UserAction::left);
  std::this_thread::sleep_for(std::chrono::milliseconds(510));
  snakeModel.updateData(s21::UserAction::noSig);
  snakeModel.updateData(s21::UserAction::escBtn);
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::exit);
}

TEST_F(SnakeGameTest, AutoMovingRight) {
  snakeModel.setGameDataDefault();
  s21::SnakeGameData *snakeGameData = &snakeModel.getModelData();
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::start);
  snakeModel.updateData(s21::UserAction::spaceBtn);
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::spawn);
  snakeModel.updateData(s21::UserAction::noSig);
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::moving);
  snakeModel.updateData(s21::UserAction::right);
  std::this_thread::sleep_for(std::chrono::milliseconds(510));
  snakeModel.updateData(s21::UserAction::noSig);
  snakeModel.updateData(s21::UserAction::escBtn);
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::exit);
}

TEST_F(SnakeGameTest, AutoMovingDown) {
  snakeModel.setGameDataDefault();
  s21::SnakeGameData *snakeGameData = &snakeModel.getModelData();
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::start);
  snakeModel.updateData(s21::UserAction::spaceBtn);
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::spawn);
  snakeModel.updateData(s21::UserAction::noSig);
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::moving);
  snakeModel.updateData(s21::UserAction::right);
  snakeModel.updateData(s21::UserAction::down);
  std::this_thread::sleep_for(std::chrono::milliseconds(510));
  snakeModel.updateData(s21::UserAction::noSig);
  snakeModel.updateData(s21::UserAction::escBtn);
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::exit);
}

TEST_F(SnakeGameTest, SetAndCancelPause) {
  snakeModel.setGameDataDefault();
  s21::SnakeGameData *snakeGameData = &snakeModel.getModelData();
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::start);
  snakeModel.updateData(s21::UserAction::spaceBtn);
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::spawn);
  snakeModel.updateData(s21::UserAction::noSig);
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::moving);
  snakeModel.updateData(s21::UserAction::tabBtn);
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::Pause);
  snakeModel.updateData(s21::UserAction::tabBtn);
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::moving);
  snakeModel.updateData(s21::UserAction::escBtn);
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::exit);
}

TEST_F(SnakeGameTest, GameOver) {
  snakeModel.setGameDataDefault();
  s21::SnakeGameData *snakeGameData = &snakeModel.getModelData();
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::start);
  snakeModel.updateData(s21::UserAction::spaceBtn);
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::spawn);
  snakeModel.updateData(s21::UserAction::noSig);
  EXPECT_EQ(snakeGameData->gameStatus, s21::GameState::moving);
  while (snakeGameData->gameStatus != s21::GameState::gameOver) {
    snakeModel.updateData(s21::UserAction::up);
  }
}
