#include "s21_set.h"

#include <gtest/gtest.h>

#include <set>

TEST(set, insert_at) {
  int a[10] = {3, 5, 4, 8, 10, 13, 1, 2, 30, 11};
  std::set<int> mp;
  s21::set<int> test;
  for (int i = 0; i < 10; ++i) {
    mp.insert(a[i]);
    test.insert(a[i]);
  }
  auto it1 = mp.begin();
  auto it2 = test.begin();
  EXPECT_EQ(*it1, *it2);
}

TEST(set, check_begin) {
  int a[10] = {3, 5, 4, 8, 10, 13, 1, 2, 30, 11};
  std::set<int> mp;
  s21::set<int> test;
  for (int i = 0; i < 10; ++i) {
    mp.insert(a[i]);
    test.insert(a[i]);
  }
  auto it1 = mp.begin();
  auto it2 = test.begin();
  EXPECT_EQ(*it1, *it2);
}

TEST(set, check_end) {
  int a[10] = {3, 5, 4, 8, 10, 13, 1, 2, 30, 11};
  std::set<int> mp;
  s21::set<int> test;
  for (int i = 0; i < 10; ++i) {
    mp.insert(a[i]);
    test.insert(a[i]);
  }
  auto it_1 = mp.end();
  auto it_2 = test.end();

  --it_1;
  --it_2;
  EXPECT_EQ(*it_1, *it_2);
}

TEST(set, insert_duplicate) {
  std::set<int> mp;
  s21::set<int> test;
  mp.insert(1);
  test.insert(1);
  auto res_1 = mp.insert(1);
  auto res_2 = test.insert(1);
  EXPECT_EQ(res_1.second, res_2.second);
}

TEST(set, erase_begin) {
  int a[10] = {3, 5, 4, 8, 10, 13, 1, 2, 30, 11};
  std::set<int> mp;
  s21::set<int> test;
  for (int i = 0; i < 10; ++i) {
    mp.insert(a[i]);
    test.insert(a[i]);
  }
  auto rt1 = mp.begin();
  auto rt2 = test.begin();
  mp.erase(rt1);
  test.erase(rt2);
  auto res_1 = mp.begin();
  auto res_2 = test.begin();
  EXPECT_EQ(*res_1, *res_2);
}

TEST(set, erase_pre_end) {
  int a[10] = {3, 5, 4, 8, 10, 13, 1, 2, 30, 11};
  std::set<int> mp;
  s21::set<int> test;
  for (int i = 0; i < 10; ++i) {
    mp.insert(a[i]);
    test.insert(a[i]);
  }
  auto rt1 = mp.end();
  auto rt2 = test.end();
  mp.erase(--rt1);
  --rt2;
  test.erase(rt2);
  auto res_1 = mp.end();
  auto res_2 = test.end();
  EXPECT_EQ(*(--res_1), *(--res_2));
}

TEST(set, insert_direct_begin) {
  std::set<int> mp{2, 5, 7, 9};
  s21::set<int> test{2, 5, 7, 9};
  auto rt1 = mp.begin();
  auto rt2 = test.begin();
  EXPECT_EQ(*rt1, *rt2);
}

TEST(set, insert_direct_end) {
  std::set<int> mp{2, 5, 7, 9};
  s21::set<int> test{2, 5, 7, 9};
  auto rt1 = mp.end();
  auto rt2 = test.end();
  EXPECT_EQ(*(--rt1), *(--rt2));
}

TEST(set, insert_direct) {
  std::set<int> mp{2, 5, 7, 9};
  s21::set<int> test{2, 5, 7, 9};
  auto rt1 = mp.begin();
  auto rt2 = test.begin();
  ++rt1;
  ++rt1;
  ++rt2;
  ++rt2;
  EXPECT_EQ(*rt1, *rt2);
}

TEST(set, insert_string) {
  std::set<std::string> mp{"test", "word", "mega", "house"};
  s21::set<std::string> test{"test", "word", "mega", "house"};
  auto rt1 = mp.begin();
  auto rt2 = test.begin();
  ++rt1;
  ++rt1;
  ++rt2;
  ++rt2;
  EXPECT_EQ(*rt1, *rt2);
}

