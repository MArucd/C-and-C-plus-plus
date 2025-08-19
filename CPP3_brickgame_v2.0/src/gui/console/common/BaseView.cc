#include "BaseView.h"

namespace s21 {
void BaseView::GameFieldRendering(Choose currGame, int level, int score,
                                  int record) {
  DrawBox(0, 0, GameSizes::windowHeight, GameSizes::windowWidth);

  DrawBox(0, 0, GameSizes::fieldHeight + 1, GameSizes::fieldWidth + 1);

  mvaddch(0, GameSizes::fieldWidth + 1, ACS_TTEE);

  mvaddch(GameSizes::fieldHeight + 1, GameSizes::fieldWidth + 1, ACS_BTEE);

  int sidePanelHeight = 1;
  if (currGame == Choose::Tetris) {
    sidePanelHeight = GameSizes::sidePanelHeight;

    DrawBox(1, GameSizes::fieldWidth + 2, sidePanelHeight,
            GameSizes::windowWidth - 1);

    mvprintw(1, GameSizes::fieldWidth + 3, "Next");
    sidePanelHeight += 1;
  }

  DrawBox(sidePanelHeight, GameSizes::fieldWidth + 2, sidePanelHeight + 2,
          GameSizes::windowWidth - 1);

  mvprintw(sidePanelHeight, GameSizes::fieldWidth + 3, "Level");
  mvprintw(sidePanelHeight + 1, GameSizes::fieldWidth + 8, "%d", level);
  sidePanelHeight += 3;

  DrawBox(sidePanelHeight, GameSizes::fieldWidth + 2, sidePanelHeight + 2,
          GameSizes::windowWidth - 1);
  mvprintw(sidePanelHeight, GameSizes::fieldWidth + 3, "Score");
  mvprintw(sidePanelHeight + 1,
           GameSizes::fieldWidth + 9 -
               static_cast<int>(std::to_string(score).length()),
           "%d", score);
  sidePanelHeight += 3;

  DrawBox(sidePanelHeight, GameSizes::fieldWidth + 2, sidePanelHeight + 2,
          GameSizes::windowWidth - 1);

  mvprintw(sidePanelHeight, GameSizes::fieldWidth + 3, "Record");
  mvprintw(sidePanelHeight + 1,
           GameSizes::fieldWidth + 9 -
               static_cast<int>(std::to_string(record).length()),
           "%d", record);
}

void BaseView::GameResultRendering(bool isVictory, int level, int score) {
  clear();
  DrawBox(0, 0, GameSizes::windowHeight, GameSizes::windowWidth);
  if (isVictory) {
    mvprintw(2, GameSizes::windowWidth / 2 - 4, "YOU WIN! CONGRET!");
  } else {
    mvprintw(2, GameSizes::windowWidth / 2 - 5, "GAME OVER!");
  }
  mvprintw(4, GameSizes::windowWidth / 2 - 7, "Your score: %d", score);
  mvprintw(6, GameSizes::windowWidth / 2 - 7, "Your level: %d", level);
  mvprintw(8, GameSizes::windowWidth / 2 - 6, "Press any key");
  mvprintw(9, GameSizes::windowWidth / 2 - 5, "to continue");
  nodelay(stdscr, FALSE);
  getch();
}

void BaseView::DrawBox(int topLeftY, int topLeftX, int bottomRightY,
                       int bottomRightX) {
  for (int i = topLeftY; i <= bottomRightY; ++i) {
    mvaddch(i, topLeftX, ACS_VLINE);
    mvaddch(i, bottomRightX, ACS_VLINE);
  }

  for (int i = topLeftX; i <= bottomRightX; ++i) {
    mvaddch(topLeftY, i, ACS_HLINE);
    mvaddch(bottomRightY, i, ACS_HLINE);
  }

  mvaddch(topLeftY, topLeftX, ACS_ULCORNER);
  mvaddch(topLeftY, bottomRightX, ACS_URCORNER);
  mvaddch(bottomRightY, topLeftX, ACS_LLCORNER);
  mvaddch(bottomRightY, bottomRightX, ACS_LRCORNER);
}

UserAction BaseView::GetAction() {
  UserAction action = UserAction::noSig;
  int key = getch();
  switch (key) {
    case KEY_LEFT:
      action = UserAction::left;
      break;
    case KEY_RIGHT:
      action = UserAction::right;
      break;
    case KEY_UP:
      action = UserAction::up;
      break;
    case KEY_DOWN:
      action = UserAction::down;
      break;
    case 13:  // Enter
      action = UserAction::enterBtn;
      break;
    case 9:  // left tab
      action = UserAction::tabBtn;
      break;
    case 32:  // space
      action = UserAction::spaceBtn;
      break;
    case 27:  // esc
      action = UserAction::escBtn;
      break;
    default:
      break;
  }
  nodelay(stdscr, TRUE);
  return action;
}

void BaseView::PauseRendering(int level, int score) {
  clear();
  DrawBox(0, 0, GameSizes::windowHeight, GameSizes::windowWidth);

  mvprintw(5, GameSizes::windowWidth / 2 - 10, "The game is on pause");
  mvprintw(8, GameSizes::windowWidth / 2 - 7, "Your score: %d", score);
  mvprintw(10, GameSizes::windowWidth / 2 - 7, "Your level: %d", level);

  mvprintw(12, GameSizes::windowWidth / 2 - 10, "Press Tab to continue");
  mvprintw(13, GameSizes::windowWidth / 2 - 7, "or Esc to exit");
  nodelay(stdscr, FALSE);
}

void BaseView::StartGameRendering() {
  clear();
  DrawBox(0, 0, GameSizes::windowHeight, GameSizes::windowWidth);
  mvprintw(9, GameSizes::windowWidth / 2 - 6, "Press space");
  mvprintw(10, GameSizes::windowWidth / 2 - 7, "to start game");
  mvprintw(11, GameSizes::windowWidth / 2 - 7, "Or Esc to exit");
  nodelay(stdscr, FALSE);
}

void BaseView::MenuRendering(std::size_t &selectedItem) {
  clear();

  int startY = 10;
  int startX = GameSizes::windowWidth / 2;

  DrawBox(0, 0, GameSizes::windowHeight, GameSizes::windowWidth);
  mvprintw(startY - 4, startX - 4, "Game Menu");

  std::vector<std::string> choices = {"Snake", "Tetris", "Exit"};

  for (std::size_t i = 0; i < choices.size(); ++i) {
    if (i == selectedItem) {
      attron(A_REVERSE);
      mvprintw(++startY + 1, startX - (int)choices[i].length() / 2, "%s",
               choices[i].c_str());
      attroff(A_REVERSE);
    } else {
      mvprintw(++startY + 1, startX - (int)choices[i].length() / 2, "%s",
               choices[i].c_str());
    }
  }
  refresh();
}

Choose BaseView::InitMenu() {
  Choose retVal = Choose::Menu;
  std::size_t selectedItem = 0;

  MenuRendering(selectedItem);

  int ch = 0;
  nodelay(stdscr, FALSE);
  while ((ch = getch()) != '\n') {
    switch (ch) {
      case KEY_UP:
        selectedItem =
            (selectedItem == 0) ? (selectedItem) : (selectedItem - 1);
        break;
      case KEY_DOWN:
        selectedItem =
            (selectedItem == 2) ? (selectedItem) : (selectedItem + 1);
        break;
    }
    MenuRendering(selectedItem);
  }
  if (selectedItem == 0) {
    retVal = Choose::Snake;
  } else if (selectedItem == 1) {
    retVal = Choose::Tetris;
    ;
  } else if (selectedItem == 2) {
    retVal = Choose::Exit;
  }
  return retVal;
}

}  // namespace s21