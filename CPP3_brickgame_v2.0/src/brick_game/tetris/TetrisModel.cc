#include "TetrisModel.h"

namespace s21 {

TetrisModel::TetrisModel() {
  tData.tField_.resize(
      GameSizes::fieldHeight,
      std::vector<std::pair<bool, int>>(GameSizes::fieldWidth, {false, 0}));
  SetGameDataDefault();
  tData.tBestScore = LoadScore("TetrisScore.txt");
}

TetrisModel::~TetrisModel() {
  SaveScore(tData.tBestScore, "TetrisScore.txt");
  tData.tField_.clear();
}

void TetrisModel::SetGameDataDefault() {
  tData.tScore = 0;
  tData.tLevel = 1;
  tData.tGameStatus = GameState::start;
  tData.tCurr.SetRandomShape();
  tData.tNext.SetRandomShape();
  tData.tProjection = tData.tCurr;
  InitializeBoard();
  SetProjection();
  last_moving_time_ = GetCurrentTime();
  curr_delay_ = GameSizes::IntervalMs[0];
}

void TetrisModel::UpdateModelData(UserAction act) {
  tData.isModified = false;
  TetrisGameData data_cast = tData;

  long long curr_time = last_moving_time_;
  if (tData.tGameStatus != GameState::Pause) {
    curr_time = GetCurrentTime();
  }

  Action func = kTetrisActionTable[static_cast<int>(tData.tGameStatus)]
                                  [static_cast<int>(act)];
  if (func) {
    (this->*func)();
  }

  if (tData.tGameStatus == GameState::moving) {
    if (curr_time - last_moving_time_ > curr_delay_) {
      last_moving_time_ = curr_time;
      if (CheckCollide()) UpdateBoard();
      MoveTetrominoDown();
    }
    UpdateLevel();
  }

  if (tData != data_cast) {
    tData.isModified = true;
  }
}

void TetrisModel::PlacePiece() {
  for (const auto& coord : tData.tCurr.GetCoords()) {
    int x = coord.x;
    int y = coord.y;
    tData.tField_[y - 1][x].first = true;
    tData.tField_[y - 1][x].second = static_cast<int>(tData.tCurr.GetShape());
  }
}

void TetrisModel::InitializeBoard() {
  tData.tField_.resize(
      GameSizes::fieldHeight,
      std::vector<std::pair<bool, int>>(GameSizes::fieldWidth, {false, 0}));
  for (int i = 0; i < GameSizes::fieldHeight; ++i) {
    for (int j = 0; j < GameSizes::fieldWidth; ++j) {
      tData.tField_[i][j].first = false;
      tData.tField_[i][j].second = static_cast<int>(TetroShape::NoShape);
    }
  }
}

int TetrisModel::ClearLines() {
  int count_lines = 0;

  for (int i = 0; i < GameSizes::fieldHeight; ++i) {
    bool lineFilled = true;
    for (int j = 0; j < GameSizes::fieldWidth; ++j) {
      if (!tData.tField_[i][j].first) {
        lineFilled = false;
        break;
      }
    }
    if (lineFilled) {
      tData.tField_.erase(tData.tField_.begin() + i);
      tData.tField_.insert(
          tData.tField_.begin(),
          std::vector<std::pair<bool, int>>(GameSizes::fieldWidth, {false, 0}));
      count_lines++;
    }
  }
  return count_lines;
}

void TetrisModel::SetProjection() {
  tData.tProjection = tData.tCurr;
  while (TryToMove(tData.tProjection, UserAction::down)) {
    tData.tProjection.MoveDown();
  }
}

bool TetrisModel::TryToMove(Tetromino& t, UserAction dir) {
  bool can_move = true;
  for (const auto& coord : t.GetCoords()) {
    switch (dir) {
      case UserAction::down:
        if (coord.y == GameSizes::fieldHeight ||
            tData.tField_[coord.y][coord.x].first) {
          can_move = false;
        }
        break;
      case UserAction::left:
        if (coord.x < 1 || tData.tField_[coord.y - 1][coord.x - 1].first) {
          can_move = false;
        }
        break;
      case UserAction::right:
        if (coord.x == GameSizes::fieldWidth - 1 ||
            tData.tField_[coord.y - 1][coord.x + 1].first) {
          can_move = false;
        }
        break;
      default:
        break;
    }
    if (!can_move) break;
  }
  return can_move;
}

void TetrisModel::UpdatePlayerResults(int completed_lines) {
  if (completed_lines == 1) {
    tData.tScore += 100;
  } else if (completed_lines == 2) {
    tData.tScore += 300;
  } else if (completed_lines == 3) {
    tData.tScore += 700;
  } else if (completed_lines == 4) {
    tData.tScore += 1500;
  }
  tData.tBestScore = std::max(tData.tBestScore, tData.tScore);
  UpdateLevel();
}

void TetrisModel::UpdateBoard() {
  PlacePiece();
  int completed_lines = ClearLines();
  UpdatePlayerResults(completed_lines);
  SpawnNewTetromino();
}

void TetrisModel::UpdateLevel() {
  if (tData.tLevel < 10 && tData.tScore > 600) {
    tData.tLevel = tData.tScore / 600;
  }
  curr_delay_ = GameSizes::IntervalMs[tData.tLevel - 1];
}

void TetrisModel::MoveTetrominoLeft() {
  if (TryToMove(tData.tCurr, UserAction::left)) {
    tData.tCurr.MoveLeft();
    SetProjection();
  }
}

void TetrisModel::MoveTetrominoRight() {
  if (TryToMove(tData.tCurr, UserAction::right)) {
    tData.tCurr.MoveRight();
    SetProjection();
  }
}

void TetrisModel::MoveTetrominoDown() {
  if (TryToMove(tData.tCurr, UserAction::down)) {
    tData.tCurr.MoveDown();
    SetProjection();
  }
}

void TetrisModel::DropTetromino() {
  tData.tCurr = tData.tProjection;
  UpdateBoard();
}

void TetrisModel::RotateTetromino() {
  auto tmp_tetromino = tData.tCurr;
  tData.tCurr.Rotate();
  bool can_rotate = true;
  for (const auto& coord : tData.tCurr.GetCoords()) {
    if (tData.tField_[coord.y - 1][coord.x].first) {
      can_rotate = false;
      break;
    }
  }
  if (!can_rotate) {
    tData.tCurr = tmp_tetromino;
  }
  SetProjection();
}

void TetrisModel::SpawnNewTetromino() {
  tData.tGameStatus = GameState::moving;
  tData.tCurr = tData.tNext;
  tData.tNext.SetRandomShape();
  tData.tProjection = tData.tCurr;
  SetProjection();
  if (CheckCollide()) tData.tGameStatus = GameState::gameOver;
}

void TetrisModel::SetPause() { tData.tGameStatus = GameState::Pause; }

void TetrisModel::CancelPause() { tData.tGameStatus = GameState::moving; }

void TetrisModel::ExitGame() { tData.tGameStatus = GameState::exit; }

void TetrisModel::Collide() {
  tData.tGameStatus = GameState::spawn;
  UpdateBoard();
}

void TetrisModel::StartGame() {
  SetGameDataDefault();
  tData.tGameStatus = GameState::spawn;
}

void TetrisModel::GameOver() { tData.tGameStatus = GameState::exit; }

bool TetrisModel::CheckCollide() {
  bool is_collide = false;
  for (const auto& coord : tData.tCurr.GetCoords()) {
    if (coord.y == GameSizes::fieldHeight) {  // down board
      is_collide = true;
      break;
    }
    if (tData.tField_[coord.y][coord.x].first) {  // other tetrominos
      is_collide = true;
      break;
    }
  }
  return is_collide;
}

}  // namespace s21
