
#include "View.h"

#include "ui_View.h"

namespace s21 {

View::View(SnakeController *s_c, TetrisController *t_c, QWidget *parent)
    : QMainWindow(parent),
      ui_(new Ui::View),
      current_game_(CurrentGame::kNone),
      action_(UserAction::noSig),
      s_data_(nullptr),
      t_data_(nullptr),
      snake_controller_(s_c),
      tetris_controller_(t_c) {
  ui_->setupUi(this);
  move(1000, 300);
  setWindowTitle("Snake Game");
  ui_->stackedWidget->setCurrentIndex(1);
  tetris_controller_->SetModelDataDefault();
  t_data_ = &tetris_controller_->GetModelData();
  snake_controller_->setModelDataDefault();
  s_data_ = &snake_controller_->getModelData();
  m_timer_ = new QTimer(this);
  connect(m_timer_, &QTimer::timeout, this, &View::UpdateAll);
}

View::~View() {
  if (m_timer_ != nullptr) delete m_timer_;
  delete ui_;
}

void View::keyPressEvent(QKeyEvent *event) {
  int key = event->key();
  switch (key) {
    case Qt::Key_Left:
      action_ = UserAction::left;
      break;
    case Qt::Key_Right:
      action_ = UserAction::right;
      break;
    case Qt::Key_Up:
      action_ = UserAction::up;
      break;
    case Qt::Key_Down:
      action_ = UserAction::down;
      break;
    case Qt::Key_Enter:
      action_ = UserAction::enterBtn;
      break;
    case Qt::Key_Tab:
      action_ = UserAction::tabBtn;
      break;
    case Qt::Key_Space:
      action_ = UserAction::spaceBtn;
      break;
    case Qt::Key_Escape:
      action_ = UserAction::escBtn;
      break;
    default:
      break;
  }
}

void View::paintEvent(QPaintEvent *event) {
  QWidget::paintEvent(event);
  if (current_game_ == CurrentGame::kSnake) {
    if (s_data_->gameStatus != GameState::gameOver &&
        s_data_->gameStatus != GameState::exit) {
      if (s_data_->gameStatus == GameState::start) {
        StartWindowRendering(ui_->SnakeInfoLabel);
      } else if (s_data_->gameStatus == GameState::Pause) {
        PauseWindowRendering(ui_->SnakeInfoLabel);
      } else {
        ui_->SnakeInfoLabel->setText("");
        SnakeGameRendering();
      }
    } else {
      ClearField();
      GameOver(s_data_->isVictory, s_data_->level, s_data_->currScore);
    }
  } else if (current_game_ == CurrentGame::kTetris) {
    if (t_data_->tGameStatus != GameState::gameOver &&
        t_data_->tGameStatus != GameState::exit) {
      if (t_data_->tGameStatus == GameState::start) {
        StartWindowRendering(ui_->TetrisInfoLabel);
      } else if (t_data_->tGameStatus == GameState::Pause) {
        PauseWindowRendering(ui_->TetrisInfoLabel);
      } else {
        ui_->TetrisInfoLabel->setText("");
        TetrisGameRendering();
      }
    } else {
      ClearField();
      GameOver(false, t_data_->tLevel, t_data_->tScore);
    }
  }
}

void View::ClearField() {
  QPainter painter(this);
  painter.eraseRect(rect());
  painter.end();
}

void View::GameOver(bool is_victory, int level, int score) {
  m_timer_->stop();
  ui_->stackedWidget->setCurrentIndex(0);
  if (is_victory) {
    ui_->GameStatus->setText("YOU WON!!!");
  } else {
    ui_->GameStatus->setText("GAME OVER!");
  }
  ui_->MenuCurrScore->setText(QString::number(score));
  ui_->MenuBestScore->setText(QString::number(level));
}

void View::UpdateAll() {
  if (current_game_ == CurrentGame::kSnake) {
    UpdateSnakeModel();
  } else if (current_game_ == CurrentGame::kTetris) {
    UpdateTetrisModel();
  }
  repaint();
}

void View::on_playAgain_clicked() {
  if (current_game_ == CurrentGame::kTetris) {
    tetris_controller_->SetModelDataDefault();
    t_data_ = &tetris_controller_->GetModelData();
    ui_->stackedWidget->setCurrentIndex(3);
    m_timer_->start(10);
  } else if (current_game_ == CurrentGame::kSnake) {
    snake_controller_->setModelDataDefault();
    s_data_ = &snake_controller_->getModelData();
    ui_->stackedWidget->setCurrentIndex(2);
    m_timer_->start(10);
  } else if (current_game_ == CurrentGame::kNone) {
    ui_->stackedWidget->setCurrentIndex(1);
  }
}

void View::on_start_snake_btn_clicked() {
  current_game_ = CurrentGame::kSnake;
  snake_controller_->setModelDataDefault();
  s_data_ = &snake_controller_->getModelData();
  ui_->stackedWidget->setCurrentIndex(2);
  m_timer_->start(10);
}

void View::on_start_tetris_btn_clicked() {
  current_game_ = CurrentGame::kTetris;
  tetris_controller_->SetModelDataDefault();
  t_data_ = &tetris_controller_->GetModelData();
  ui_->stackedWidget->setCurrentIndex(3);
  m_timer_->start(10);
}

void View::on_exit_btn_clicked() { close(); }

void View::on_closeGame_clicked() {
  current_game_ = CurrentGame::kNone;
  ui_->stackedWidget->setCurrentIndex(1);
}

void View::UpdateSnakeModel() {
  snake_controller_->updateModelData(action_);
  s_data_ = &snake_controller_->getModelData();
  action_ = UserAction::noSig;
  ui_->CurrScore->setText(QString::number(s_data_->currScore));
  ui_->CurrLevel->setText(QString::number(s_data_->level));
  ui_->BestScore->setText(QString::number(s_data_->bestScore));
  if (s_data_->gameStatus == GameState::gameOver ||
      s_data_->gameStatus == GameState::exit) {
    m_timer_->stop();
  }
}

void View::UpdateTetrisModel() {
  tetris_controller_->updateModelData(action_);
  t_data_ = &tetris_controller_->GetModelData();
  action_ = UserAction::noSig;
  ui_->tetris_curr_score->setText(QString::number(t_data_->tScore));
  ui_->tetris_curr_level->setText(QString::number(t_data_->tLevel));
  ui_->tetris_best_score->setText(QString::number(t_data_->tBestScore));
  if (t_data_->tGameStatus == GameState::gameOver ||
      t_data_->tGameStatus == GameState::exit) {
    m_timer_->stop();
  }
}

void View::SnakeGameRendering() {
  QPainter qp(this);
  QImage pear("images/pear.png");

  QRectF pearRect(s_data_->fruitCoord.x * GameSizes::kDotSize,
                  s_data_->fruitCoord.y * GameSizes::kDotSize,
                  GameSizes::kDotSize, GameSizes::kDotSize);
  QImage head("images/snakeHEAD.png");

  QRectF head_rect(s_data_->snakeBodyCoord[0].x * GameSizes::kDotSize,
                   s_data_->snakeBodyCoord[0].y * GameSizes::kDotSize,
                   GameSizes::kDotSize, GameSizes::kDotSize);

  QTransform transform;
  int rot = 0;
  if (s_data_->direction == Direction::down) {
    rot = 180;
  } else if (s_data_->direction != Direction::up) {
    rot = (s_data_->direction == Direction::left ? -90 : 90);
  }
  head = head.transformed(transform.rotate(rot));

  qp.drawImage(pearRect, pear);

  for (std::size_t i = 0; i < s_data_->snakeBodyCoord.size(); ++i) {
    qp.setBrush(QColor(148, 195, 76));
    qp.setPen(QColor(148, 195, 76));
    if (i == 0) {
      qp.drawImage(head_rect, head);
    } else {
      qp.drawRect(s_data_->snakeBodyCoord[i].x * GameSizes::kDotSize,
                  s_data_->snakeBodyCoord[i].y * GameSizes::kDotSize,
                  GameSizes::kDotSize - 1, GameSizes::kDotSize - 1);
    }
  }
  qp.end();
}

void View::TetrisGameRendering() {
  QPainter qp(this);

  qp.setBrush(QColor(90, 90, 90));
  qp.setPen(QColor(0, 0, 0));

  qp.setBrush(kColors[0]);
  for (const auto &item : t_data_->tProjection.GetCoords()) {
    qp.drawRect((item.x) * GameSizes::kDotSize,
                (item.y - 1) * GameSizes::kDotSize, GameSizes::kDotSize - 1,
                GameSizes::kDotSize - 1);
  }

  qp.setBrush(QColor(148, 195, 76));

  for (const auto &item : t_data_->tCurr.GetCoords()) {
    qp.setBrush(kColors[(int)t_data_->tCurr.GetShape()]);
    qp.drawRect(item.x * GameSizes::kDotSize,
                (item.y - 1) * GameSizes::kDotSize, GameSizes::kDotSize - 1,
                GameSizes::kDotSize - 1);
  }

  // next tetromino
  for (const auto &item : t_data_->tNext.GetCoords()) {
    qp.setBrush(kColors[(int)t_data_->tNext.GetShape()]);
    qp.drawRect((item.x + 8) * GameSizes::kDotSize,
                (item.y + 2) * GameSizes::kDotSize, GameSizes::kDotSize - 1,
                GameSizes::kDotSize - 1);
  }

  // board
  for (int i = 0; i < GameSizes::fieldHeight; ++i) {
    for (int j = 0; j < GameSizes::fieldWidth; ++j) {
      if (t_data_->tField_[i][j].first) {
        qp.setBrush(kColors[(int)t_data_->tField_[i][j].second]);
        qp.drawRect(j * GameSizes::kDotSize, i * GameSizes::kDotSize,
                    GameSizes::kDotSize - 1, GameSizes::kDotSize - 1);
      }
    }
  }
  qp.end();
}

void View::StartWindowRendering(QLabel *p_label) {
  p_label->setText("Press space to start");
  p_label->setStyleSheet("border: none;");
}

void View::PauseWindowRendering(QLabel *p_label) {
  p_label->setText(
      "Game on pause.<br> Press Tab to continue<br> or Esc to exit");
}

}  // namespace s21