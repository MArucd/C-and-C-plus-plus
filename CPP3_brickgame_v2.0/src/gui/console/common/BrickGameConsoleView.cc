#include "BrickGameConsoleView.h"

namespace s21 {

BrickGameConsoleView::BrickGameConsoleView(SnakeController* s_c,
                                           TetrisController* t_c)
    : snakeView_(s_c), tetrisView_(t_c) {}

void BrickGameConsoleView::Start() {
  setlocale(LC_ALL, "");
  InitNcurses();
  MainLoop();
}

void BrickGameConsoleView::InitNcurses() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  curs_set(0);

  start_color();
  InitColors();
}

void BrickGameConsoleView::MainLoop() {
  Choose ch = InitMenu();

  while (ch != Choose::Exit) {
    if (ch == Choose::Snake) {
      snakeView_.Start();
    } else if (ch == Choose::Tetris) {
      tetrisView_.Start();
    }
    ch = InitMenu();
  }

  curs_set(1);
  endwin();
}

void BrickGameConsoleView::InitColors() {
  init_color((short)ColorIndex::Red, 1000, 0, 0);
  init_color((short)ColorIndex::Green, 0, 1000, 0);
  init_color((short)ColorIndex::Cyan, 0, 1000, 1000);
  init_color((short)ColorIndex::Purple, 1000, 0, 1000);
  init_color((short)ColorIndex::Yellow, 1000, 1000, 0);
  init_color((short)ColorIndex::Orange, 1000, 500, 0);
  init_color((short)ColorIndex::Blue, 0, 0, 1000);
  init_color((short)ColorIndex::Gray, 500, 500, 500);

  init_pair(1, (short)ColorIndex::Red, (short)ColorIndex::Red);  // Красный
  init_pair(2, (short)ColorIndex::Green,
            (short)ColorIndex::Green);  // Зеленый
  init_pair(3, (short)ColorIndex::Cyan, (short)ColorIndex::Cyan);  // Голубой
  init_pair(4, (short)ColorIndex::Purple,
            (short)ColorIndex::Purple);  // Фиолетовый
  init_pair(5, (short)ColorIndex::Yellow,
            (short)ColorIndex::Yellow);  // Желтый
  init_pair(6, (short)ColorIndex::Orange,
            (short)ColorIndex::Orange);  // Оранжевый
  init_pair(7, (short)ColorIndex::Blue, (short)ColorIndex::Blue);  // Синий
  init_pair(8, (short)ColorIndex::Gray, (short)ColorIndex::Gray);  // Серый
}

}  // namespace s21
