#include "s21_map.h"

#include <gtest/gtest.h>

#include <map>

TEST(map, insert_at) {
  int a[10] = {3, 5, 4, 8, 10, 13, 1, 2, 30, 11};
  std::map<int, int> mp;
  s21::map<int, int> test;
  for (int i = 0; i < 10; ++i) {
    mp.insert(std::pair<int, int>(a[i], i));
    test.insert(std::pair<int, int>(a[i], i));
  }
  EXPECT_EQ(mp.at(8), test.at(8));
}

TEST(map, check_begin) {
  int a[10] = {3, 5, 4, 8, 10, 13, 1, 2, 30, 11};
  std::map<int, int> mp;
  s21::map<int, int> test;
  for (int i = 0; i < 10; ++i) {
    mp.insert(std::pair<int, int>(a[i], i));
    test.insert(std::pair<int, int>(a[i], i));
  }
  auto it1 = mp.begin();
  auto it2 = test.begin();
  EXPECT_EQ((*it1).first, (*it2).first);
}

TEST(map, check_end) {
  int a[10] = {3, 5, 4, 8, 10, 13, 1, 2, 30, 11};
  std::map<int, int> mp;
  s21::map<int, int> test;
  for (int i = 0; i < 10; ++i) {
    mp.insert(std::pair<int, int>(a[i], i));
    test.insert(std::pair<int, int>(a[i], i));
  }
  auto it_1 = mp.end();
  auto it_2 = test.end();

  --it_1;
  --it_2;
  EXPECT_EQ((*it_1).first, (*it_2).first);
}

TEST(map, insert_duplicate) {
  std::map<int, int> mp;
  s21::map<int, int> test;
  mp.insert({1, 2});
  test.insert({1, 2});
  auto res_1 = mp.insert({1, 2});
  auto res_2 = test.insert({1, 2});
  EXPECT_EQ(res_1.second, res_2.second);
}

TEST(map, at) {
  int a[10] = {3, 5, 4, 8, 10, 13, 1, 2, 30, 11};
  std::map<int, int> mp;
  s21::map<int, int> test;
  for (int i = 0; i < 10; ++i) {
    mp.insert(std::pair<int, int>(a[i], i));
    test.insert(std::pair<int, int>(a[i], i));
  }
  EXPECT_EQ(mp.at(8), test.at(8));
}

TEST(map, erase_begin) {
  int a[10] = {3, 5, 4, 8, 10, 13, 1, 2, 30, 11};
  std::map<int, int> mp;
  s21::map<int, int> test;
  for (int i = 0; i < 10; ++i) {
    mp.insert(std::pair<int, int>(a[i], i));
    test.insert(std::pair<int, int>(a[i], i));
  }
  auto rt1 = mp.begin();
  auto rt2 = test.begin();
  mp.erase(rt1);
  test.erase(rt2);
  auto res_1 = mp.begin();
  auto res_2 = test.begin();
  EXPECT_EQ((*res_1).first, (*res_2).first);
}

TEST(map, erase_pre_end) {
  int a[10] = {3, 5, 4, 8, 10, 13, 1, 2, 30, 11};
  std::map<int, int> mp;
  s21::map<int, int> test;
  for (int i = 0; i < 10; ++i) {
    mp.insert(std::pair<int, int>(a[i], i));
    test.insert(std::pair<int, int>(a[i], i));
  }
  auto rt1 = mp.end();
  auto rt2 = test.end();
  mp.erase(--rt1);
  --rt2;
  test.erase(rt2);
  auto res_1 = mp.end();
  auto res_2 = test.end();
  EXPECT_EQ((*(--res_1)).first, (*(--res_2)).first);
}

TEST(map, insert_direct_begin) {
  std::map<int, int> mp{{2, 2}, {5, 4}, {7, 3}, {9, 4}};
  s21::map<int, int> test{{2, 2}, {5, 4}, {7, 3}, {9, 4}};
  auto rt1 = mp.begin();
  auto rt2 = test.begin();
  EXPECT_EQ((*rt1).first, (*rt2).first);
}

TEST(map, insert_direct_end) {
  std::map<int, int> mp{{2, 2}, {5, 4}, {7, 3}, {9, 4}};
  s21::map<int, int> test{{2, 2}, {5, 4}, {7, 3}, {9, 4}};
  auto rt1 = mp.end();
  auto rt2 = test.end();
  EXPECT_EQ((*(--rt1)).first, (*(--rt2)).first);
}

