#include <gtest/gtest.h>

#include "s21_array.h"

TEST(ArrayConstructorSuite, ConstructEmpty) {
  s21::array<int, 5> s21_array;
  std::array<int, 5> std_array;
  ASSERT_TRUE(s21_array.size() == 5);
  ASSERT_TRUE(s21_array.size() == std_array.size());
}

// size_t cannot be negative, so i am not testing this situation
TEST(ArrayConstructorSuite, ConstructorZero) {
  s21::array<int, 0> s21_array;
  std::array<int, 0> std_array;
  ASSERT_TRUE(s21_array.size() == 0);
  ASSERT_TRUE(s21_array.size() == std_array.size());
}

TEST(ArrayConstructorSuite, ConstructFromList) {
  s21::array<int, 3> s21_array{3, 4, 5};
  std::array<int, 3> std_array{3, 4, 5};
  ASSERT_TRUE(s21_array.size() == 3);
  ASSERT_TRUE(s21_array.size() == std_array.size());
  for (int i = 0; i < 3; i++) ASSERT_TRUE(s21_array[i] == std_array[i]);
}

TEST(ArrayConstructorSuite, ConstructFromListUneven) {
  s21::array<int, 3> s21_array{3, 4};
  std::array<int, 3> std_array{3, 4};
  ASSERT_TRUE(s21_array.size() == 3);
  ASSERT_TRUE(s21_array.size() == std_array.size());
  for (int i = 0; i < 3; i++) ASSERT_TRUE(s21_array[i] == std_array[i]);
}

TEST(ArrayConstructorSuite, ConstructFromListOperator) {
  s21::array<int, 3> s21_array = {3, 4, 5};
  std::array<int, 3> std_array = {3, 4, 5};
  ASSERT_TRUE(s21_array.size() == 3);
  ASSERT_TRUE(s21_array.size() == std_array.size());
  for (int i = 0; i < 3; i++) ASSERT_TRUE(s21_array[i] == std_array[i]);
}

TEST(ArrayConstructorSuite, ConstructFromListUnevenOperator) {
  s21::array<int, 3> s21_array = {3, 4};
  std::array<int, 3> std_array = {3, 4};
  ASSERT_TRUE(s21_array.size() == 3);
  ASSERT_TRUE(s21_array.size() == std_array.size());
  for (int i = 0; i < 3; i++) ASSERT_TRUE(s21_array[i] == std_array[i]);
}

TEST(ArrayConstructorSuite, ConstructFromListEmpty) {
  s21::array<int, 0> s21_array{};
  std::array<int, 0> std_array{};
  ASSERT_TRUE(s21_array.size() == 0);
  ASSERT_TRUE(s21_array.size() == std_array.size());
}

TEST(ArrayConstructorSuite, CopyConstructor) {
  s21::array<int, 4> s21_array{3, 4, 6, 7};
  s21::array<int, 4> s21_array_copy(s21_array);
  std::array<int, 4> std_array{3, 4, 6, 7};
  std::array<int, 4> std_array_copy(std_array);
  ASSERT_TRUE(s21_array_copy.size() == 4);
  ASSERT_TRUE(s21_array_copy.size() == std_array_copy.size());
  for (int i = 0; i < 4; i++)
    ASSERT_TRUE(s21_array_copy[i] == std_array_copy[i]);
}

TEST(ArrayConstructorSuite, MoveConstructor) {
  s21::array<int, 4> s21_array{3, 4, 6, 7};
  s21::array<int, 4> s21_array_move(std::move(s21_array));
  std::array<int, 4> std_array{3, 4, 6, 7};
  std::array<int, 4> std_array_move(std::move(std_array));
  ASSERT_TRUE(s21_array_move.size() == 4);
  ASSERT_TRUE(s21_array_move.size() == std_array_move.size());
  for (int i = 0; i < 4; i++)
    ASSERT_TRUE(s21_array_move[i] == std_array_move[i]);
}

TEST(ArrayConstructorSuite, OperatorConstructor) {
  s21::array<int, 4> s21_array{3, 4, 6, 7};
  s21::array<int, 4> s21_array_move = std::move(s21_array);
  std::array<int, 4> std_array{3, 4, 6, 7};
  std::array<int, 4> std_array_move = std::move(std_array);
  ASSERT_TRUE(s21_array_move.size() == 4);
  ASSERT_TRUE(s21_array_move.size() == std_array_move.size());
  for (int i = 0; i < 4; i++)
    ASSERT_TRUE(s21_array_move[i] == std_array_move[i]);
}

TEST(ArrayConstructorSuite, ClearPrevious) {
  s21::array<int, 4> s21_array{3, 4, 6, 7};
  s21::array<int, 4> s21_array_move = {2, 7, 3, 2};
  s21_array_move = std::move(s21_array);
  std::array<int, 4> std_array{3, 4, 6, 7};
  std::array<int, 4> std_array_move = {2, 7, 3, 2};
  std_array_move = std::move(std_array);
  ASSERT_TRUE(s21_array_move.size() == 4);
  ASSERT_TRUE(s21_array_move.size() == std_array_move.size());
  for (int i = 0; i < 4; i++)
    ASSERT_TRUE(s21_array_move[i] == std_array_move[i]);
}

