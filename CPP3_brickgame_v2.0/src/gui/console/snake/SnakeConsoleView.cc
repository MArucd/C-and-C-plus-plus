
#include "SnakeConsoleView.h"

namespace s21 {

SnakeConsoleView::SnakeConsoleView(SnakeController* c)
    : action_(UserAction::noSig), data_(), controller_(c) {}

void SnakeConsoleView::Start() {
  nodelay(stdscr, TRUE);
  controller_->setModelDataDefault();
  data_ = &controller_->getModelData();
  SnakeMainLoop();

  if (data_->gameStatus == GameState::gameOver ||
      data_->gameStatus == GameState::exit) {
    GameResultRendering(data_->isVictory, data_->level, data_->currScore);
  }
}

void SnakeConsoleView::SnakeMainLoop() {
  while (data_->gameStatus != GameState::gameOver &&
         data_->gameStatus != GameState::exit) {
    if (data_->isModified) {
      Rendering();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    action_ = GetAction();
    ModelConnect();
  }
}

void SnakeConsoleView::Rendering() {
  if (data_->gameStatus == GameState::start) {
    StartGameRendering();
  } else if (data_->gameStatus == GameState::Pause) {
    PauseRendering(data_->level, data_->currScore);
  } else {
    GameRendering();
  }
}

void SnakeConsoleView::ModelConnect() {
  controller_->updateModelData(action_);
  data_ = &controller_->getModelData();
  action_ = UserAction::noSig;
}

void SnakeConsoleView::GameRendering() {
  clear();
  // Fruit
  attron(COLOR_PAIR(1));
  mvprintw(data_->fruitCoord.y + 1, data_->fruitCoord.x + 1, "%c", ACS_PI);
  attroff(COLOR_PAIR(1));

  // Snake
  attron(COLOR_PAIR(2));
  for (const auto& i : data_->snakeBodyCoord) {
    mvprintw(i.y + 1, i.x + 1, "%c", 'S');
  }
  attroff(COLOR_PAIR(2));

  GameFieldRendering(Choose::Snake, data_->level, data_->currScore,
                     data_->bestScore);
  refresh();
}

}  // namespace s21