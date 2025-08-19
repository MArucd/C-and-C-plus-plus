#ifndef BRICKGAME_CONTROLLER_H
#define BRICKGAME_CONTROLLER_H

#include "SnakeModel.h"

namespace s21 {

class SnakeController {
 public:
  SnakeController(SnakeModel *model) : model_(model) {}
  ~SnakeController() = default;

  void updateModelData(UserAction action = UserAction::up) {
    model_->updateData(action);
  }

  void setModelDataDefault() { model_->setGameDataDefault(); }

  SnakeGameData &getModelData() { return model_->getModelData(); }

 private:
  SnakeModel *model_;

};  // SnakeController

}  // namespace s21

#endif  // BRICKGAME_CONTROLLER_H