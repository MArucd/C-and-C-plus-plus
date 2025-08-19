#ifndef BRICKGAME_BASEMODEL_H_
#define BRICKGAME_BASEMODEL_H_

#include <chrono>
#include <fstream>
#include <iostream>
#include <random>

#include "Constants.h"

namespace s21 {

class BaseModel {
 public:
  static long long GetCurrentTime() {
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    return ms.count();
  }

  static void SaveScore(int score, const std::string& fileName) {
    std::ofstream file(fileName);
    if (file.is_open()) {
      file << score;
      file.close();
    }
  }

  static int LoadScore(const std::string& fileName) {
    int score = 0;
    std::ifstream file(fileName);
    if (file.is_open()) {
      file >> score;
      file.close();
    }
    return score;
  }
};

}  // namespace s21
#endif  // BRICKGAME_BASEMODEL_H_