TEST(map, insert_direct) {
  std::map<int, int> mp{{2, 2}, {5, 4}, {7, 3}, {9, 4}};
  s21::map<int, int> test{{2, 2}, {5, 4}, {7, 3}, {9, 4}};
  auto rt1 = mp.begin();
  auto rt2 = test.begin();
  ++rt1;
  ++rt1;
  ++rt2;
  ++rt2;
  EXPECT_EQ((*rt1).first, (*rt2).first);
}

TEST(map, insert_string) {
  std::map<std::string, int> mp{
      {"test", 2}, {"word", 4}, {"mega", 3}, {"house", 4}};
  s21::map<std::string, int> test{
      {"test", 2}, {"word", 4}, {"mega", 3}, {"house", 4}};
  auto rt1 = mp.begin();
  auto rt2 = test.begin();
  ++rt1;
  ++rt1;
  ++rt2;
  ++rt2;
  EXPECT_EQ((*rt1).first, (*rt2).first);
}

TEST(map, insert_string_1) {
  std::map<std::string, int> mp{
      {"test", 2}, {"test", 4}, {"mega", 3}, {"house", 4}};
  s21::map<std::string, int> test{
      {"test", 2}, {"test", 4}, {"mega", 3}, {"house", 4}};
  auto rt1 = mp.begin();
  auto rt2 = test.begin();
  ++rt1;
  ++rt1;
  ++rt2;
  ++rt2;
  EXPECT_EQ((*rt1).first, (*rt2).first);
}

TEST(map, insert_string_2) {
  std::map<std::string, int> mp{
      {"test", 2}, {"testt", 4}, {"mega", 3}, {"house", 4}};
  s21::map<std::string, int> test{
      {"test", 2}, {"testt", 4}, {"mega", 3}, {"house", 4}};

  auto rt1 = mp.begin();
  auto rt2 = test.begin();
  ++rt1;
  ++rt1;
  ++rt2;
  ++rt2;
  EXPECT_EQ((*rt1).first, (*rt2).first);
}

TEST(map, constructor_move) {
  std::map<std::string, int> mp1{
      {"test", 2}, {"testt", 4}, {"mega", 3}, {"house", 4}};
  s21::map<std::string, int> test1{
      {"test", 2}, {"testt", 4}, {"mega", 3}, {"house", 4}};
  s21::map<std::string, int> test(std::move(test1));
  std::map<std::string, int> mp(std::move(mp1));
  auto rt1 = mp.begin();
  auto rt2 = test.begin();
  ++rt1;
  ++rt1;
  ++rt2;
  ++rt2;
  EXPECT_EQ((*rt1).first, (*rt2).first);
}

TEST(map, operator_move) {
  std::map<std::string, int> mp1{
      {"test", 2}, {"testt", 4}, {"mega", 3}, {"house", 4}};
  s21::map<std::string, int> test1{
      {"test", 2}, {"testt", 4}, {"mega", 3}, {"house", 4}};
  s21::map<std::string, int> test;
  std::map<std::string, int> mp;
  test = std::move(test1);
  mp = std::move(mp1);
  auto rt1 = mp.begin();
  auto rt2 = test.begin();
  ++rt1;
  ++rt1;
  ++rt2;
  ++rt2;
  EXPECT_EQ((*rt1).first, (*rt2).first);
}

TEST(map, operator_copy) {
  std::map<double, std::string> mp1{
      {2.04, "test"}, {15.432, "testt"}, {0.345, "mega"}, {0.54, "house"}};
  s21::map<double, std::string> test1{
      {2.04, "test"}, {15.432, "testt"}, {0.345, "mega"}, {0.54, "house"}};
  std::map<double, std::string> mp(mp1);
  s21::map<double, std::string> test(test1);
  auto it_mp = mp.begin();
  auto it_test = test.begin();
  EXPECT_EQ((*it_mp).first, (*it_test).first);
}

TEST(map, operator_copy_end) {
  std::map<double, std::string> mp1{
      {2.04, "test"}, {15.432, "testt"}, {0.345, "mega"}, {0.54, "house"}};
  s21::map<double, std::string> test1{
      {2.04, "test"}, {15.432, "testt"}, {0.345, "mega"}, {0.54, "house"}};
  std::map<double, std::string> mp(mp1);
  s21::map<double, std::string> test(test1);
  auto it_mp = mp.end();
  auto it_test = test.end();
  --it_mp;
  --it_test;
  EXPECT_EQ((*it_mp).first, (*it_test).first);
}