TEST(set, insert_string_1) {
  std::set<std::string> mp{"test", "test", "mega", "house"};
  s21::set<std::string> test{"test", "test", "mega", "house"};
  auto rt1 = mp.begin();
  auto rt2 = test.begin();
  ++rt1;
  ++rt1;
  ++rt2;
  ++rt2;
  EXPECT_EQ(*rt1, *rt2);
}

TEST(set, insert_string_2) {
  std::set<std::string> mp{"test", "ttest", "mega", "house"};
  s21::set<std::string> test{"test", "ttest", "mega", "house"};
  auto rt1 = mp.begin();
  auto rt2 = test.begin();
  ++rt1;
  ++rt1;
  ++rt2;
  ++rt2;
  EXPECT_EQ(*rt1, *rt2);
}
TEST(set, constructor_move) {
  std::set<std::string> mp1{"test", "ttest", "mega", "house"};
  s21::set<std::string> test1{"test", "ttest", "mega", "house"};
  s21::set<std::string> test(std::move(test1));
  std::set<std::string> mp(std::move(mp1));
  auto rt1 = mp.begin();
  auto rt2 = test.begin();
  ++rt1;
  ++rt1;
  ++rt2;
  ++rt2;
  EXPECT_EQ(*rt1, *rt2);
}
TEST(set, operator_move) {
  std::set<std::string> mp1{"test", "ttest", "mega", "house"};
  s21::set<std::string> test1{"test", "ttest", "mega", "house"};
  s21::set<std::string> test;
  std::set<std::string> mp;
  test = std::move(test1);
  mp = std::move(mp1);
  auto rt1 = mp.begin();
  auto rt2 = test.begin();
  ++rt1;
  ++rt1;
  ++rt2;
  ++rt2;
  EXPECT_EQ(*rt1, *rt2);
}

TEST(set, operator_copy) {
  std::set<std::string> mp1{"test", "ttest", "mega", "house"};
  s21::set<std::string> test1{"test", "ttest", "mega", "house"};
  std::set<std::string> mp(mp1);
  s21::set<std::string> test(test1);
  auto it_mp = mp.begin();
  auto it_test = test.begin();
  EXPECT_EQ(*it_mp, *it_test);
}

TEST(set, operator_copy_end) {
  std::set<std::string> mp1{"test", "ttest", "mega", "house"};
  s21::set<std::string> test1{"test", "ttest", "mega", "house"};
  std::set<std::string> mp(mp1);
  s21::set<std::string> test(test1);
  auto it_mp = mp.end();
  auto it_test = test.end();
  --it_mp;
  --it_test;
  EXPECT_EQ(*it_mp, *it_test);
}

TEST(set, operator_copy_insert) {
  std::set<std::string> mp1{"test", "ttest", "mega", "house"};
  s21::set<std::string> test1{"test", "ttest", "mega", "house"};
  std::set<std::string> mp(mp1);
  s21::set<std::string> test(test1);
  mp.insert("work");
  test.insert("work");
  auto it_mp = mp.begin();
  auto it_test = test.begin();
  for (long unsigned int i = 0; i < test.size(); i++) {
    EXPECT_EQ(*it_mp, *it_test);
    ++it_test;
    ++it_mp;
  }
}

TEST(set, empty_check) {
  s21::set<double> test1;
  EXPECT_TRUE(test1.empty());
}

TEST(set, empty_check_false) {
  s21::set<std::string> test1{"test", "ttest", "mega", "house"};
  EXPECT_FALSE(test1.empty());
}

TEST(set, merge) {
  std::set<std::string> mp1{"test", "ttest", "mega", "house"};
  s21::set<std::string> test1{"test", "ttest", "mega", "house"};
  std::set<std::string> mp2{"grep", "cat"};
  s21::set<std::string> test2{"grep", "cat"};
  mp1.merge(mp2);
  test1.merge(test2);
  auto it1 = mp1.begin();
  auto it2 = test1.begin();
  EXPECT_EQ(*it1, *it2);
}

TEST(set, swap) {
  s21::set<std::string> test1{"test", "ttest", "mega", "house"};
  s21::set<std::string> test2{"grep", "cat"};
  test1.swap(test2);
  auto it1 = test1.begin();
  auto it2 = test2.begin();
  EXPECT_EQ(*it1, "cat");
  EXPECT_EQ(*it2, "house");
}