TEST(ArrayAtSuite, RightAt) {
  s21::array<int, 4> s21_array{3, 4, 6, 7};
  std::array<int, 4> std_array{3, 4, 6, 7};
  for (int i = 0; i < 4; i++) ASSERT_TRUE(s21_array.at(i) == std_array.at(i));
}

TEST(ArrayAtSuite, ExceptionAt) {
  s21::array<int, 4> s21_array{3, 4, 6, 7};
  std::array<int, 4> std_array{3, 4, 6, 7};
  ASSERT_THROW(s21_array.at(4), std::out_of_range);
  ASSERT_THROW(std_array.at(4), std::out_of_range);
}

TEST(ArrayBracketsSuite, NormalBraces) {
  s21::array<int, 4> s21_array{3, 4, 6, 7};
  std::array<int, 4> std_array{3, 4, 6, 7};
  for (int i = 0; i < 4; i++) ASSERT_TRUE(s21_array[i] == std_array[i]);
}

TEST(ArrayBracketsSuite, NoException) {
  s21::array<int, 4> s21_array{3, 4, 6, 7};
  std::array<int, 4> std_array{3, 4, 6, 7};
  ASSERT_NO_THROW(s21_array[4]);
  ASSERT_NO_THROW(std_array[4]);
}

TEST(ArrayFrontBackSuite, Front) {
  s21::array<int, 4> s21_array{3, 4, 6, 7};
  std::array<int, 4> std_array{3, 4, 6, 7};
  ASSERT_TRUE(s21_array.front() == 3);
  ASSERT_TRUE(s21_array.front() == std_array.front());
}

TEST(ArrayFrontBackSuite, Back) {
  s21::array<int, 4> s21_array{3, 4, 6, 7};
  std::array<int, 4> std_array{3, 4, 6, 7};
  ASSERT_TRUE(s21_array.back() == 7);
  ASSERT_TRUE(s21_array.back() == std_array.back());
}

TEST(ArrayFrontBackSuite, FrontBack) {
  s21::array<int, 1> s21_array{3};
  std::array<int, 1> std_array{3};
  ASSERT_TRUE(s21_array.front() == 3);
  ASSERT_TRUE(s21_array.front() == s21_array.back());
  ASSERT_TRUE(std_array.front() == std_array.back());
  ASSERT_TRUE(s21_array.front() == std_array.front());
  ASSERT_TRUE(s21_array.back() == std_array.back());
}

TEST(ArrayDataSuite, DataFromFilled) {
  s21::array<int, 7> s21_array{1, 2, 3, 4, 5, 6, 7};
  std::array<int, 7> std_array{1, 2, 3, 4, 5, 6, 7};
  s21::array<int, 7>::iterator s21_iterator = s21_array.data();
  std::array<int, 7>::iterator std_iterator = std_array.data();
  for (int i = 0; i < 7; i++) ASSERT_TRUE(*s21_iterator++ == *std_iterator++);
}

TEST(ArrayDataSuite, DataPointingAtFirst) {
  s21::array<int, 7> s21_array{1, 2, 3, 4, 5, 6, 7};
  std::array<int, 7> std_array{1, 2, 3, 4, 5, 6, 7};
  s21::array<int, 7>::iterator s21_iterator = s21_array.data();
  std::array<int, 7>::iterator std_iterator = std_array.data();
  ASSERT_TRUE(*s21_iterator == s21_array.front());
  ASSERT_TRUE(*std_iterator == std_array.front());
  ASSERT_TRUE(*s21_iterator == *std_iterator);
  ASSERT_TRUE(s21_iterator == s21_array.begin());
  ASSERT_TRUE(std_iterator == std_array.begin());
}

TEST(ArrayBeginEndSuite, Begin) {
  s21::array<int, 7> s21_array{1, 2, 3, 4, 5, 6, 7};
  std::array<int, 7> std_array{1, 2, 3, 4, 5, 6, 7};
  ASSERT_TRUE(*s21_array.begin() == s21_array.front());
  ASSERT_TRUE(*std_array.begin() == std_array.front());
  ASSERT_TRUE(*s21_array.begin() == *std_array.begin());
}

TEST(ArrayBeginEndSuite, End) {
  s21::array<int, 7> s21_array{1, 2, 3, 4, 5, 6, 7};
  std::array<int, 7> std_array{1, 2, 3, 4, 5, 6, 7};
  ASSERT_TRUE(*std::prev(s21_array.end()) == s21_array.back());
  ASSERT_TRUE(*std::prev(std_array.end()) == std_array.back());
  ASSERT_TRUE(*std::prev(s21_array.end()) == *std::prev(std_array.end()));
}

TEST(ArrayBeginEndSuite, BeginEndOnEmpty) {
  s21::array<int, 0> s21_array;
  std::array<int, 0> std_array;
  ASSERT_TRUE(s21_array.begin() == s21_array.end());
  ASSERT_TRUE(std_array.begin() == std_array.end());
}

