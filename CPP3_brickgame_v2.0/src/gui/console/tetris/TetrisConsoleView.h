#ifndef BRICKGAME_GUI_TETRIS_VIEW_H_
#define BRICKGAME_GUI_TETRIS_VIEW_H_

#include "../../../controller/TetrisController.h"
#include "../common/BaseView.h"

namespace s21 {

class TetrisConsoleView : public BaseView {
 public:
  explicit TetrisConsoleView(TetrisController *c = nullptr);
  void Start() override;

 private:
  UserAction tAction_;
  TetrisGameData *tData_;
  TetrisController *controller_;
  void TetrisMainLoop();
  void ModelConnect();
  void GameRendering();
  void Rendering();
};
}  // namespace s21

#endif  // BRICKGAME_GUI_TETRIS_VIEW_H_