TEST(map, operator_copy_insert) {
  std::map<double, std::string> mp1{
      {2.04, "test"}, {15.432, "testt"}, {0.345, "mega"}, {0.54, "house"}};
  s21::map<double, std::string> test1{
      {2.04, "test"}, {15.432, "testt"}, {0.345, "mega"}, {0.54, "house"}};
  std::map<double, std::string> mp(mp1);
  s21::map<double, std::string> test(test1);
  mp.insert(std::pair<double, std::string>(3.43, "work"));
  test.insert(std::pair<double, std::string>(3.43, "work"));
  auto it_mp = mp.begin();
  auto it_test = test.begin();
  for (long unsigned int i = 0; i < test.size(); i++) {
    EXPECT_EQ((*it_mp).first, (*it_test).first);
    ++it_test;
    ++it_mp;
  }
}

TEST(map, operator_br) {
  std::map<double, std::string> mp1{
      {2.04, "test"}, {15.432, "testt"}, {0.345, "mega"}, {0.54, "house"}};
  s21::map<double, std::string> test1{
      {2.04, "test"}, {15.432, "testt"}, {0.345, "mega"}, {0.54, "house"}};
  EXPECT_EQ(mp1[2.04], test1[2.04]);
  EXPECT_EQ(mp1[3], test1[3]);
}

TEST(map, empty_check) {
  s21::map<double, std::string> test1;
  EXPECT_TRUE(test1.empty());
}

TEST(map, empty_check_false) {
  s21::map<double, std::string> test1{
      {2.04, "test"}, {15.432, "testt"}, {0.345, "mega"}, {0.54, "house"}};
  EXPECT_FALSE(test1.empty());
}

TEST(map, merge) {
  std::map<double, std::string> mp1{
      {2.04, "test"}, {15.432, "testt"}, {0.345, "mega"}, {0.54, "house"}};
  s21::map<double, std::string> test1{
      {2.04, "test"}, {15.432, "testt"}, {0.345, "mega"}, {0.54, "house"}};
  std::map<double, std::string> mp2{
      {3.45, "test"}, {1.456, "testt"}, {0.123, "mega"}, {13.03, "house"}};
  s21::map<double, std::string> test2{
      {3.45, "test"}, {1.456, "testt"}, {0.123, "mega"}, {13.03, "house"}};
  mp1.merge(mp2);
  test1.merge(test2);
  auto it1 = mp1.begin();
  auto it2 = test1.begin();
  EXPECT_EQ((*it1).first, (*it2).first);
}

TEST(map, swap) {
  s21::map<double, std::string> test1{
      {2.04, "test"}, {15.432, "testt"}, {0.345, "mega"}, {0.54, "house"}};
  s21::map<double, std::string> test2{
      {3.45, "test"}, {1.456, "testt"}, {0.123, "mega"}, {13.03, "house"}};
  test1.swap(test2);
  auto it1 = test1.begin();
  auto it2 = test2.begin();
  EXPECT_EQ((*it1).first, 0.123);
  EXPECT_EQ((*it2).first, 0.345);
}

TEST(map, insert_or_assign_exist) {
  std::map<int, std::string> test1{
      {5, "test"}, {15, "testt"}, {10, "mega"}, {4, "house"}};
  s21::map<int, std::string> test2{
      {5, "test"}, {15, "testt"}, {10, "mega"}, {4, "house"}};
  test1.insert_or_assign(5, "wwoorrkk");
  test2.insert_or_assign(5, "wwoorrkk");
  EXPECT_EQ(test1[5], test2[5]);
}

TEST(map, insert_or_assign_not_exist) {
  std::map<int, std::string> test1{
      {5, "test"}, {15, "testt"}, {10, "mega"}, {4, "house"}};
  s21::map<int, std::string> test2{
      {5, "test"}, {15, "testt"}, {10, "mega"}, {4, "house"}};
  test1.insert_or_assign(7, "wwoorrkk");
  test2.insert_or_assign(7, "wwoorrkk");
  EXPECT_EQ(test1[7], test2[7]);
}