TEST(ArraySizeSuite, Empty) {
  s21::array<int, 0> s21_array;
  std::array<int, 0> std_array;
  ASSERT_TRUE(s21_array.empty());
  ASSERT_TRUE(std_array.empty());
}

TEST(ArraySizeSuite, NotEmpty) {
  s21::array<int, 6> s21_array;
  std::array<int, 6> std_array;
  ASSERT_FALSE(s21_array.empty());
  ASSERT_FALSE(std_array.empty());
}

TEST(ArraySizeSuite, SizeZero) {
  s21::array<int, 0> s21_array;
  std::array<int, 0> std_array;
  ASSERT_TRUE(s21_array.size() == 0);
  ASSERT_TRUE(s21_array.max_size() == 0);
  ASSERT_TRUE(std_array.size() == 0);
  ASSERT_TRUE(std_array.max_size() == 0);
}

TEST(ArraySizeSuite, SizeNotZero) {
  s21::array<int, 6> s21_array;
  std::array<int, 6> std_array;
  ASSERT_TRUE(s21_array.size() == 6);
  ASSERT_TRUE(s21_array.max_size() == 6);
  ASSERT_TRUE(std_array.size() == 6);
  ASSERT_TRUE(std_array.max_size() == 6);
}

TEST(ArraySwapSuite, Swap) {
  s21::array<int, 7> s21_array_1{1, 2, 3, 4, 5, 6, 7};
  s21::array<int, 7> s21_array_1_copy(s21_array_1);
  s21::array<int, 7> s21_array_2{8, 9, 10, 11, 12, 13, 14};
  s21::array<int, 7> s21_array_2_copy(s21_array_2);
  std::array<int, 7> std_array_1{1, 2, 3, 4, 5, 6, 7};
  std::array<int, 7> std_array_1_copy(std_array_1);
  std::array<int, 7> std_array_2{8, 9, 10, 11, 12, 13, 14};
  std::array<int, 7> std_array_2_copy(std_array_2);
  s21::array<int, 7>::iterator s21_begin_1 = s21_array_1.begin();
  s21::array<int, 7>::iterator s21_begin_2 = s21_array_2.begin();
  std::array<int, 7>::iterator std_begin_1 = std_array_1.begin();
  std::array<int, 7>::iterator std_begin_2 = std_array_2.begin();
  s21_array_1.swap(s21_array_2);
  std_array_1.swap(std_array_2);
  // Does not cause iterators and references
  // to associate with the other container.
  ASSERT_TRUE(s21_begin_1 == s21_array_1.begin());
  ASSERT_TRUE(s21_begin_2 == s21_array_2.begin());
  ASSERT_TRUE(std_begin_1 == std_array_1.begin());
  ASSERT_TRUE(std_begin_2 == std_array_2.begin());
  for (int i = 0; i < 7; i++) {
    ASSERT_TRUE(s21_array_1[i] == s21_array_2_copy[i]);
    ASSERT_TRUE(std_array_1[i] == std_array_2_copy[i]);
    ASSERT_TRUE(s21_array_1[i] == std_array_1[i]);
    ASSERT_TRUE(s21_array_2[i] == s21_array_1_copy[i]);
    ASSERT_TRUE(std_array_2[i] == std_array_1_copy[i]);
    ASSERT_TRUE(s21_array_2[i] == std_array_2[i]);
  }
}

TEST(FillSuite, FillNormal) {
  s21::array<int, 9> s21_array;
  std::array<int, 9> std_array;
  s21_array.fill(5);
  std_array.fill(5);
  for (int i = 0; i < 9; i++) ASSERT_TRUE(s21_array[i] == std_array[i]);
}

TEST(FillSuite, FillFilled) {
  s21::array<int, 5> s21_array{2, 4, 6, 7, 8};
  std::array<int, 5> std_array{2, 4, 6, 7, 8};
  s21_array.fill(1);
  std_array.fill(1);
  for (int i = 0; i < 5; i++) ASSERT_TRUE(s21_array[i] == std_array[i]);
}

TEST(FillSuite, FillMalloced) {
  int *numbers = new int[10]{8};
  s21::array<int *, 5> s21_array;
  std::array<int *, 5> std_array;
  s21_array[0] = numbers;
  std_array[0] = numbers;
  int *new_numbers = new int[8]{7, 7, 7, 7, 7, 7, 7, 7};
  s21_array.fill(new_numbers);
  std_array.fill(new_numbers);
  for (int i = 0; i < 8; i++) {
    ASSERT_TRUE(s21_array[0][i] == 7);
    ASSERT_TRUE(s21_array[0][i] == std_array[0][i]);
  }
  delete[] numbers;
  delete[] new_numbers;
}

TEST(FillSuite, FillEmpty) {
  s21::array<int, 0> s21_array;
  std::array<int, 0> std_array;
  ASSERT_NO_THROW(s21_array.fill(89));
  ASSERT_NO_THROW(std_array.fill(89));
  ASSERT_TRUE(s21_array.size() == 0);
  ASSERT_TRUE(s21_array.size() == std_array.size());
}
