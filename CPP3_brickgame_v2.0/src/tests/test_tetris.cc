#include <gtest/gtest.h>

#include <thread>

#include "../brick_game/tetris/TetrisModel.h"

class TetrisGameTest : public ::testing::Test {
 protected:
  s21::TetrisModel tetrisModel;
  s21::TetrisGameData *tetrisGameData;
};

TEST_F(TetrisGameTest, MoveLeft) {
  tetrisModel.SetGameDataDefault();
  tetrisGameData = &tetrisModel.GetTetrisGameData();
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::start);
  tetrisModel.UpdateModelData(s21::UserAction::spaceBtn);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::spawn);
  tetrisModel.UpdateModelData(s21::UserAction::noSig);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::moving);

  auto tmp_coords = tetrisGameData->tCurr.GetCoords();

  tetrisModel.UpdateModelData(s21::UserAction::left);
  tetrisModel.UpdateModelData(s21::UserAction::left);

  for (size_t i = 0; i < tmp_coords.size(); i++) {
    EXPECT_EQ(tmp_coords[i].x - 2, tetrisGameData->tCurr.GetCoords()[i].x);
  }

  tetrisModel.UpdateModelData(s21::UserAction::escBtn);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::exit);
}

TEST_F(TetrisGameTest, MoveRight) {
  tetrisModel.SetGameDataDefault();
  tetrisGameData = &tetrisModel.GetTetrisGameData();
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::start);
  tetrisModel.UpdateModelData(s21::UserAction::spaceBtn);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::spawn);
  tetrisModel.UpdateModelData(s21::UserAction::noSig);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::moving);

  tetrisModel.UpdateModelData(s21::UserAction::right);
  tetrisModel.UpdateModelData(s21::UserAction::right);
  tetrisModel.UpdateModelData(s21::UserAction::right);

  tetrisModel.UpdateModelData(s21::UserAction::escBtn);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::exit);
}

TEST_F(TetrisGameTest, MoveDown) {
  tetrisModel.SetGameDataDefault();
  tetrisGameData = &tetrisModel.GetTetrisGameData();
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::start);
  tetrisModel.UpdateModelData(s21::UserAction::spaceBtn);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::spawn);
  tetrisModel.UpdateModelData(s21::UserAction::noSig);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::moving);

  tetrisModel.UpdateModelData(s21::UserAction::down);
  tetrisModel.UpdateModelData(s21::UserAction::down);
  tetrisModel.UpdateModelData(s21::UserAction::down);

  tetrisModel.UpdateModelData(s21::UserAction::escBtn);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::exit);
}

TEST_F(TetrisGameTest, Rotate) {
  tetrisModel.SetGameDataDefault();
  tetrisGameData = &tetrisModel.GetTetrisGameData();
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::start);
  tetrisModel.UpdateModelData(s21::UserAction::spaceBtn);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::spawn);
  tetrisModel.UpdateModelData(s21::UserAction::noSig);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::moving);

  tetrisModel.UpdateModelData(s21::UserAction::up);
  tetrisModel.UpdateModelData(s21::UserAction::up);
  tetrisModel.UpdateModelData(s21::UserAction::up);

  tetrisModel.UpdateModelData(s21::UserAction::escBtn);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::exit);
}

TEST_F(TetrisGameTest, Drop) {
  tetrisModel.SetGameDataDefault();
  tetrisGameData = &tetrisModel.GetTetrisGameData();
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::start);
  tetrisModel.UpdateModelData(s21::UserAction::spaceBtn);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::spawn);
  tetrisModel.UpdateModelData(s21::UserAction::noSig);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::moving);

  tetrisModel.UpdateModelData(s21::UserAction::spaceBtn);
  tetrisModel.UpdateModelData(s21::UserAction::spaceBtn);
  tetrisModel.UpdateModelData(s21::UserAction::spaceBtn);

  tetrisModel.UpdateModelData(s21::UserAction::escBtn);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::exit);
}

TEST_F(TetrisGameTest, Collide) {
  tetrisModel.SetGameDataDefault();
  tetrisGameData = &tetrisModel.GetTetrisGameData();
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::start);
  tetrisModel.UpdateModelData(s21::UserAction::spaceBtn);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::spawn);
  tetrisModel.UpdateModelData(s21::UserAction::noSig);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::moving);

  for (int i = 0; i < 20; i++) {
    tetrisModel.UpdateModelData(s21::UserAction::down);
  }

  tetrisModel.UpdateModelData(s21::UserAction::escBtn);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::exit);
}

TEST_F(TetrisGameTest, SetAndCancelPause) {
  tetrisModel.SetGameDataDefault();
  tetrisGameData = &tetrisModel.GetTetrisGameData();
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::start);
  tetrisModel.UpdateModelData(s21::UserAction::spaceBtn);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::spawn);
  tetrisModel.UpdateModelData(s21::UserAction::noSig);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::moving);

  tetrisModel.UpdateModelData(s21::UserAction::tabBtn);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::Pause);

  tetrisModel.UpdateModelData(s21::UserAction::tabBtn);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::moving);

  tetrisModel.UpdateModelData(s21::UserAction::escBtn);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::exit);
}

