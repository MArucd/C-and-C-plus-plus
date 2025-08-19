#include "s21_multiset.h"

#include <gtest/gtest.h>

#include <set>

TEST(multiset, insert_at) {
  int a[10] = {3, 5, 4, 8, 10, 13, 1, 2, 30, 11};
  std::multiset<int> mp;
  s21::multiset<int> test;
  for (int i = 0; i < 10; ++i) {
    mp.insert(a[i]);
    test.insert(a[i]);
  }
  auto it1 = mp.begin();
  auto it2 = test.begin();
  EXPECT_EQ(*it1, *it2);
}

TEST(multiset, check_begin) {
  int a[10] = {3, 5, 4, 8, 10, 13, 1, 2, 30, 11};
  std::multiset<int> mp;
  s21::multiset<int> test;
  for (int i = 0; i < 10; ++i) {
    mp.insert(a[i]);
    test.insert(a[i]);
  }
  auto it1 = mp.begin();
  auto it2 = test.begin();
  EXPECT_EQ(*it1, *it2);
}

TEST(multiset, check_end) {
  int a[10] = {3, 5, 4, 8, 10, 13, 1, 2, 30, 11};
  std::multiset<int> mp;
  s21::multiset<int> test;
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

TEST(multiset, insert_duplicate) {
  std::multiset<int> mp;
  s21::multiset<int> test;
  mp.insert(1);
  test.insert(1);
  auto res_1 = mp.insert(1);
  auto res_2 = test.insert(1);
  EXPECT_EQ(*res_1, *res_2);
}

TEST(multiset, erase_begin) {
  int a[10] = {3, 5, 4, 8, 10, 13, 1, 2, 30, 11};
  std::multiset<int> mp;
  s21::multiset<int> test;
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

TEST(multiset, erase_pre_end) {
  int a[10] = {3, 5, 4, 8, 10, 13, 1, 2, 30, 11};
  std::multiset<int> mp;
  s21::multiset<int> test;
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

TEST(multiset, insert_direct_begin) {
  std::multiset<int> mp{2, 5, 7, 9};
  s21::multiset<int> test{2, 5, 7, 9};
  auto rt1 = mp.begin();
  auto rt2 = test.begin();
  EXPECT_EQ(*rt1, *rt2);
}

TEST(multiset, insert_direct_end) {
  std::multiset<int> mp{2, 5, 7, 9};
  s21::multiset<int> test{2, 5, 7, 9};
  auto rt1 = mp.end();
  auto rt2 = test.end();
  EXPECT_EQ(*(--rt1), *(--rt2));
}

TEST(multiset, insert_direct) {
  std::multiset<int> mp{2, 5, 7, 9};
  s21::multiset<int> test{2, 5, 7, 9};
  auto rt1 = mp.begin();
  auto rt2 = test.begin();
  ++rt1;
  ++rt1;
  ++rt2;
  ++rt2;
  EXPECT_EQ(*rt1, *rt2);
}

TEST(multiset, insert_string) {
  std::multiset<std::string> mp{"test", "word", "mega", "house"};
  s21::multiset<std::string> test{"test", "word", "mega", "house"};
  auto rt1 = mp.begin();
  auto rt2 = test.begin();
  ++rt1;
  ++rt1;
  ++rt2;
  ++rt2;
  EXPECT_EQ(*rt1, *rt2);
}

TEST(multiset, insert_string_1) {
  std::multiset<std::string> mp{"test", "test", "mega", "house"};
  s21::multiset<std::string> test{"test", "test", "mega", "house"};
  auto rt1 = mp.begin();
  auto rt2 = test.begin();
  ++rt1;
  ++rt1;
  ++rt2;
  ++rt2;
  EXPECT_EQ(*rt1, *rt2);
}

TEST(multiset, insert_string_2) {
  std::multiset<std::string> mp{"test", "ttest", "mega", "house"};
  s21::multiset<std::string> test{"test", "ttest", "mega", "house"};
  auto rt1 = mp.begin();
  auto rt2 = test.begin();
  ++rt1;
  ++rt1;
  ++rt2;
  ++rt2;
  EXPECT_EQ(*rt1, *rt2);
}
TEST(multiset, constructor_move) {
  std::multiset<std::string> mp1{"test", "ttest", "mega", "house"};
  s21::multiset<std::string> test1{"test", "ttest", "mega", "house"};
  s21::multiset<std::string> test(std::move(test1));
  std::multiset<std::string> mp(std::move(mp1));
  auto rt1 = mp.begin();
  auto rt2 = test.begin();
  ++rt1;
  ++rt1;
  ++rt2;
  ++rt2;
  EXPECT_EQ(*rt1, *rt2);
}
TEST(multiset, operator_move) {
  std::multiset<std::string> mp1{"test", "ttest", "mega", "house"};
  s21::multiset<std::string> test1{"test", "ttest", "mega", "house"};
  s21::multiset<std::string> test;
  std::multiset<std::string> mp;
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

TEST(multiset, operator_copy) {
  std::multiset<std::string> mp1{"test", "ttest", "mega", "house"};
  s21::multiset<std::string> test1{"test", "ttest", "mega", "house"};
  std::multiset<std::string> mp(mp1);
  s21::multiset<std::string> test(test1);
  auto it_mp = mp.begin();
  auto it_test = test.begin();
  EXPECT_EQ(*it_mp, *it_test);
}

TEST(multiset, operator_copy_end) {
  std::multiset<std::string> mp1{"test", "ttest", "mega", "house"};
  s21::multiset<std::string> test1{"test", "ttest", "mega", "house"};
  std::multiset<std::string> mp(mp1);
  s21::multiset<std::string> test(test1);
  auto it_mp = mp.end();
  auto it_test = test.end();
  --it_mp;
  --it_test;
  EXPECT_EQ(*it_mp, *it_test);
}

TEST(multiset, operator_copy_insert) {
  std::multiset<std::string> mp1{"test", "ttest", "mega", "house"};
  s21::multiset<std::string> test1{"test", "ttest", "mega", "house"};
  std::multiset<std::string> mp(mp1);
  s21::multiset<std::string> test(test1);
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

TEST(multiset, empty_check) {
  s21::multiset<double> test1;
  EXPECT_TRUE(test1.empty());
}

TEST(multiset, empty_check_false) {
  s21::multiset<std::string> test1{"test", "ttest", "mega", "house"};
  EXPECT_FALSE(test1.empty());
}

TEST(multiset, merge) {
  std::multiset<std::string> mp1{"test", "ttest", "mega", "house"};
  s21::multiset<std::string> test1{"test", "ttest", "mega", "house"};
  std::multiset<std::string> mp2{"grep", "cat"};
  s21::multiset<std::string> test2{"grep", "cat"};
  mp1.merge(mp2);
  test1.merge(test2);
  auto it1 = mp1.begin();
  auto it2 = test1.begin();
  EXPECT_EQ(*it1, *it2);
}

TEST(multiset, swap) {
  s21::multiset<std::string> test1{"test", "ttest", "mega", "house"};
  s21::multiset<std::string> test2{"grep", "cat"};
  test1.swap(test2);
  auto it1 = test1.begin();
  auto it2 = test2.begin();
  EXPECT_EQ(*it1, "cat");
  EXPECT_EQ(*it2, "house");
}

TEST(multiset, upper_bound) {
  s21::multiset<int> test{1, 2, 3, 4, 6, 5, 6, 4, 7, 3, 8};
  auto it = test.upper_bound(6);
  EXPECT_EQ(*it, 7);
}

TEST(multiset, lower_bound) {
  s21::multiset<int> test{1, 2, 3, 4, 6, 5, 6, 4, 7, 3, 8};
  auto it = test.lower_bound(6);
  EXPECT_EQ(*it, 6);
}

TEST(multiset, lower_bound_not_found) {
  s21::multiset<int> test{1, 2, 3, 4, 6, 6, 4, 7, 3, 8};
  auto it = test.lower_bound(5);
  EXPECT_EQ(*it, 6);
}
