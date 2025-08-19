#ifndef BRICKGAME_TETRIS_TETRISMODEL_H_
#define BRICKGAME_TETRIS_TETRISMODEL_H_

#include "../common/BaseModel.h"
#include "Tetromino.h"

namespace s21 {

struct TetrisGameData {
  bool isModified;
  int tScore;
  int tBestScore;
  int tLevel;
  GameState tGameStatus;
  Tetromino tCurr;
  Tetromino tProjection;
  Tetromino tNext;
  std::vector<std::vector<std::pair<bool, int>>> tField_;

  TetrisGameData()
      : isModified(true),
        tScore(0),
        tBestScore(0),
        tLevel(1),
        tGameStatus(GameState::start),
        tCurr(),
        tProjection(),
        tNext(),
        tField_() {}
  bool operator==(const TetrisGameData& other) const {
    return tScore == other.tScore && tBestScore == other.tBestScore &&
           tLevel == other.tLevel && tGameStatus == other.tGameStatus &&
           tCurr == other.tCurr && tField_ == other.tField_;
  }
  bool operator!=(const TetrisGameData& other) const {
    return !(*this == other);
  }
};

class TetrisModel : public BaseModel {
 public:
  TetrisModel();
  ~TetrisModel();

  TetrisGameData& GetTetrisGameData() { return tData; }
  void SetGameDataDefault();
  void UpdateModelData(UserAction act = UserAction::noSig);

  using Action = void (TetrisModel::*)();

  const Action kTetrisActionTable[7][9] = {
      // kStart
      {nullptr, nullptr, nullptr, nullptr, nullptr, &TetrisModel::StartGame,
       &TetrisModel::StartGame, &TetrisModel::ExitGame, nullptr},
      // kSpawn
      {&TetrisModel::SpawnNewTetromino, &TetrisModel::SpawnNewTetromino,
       &TetrisModel::SpawnNewTetromino, &TetrisModel::SpawnNewTetromino,
       &TetrisModel::SpawnNewTetromino, &TetrisModel::SpawnNewTetromino,
       &TetrisModel::SpawnNewTetromino, &TetrisModel::SpawnNewTetromino,
       &TetrisModel::SpawnNewTetromino},
      // kMoving,
      {nullptr, &TetrisModel::MoveTetrominoLeft,
       &TetrisModel::MoveTetrominoRight, &TetrisModel::MoveTetrominoDown,
       &TetrisModel::RotateTetromino, &TetrisModel::DropTetromino,
       &TetrisModel::DropTetromino, &TetrisModel::ExitGame,
       &TetrisModel::SetPause},
      //        kCollide,
      {&TetrisModel::Collide, &TetrisModel::Collide, &TetrisModel::Collide,
       &TetrisModel::Collide, &TetrisModel::Collide, &TetrisModel::Collide,
       &TetrisModel::Collide, &TetrisModel::Collide, &TetrisModel::Collide},
      //        kPause,
      {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
       &TetrisModel::CancelPause, &TetrisModel::ExitGame,
       &TetrisModel::CancelPause},
      //        kExit,
      {&TetrisModel::ExitGame, &TetrisModel::ExitGame, &TetrisModel::ExitGame,
       &TetrisModel::ExitGame, &TetrisModel::ExitGame, &TetrisModel::ExitGame,
       &TetrisModel::ExitGame, &TetrisModel::ExitGame, &TetrisModel::ExitGame},
      //        kGameOver
      {&TetrisModel::GameOver, &TetrisModel::GameOver, &TetrisModel::GameOver,
       &TetrisModel::GameOver, &TetrisModel::GameOver, &TetrisModel::GameOver,
       &TetrisModel::GameOver, &TetrisModel::GameOver, &TetrisModel::GameOver}};

 private:
  TetrisGameData tData;
  long long last_moving_time_{};
  long long curr_delay_{};

  bool CheckCollide();
  void UpdateBoard();
  void UpdatePlayerResults(int completed_lines);
  void InitializeBoard();
  void PlacePiece();
  int ClearLines();
  void SetProjection();
  void UpdateLevel();
  bool TryToMove(Tetromino& t, UserAction direction);

  // FSM ACTION METHODS
  void MoveTetrominoLeft();
  void MoveTetrominoRight();
  void MoveTetrominoDown();
  void DropTetromino();
  void RotateTetromino();
  void SpawnNewTetromino();
  void SetPause();
  void CancelPause();
  void ExitGame();
  void Collide();
  void StartGame();
  void GameOver();
};

}  // namespace s21
#endif  // BRICKGAME_TETRIS_TETRISMODEL_H_