TEST_F(TetrisGameTest, GameOver) {
  tetrisModel.SetGameDataDefault();
  tetrisGameData = &tetrisModel.GetTetrisGameData();
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::start);
  tetrisModel.UpdateModelData(s21::UserAction::spaceBtn);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::spawn);
  tetrisModel.UpdateModelData(s21::UserAction::noSig);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::moving);

  while (tetrisGameData->tGameStatus != s21::GameState::gameOver) {
    tetrisModel.UpdateModelData(s21::UserAction::spaceBtn);
  }

  tetrisModel.UpdateModelData(s21::UserAction::escBtn);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::exit);
}

TEST_F(TetrisGameTest, AutoMovingDown) {
  tetrisModel.SetGameDataDefault();
  tetrisGameData = &tetrisModel.GetTetrisGameData();
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::start);
  tetrisModel.UpdateModelData(s21::UserAction::spaceBtn);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::spawn);
  tetrisModel.UpdateModelData(s21::UserAction::noSig);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::moving);

  auto tmp_coords = tetrisGameData->tCurr.GetCoords();

  std::this_thread::sleep_for(std::chrono::milliseconds(510));
  tetrisModel.UpdateModelData(s21::UserAction::noSig);

  for (size_t i = 0; i < tmp_coords.size(); i++) {
    EXPECT_EQ(tmp_coords[i].y + 1, tetrisGameData->tCurr.GetCoords()[i].y);
  }

  tetrisModel.UpdateModelData(s21::UserAction::escBtn);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::exit);
}

TEST_F(TetrisGameTest, ClearOneLine) {
  tetrisModel.SetGameDataDefault();
  tetrisGameData = &tetrisModel.GetTetrisGameData();
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::start);
  tetrisModel.UpdateModelData(s21::UserAction::spaceBtn);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::spawn);
  tetrisModel.UpdateModelData(s21::UserAction::noSig);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::moving);

  for (int i = 19; i < 20; ++i) {  // filling 1 lines
    for (int j = 0; j < 10; ++j) {
      tetrisGameData->tField_[i][j].first = true;
    }
  }

  tetrisModel.UpdateModelData(s21::UserAction::spaceBtn);
  EXPECT_EQ(tetrisGameData->tScore, 100);

  tetrisModel.UpdateModelData(s21::UserAction::escBtn);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::exit);
}

TEST_F(TetrisGameTest, ClearTwoLines) {
  tetrisModel.SetGameDataDefault();
  tetrisGameData = &tetrisModel.GetTetrisGameData();
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::start);
  tetrisModel.UpdateModelData(s21::UserAction::spaceBtn);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::spawn);
  tetrisModel.UpdateModelData(s21::UserAction::noSig);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::moving);

  for (int i = 18; i < 20; ++i) {  // filling 2 lines
    for (int j = 0; j < 10; ++j) {
      tetrisGameData->tField_[i][j].first = true;
    }
  }

  tetrisModel.UpdateModelData(s21::UserAction::spaceBtn);
  EXPECT_EQ(tetrisGameData->tScore, 300);

  tetrisModel.UpdateModelData(s21::UserAction::escBtn);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::exit);
}

TEST_F(TetrisGameTest, ClearThreeLines) {
  tetrisModel.SetGameDataDefault();
  tetrisGameData = &tetrisModel.GetTetrisGameData();
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::start);
  tetrisModel.UpdateModelData(s21::UserAction::spaceBtn);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::spawn);
  tetrisModel.UpdateModelData(s21::UserAction::noSig);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::moving);

  for (int i = 17; i < 20; ++i) {  // filling 3 lines
    for (int j = 0; j < 10; ++j) {
      tetrisGameData->tField_[i][j].first = true;
    }
  }

  tetrisModel.UpdateModelData(s21::UserAction::spaceBtn);
  EXPECT_EQ(tetrisGameData->tScore, 700);

  tetrisModel.UpdateModelData(s21::UserAction::escBtn);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::exit);
}

TEST_F(TetrisGameTest, ClearFourLines) {
  tetrisModel.SetGameDataDefault();
  tetrisGameData = &tetrisModel.GetTetrisGameData();
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::start);
  tetrisModel.UpdateModelData(s21::UserAction::spaceBtn);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::spawn);
  tetrisModel.UpdateModelData(s21::UserAction::noSig);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::moving);

  for (int i = 16; i < 20; ++i) {  // filling 4 lines
    for (int j = 0; j < 10; ++j) {
      tetrisGameData->tField_[i][j].first = true;
    }
  }

  tetrisModel.UpdateModelData(s21::UserAction::spaceBtn);
  EXPECT_EQ(tetrisGameData->tScore, 1500);

  tetrisModel.UpdateModelData(s21::UserAction::escBtn);
  EXPECT_EQ(tetrisGameData->tGameStatus, s21::GameState::exit);
}