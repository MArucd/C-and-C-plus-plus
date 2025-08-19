#include <gtest/gtest.h>

#include <list>

#include "s21_list.h"
TEST(list, elback1) {
  s21::list<int> our;
  our.push_back(2);
  std::list<int> stl;
  stl.push_back(2);
  EXPECT_EQ(stl.back(), our.back());
}
TEST(list, elfront1) {
  s21::list<int> our;
  our.push_back(2);
  std::list<int> stl;
  stl.push_back(2);
  EXPECT_EQ(stl.front(), our.front());
}
TEST(list, elfront2) {
  s21::list<int> our;
  our.push_back(2);
  our.push_back(3);
  std::list<int> stl;
  stl.push_back(2);
  stl.push_back(3);
  EXPECT_EQ(stl.front(), our.front());
}
TEST(list, elback2) {
  s21::list<int> our;
  our.push_back(2);
  our.push_back(3);
  std::list<int> stl;
  stl.push_back(2);
  stl.push_back(3);
  EXPECT_EQ(stl.back(), our.back());
}

TEST(list, emtyTrue) {
  s21::list<int> our;
  std::list<int> stl;
  EXPECT_EQ(our.empty(), stl.empty());
}
TEST(list, emtyFalse) {
  s21::list<int> our;
  our.push_back(3);
  std::list<int> stl;
  stl.push_back(3);
  EXPECT_EQ(our.empty(), stl.empty());
}
TEST(list, clear) {
  s21::list<int> our;
  our.push_back(3);
  our.push_back(1);
  our.push_back(1);
  our.clear();
  std::list<int> stl;
  stl.push_back(3);
  stl.push_back(1);
  stl.push_back(1);
  stl.clear();
  EXPECT_EQ(our.empty(), stl.empty());
}
TEST(list, sizeZero) {
  s21::list<int> our;
  our.push_back(3);
  our.push_back(1);
  our.push_back(1);
  our.clear();
  std::list<int> stl;
  stl.push_back(3);
  stl.push_back(1);
  stl.push_back(1);
  stl.clear();
  EXPECT_EQ(our.size(), stl.size());
}
TEST(list, sizeThree) {
  s21::list<int> our;
  our.push_back(3);
  our.push_back(1);
  our.push_back(1);

  std::list<int> stl;
  stl.push_back(3);
  stl.push_back(1);
  stl.push_back(1);

  EXPECT_EQ(our.size(), stl.size());
}
TEST(list, push_front) {
  s21::list<int> our;
  our.push_front(3);
  our.push_front(1);
  our.push_front(1);

  std::list<int> stl;
  stl.push_front(3);
  stl.push_front(1);
  stl.push_front(1);

  EXPECT_EQ(our.back(), stl.back());
}
TEST(list, pop_front) {
  s21::list<int> our;
  our.push_front(3);
  our.push_front(1);
  our.push_front(1);
  our.pop_front();
  std::list<int> stl;
  stl.push_front(3);
  stl.push_front(1);
  stl.push_front(1);
  stl.pop_front();
  EXPECT_EQ(our.back(), stl.back());
}
TEST(list, pop_back) {
  s21::list<int> our;
  our.push_front(3);
  our.push_front(1);
  our.push_front(1);
  our.pop_back();
  std::list<int> stl;
  stl.push_front(3);
  stl.push_front(1);
  stl.push_front(1);
  stl.pop_back();
  EXPECT_EQ(our.back(), stl.back());
}
TEST(list, some_hard_test) {
  s21::list<std::string> our;
  our.push_front("haha");
  our.push_back("hi");
  our.push_front("ha");
  our.pop_back();
  our.pop_front();
  our.push_front("hs");
  std::list<std::string> stl;
  stl.push_front("haha");
  stl.push_back("hi");
  stl.push_front("ha");
  stl.pop_back();
  stl.pop_front();
  stl.push_front("hs");
  EXPECT_EQ(our.front(), stl.front());
}
TEST(list, iterator) {
  s21::list<int> our;
  our.push_front(3);
  our.push_front(2);
  our.push_front(1);
  s21::list<int>::iterator it(our.begin());
  EXPECT_EQ(*it, our.front());
  ++it;
  EXPECT_EQ(*it, 2);
  --it;
  EXPECT_EQ(*it, our.front());
  --it;
  --it;
  EXPECT_EQ(*it, our.back());
  ++it;
  ++it;
  EXPECT_EQ(*it, our.front());
  s21::list<int>::iterator it1(our.begin());
  EXPECT_EQ(it == it1, true);
  ++it1;
  EXPECT_EQ(it != it1, true);
  s21::list<int>::iterator it2(it1);
  EXPECT_EQ(it2 == it1, true);
}

TEST(list, insert_in_empty) {
  s21::list<int> our;
  s21::list<int>::iterator it_back(our.end());
  s21::list<int>::iterator it1_back(our.insert(it_back, 3));
  EXPECT_EQ(*it1_back, our.back());
  our.pop_front();
  EXPECT_EQ(0, our.front());
}
TEST(list, insert_in_1_elem) {
  s21::list<int> our;
  our.push_back(1);
  s21::list<int>::iterator it_back(our.end());
  s21::list<int>::iterator it1_back(our.insert(it_back, 3));
  EXPECT_EQ(*it1_back, our.back());
  ++it1_back;
  ++it1_back;
  EXPECT_EQ(*it1_back, 1);
  our.pop_back();
  our.push_back(1);
  s21::list<int>::iterator it_front(our.begin());
  s21::list<int>::iterator it1_front(our.insert(it_front, 3));
  EXPECT_EQ(*it1_front, our.front());
}
TEST(list, insert_in_a_few_elem) {
  s21::list<int> our;
  our.push_back(1);
  our.push_back(2);
  our.push_back(4);
  s21::list<int>::iterator it_back(our.end());
  --it_back;
  s21::list<int>::iterator it_new_back(our.insert(it_back, 3));
  ++it_new_back;
  EXPECT_EQ(*it_new_back, 4);
  --it_new_back;
  EXPECT_EQ(*it_new_back, 3);
  --it_new_back;
  EXPECT_EQ(*it_new_back, 2);
}
TEST(list, insert_in_a_2_elem) {
  s21::list<int> our;
  our.push_back(1);
  our.push_back(2);
  s21::list<int>::iterator it_back(our.end());
  s21::list<int>::iterator it_new_back(our.insert(it_back, 3));
  ++it_new_back;
  ++it_new_back;
  EXPECT_EQ(*it_new_back, 1);
  --it_new_back;
  --it_new_back;
  EXPECT_EQ(*it_new_back, 3);
}

TEST(list, push_pop) {
  s21::list<int> our;
  our.push_back(1);
  s21::list<int>::iterator it(our.begin());
  EXPECT_EQ(*it, 1);
  our.pop_back();
  our.push_front(1);
  EXPECT_EQ(our.back(), 1);
  EXPECT_EQ(our.front(), 1);
  our.pop_front();
  our.push_back(1);
  EXPECT_EQ(our.back(), 1);
  EXPECT_EQ(our.front(), 1);
}

TEST(list, erase) {
  s21::list<int> our;
  our.push_back(1);
  s21::list<int>::iterator it(our.begin());
  our.erase(it);
  EXPECT_EQ(our.front(), 0);
}

TEST(list, erase_elem) {
  s21::list<int> our;
  our.push_front(1);
  our.push_back(2);
  our.push_back(3);
  s21::list<int>::iterator it(our.begin());
  ++it;
  our.erase(it);
  auto it_test(our.begin());
  ++it_test;
  EXPECT_EQ(*it_test, 3);
  --it_test;
  EXPECT_EQ(*it_test, 1);
}
TEST(list, merge) {
  s21::list<int> our;
  s21::list<int> our1;
  our.push_back(1);
  our.push_back(2);
  our.push_back(3);
  our1.push_back(0);
  our1.push_back(5);
  our1.push_back(6);
  our.merge(our1);
  auto it(our.begin());
  EXPECT_EQ(*it, 0);
  ++it;
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 5);
  ++it;
  EXPECT_EQ(*it, 6);
}
TEST(list, merge_string) {
  s21::list<std::string> our;
  s21::list<std::string> our1;
  our.push_back("as");
  our.push_back("c");
  our.push_back("ab");
  our1.push_back("ag");
  our1.push_back("b");
  our1.push_back("abc");
  our.merge(our1);
  auto it(our.begin());
  EXPECT_EQ(*it, "ag");
  ++it;
  EXPECT_EQ(*it, "as");
  ++it;
  EXPECT_EQ(*it, "b");
  ++it;
  EXPECT_EQ(*it, "abc");
  ++it;
  EXPECT_EQ(*it, "c");
  ++it;
  EXPECT_EQ(*it, "ab");
}
TEST(list, split) {
  s21::list<int> our;
  s21::list<int> our1;
  our.push_back(1);
  our.push_back(2);
  our1.push_back(0);
  our1.push_back(5);
  our1.push_back(6);
  auto it(our.begin());
  ++it;
  our.splice(it, our1);
  auto it_check(our.begin());
  EXPECT_EQ(*it_check, 1);
  ++it_check;
  EXPECT_EQ(*it_check, 0);
  ++it_check;
  EXPECT_EQ(*it_check, 5);
  ++it_check;
  EXPECT_EQ(*it_check, 6);
  ++it_check;
  EXPECT_EQ(*it_check, 2);
}
TEST(list, split1) {
  s21::list<int> our;
  s21::list<int> our1;
  our1.push_back(0);
  our1.push_back(5);
  our1.push_back(6);
  auto it(our.begin());
  ++it;
  our.splice(it, our1);
  auto it_check(our.begin());
  EXPECT_EQ(*it_check, 0);
  ++it_check;
  EXPECT_EQ(*it_check, 5);
  ++it_check;
  EXPECT_EQ(*it_check, 6);
}
TEST(list, initializer_list) {
  s21::list<int> our;
  s21::list<int> our1{1, 5, 6};
  auto it(our.begin());
  ++it;
  our.splice(it, our1);
  auto it_check(our.begin());
  EXPECT_EQ(*it_check, 1);
  ++it_check;
  EXPECT_EQ(*it_check, 5);
  ++it_check;
  EXPECT_EQ(*it_check, 6);
}

TEST(list, unique) {
  s21::list<int> our{1, 1, 1, 2, 2, 3, 3, 3};
  our.unique();
  auto it_check(our.begin());
  EXPECT_EQ(*it_check, 1);
  ++it_check;
  EXPECT_EQ(*it_check, 2);
  ++it_check;
  EXPECT_EQ(*it_check, 3);
}
TEST(list, sortInt) {
  s21::list<int> our;
  our.push_back(2);
  our.push_back(7);
  our.push_back(9);
  our.push_back(8);
  our.push_back(1);
  our.push_back(3);
  our.sort();
  std::list<int> stl;
  stl.push_back(9);
  stl.push_back(2);
  stl.push_back(7);
  stl.push_back(3);
  stl.push_back(1);
  stl.push_back(8);
  stl.sort();
  EXPECT_EQ(our.back(), stl.back());
  EXPECT_EQ(our.front(), stl.front());
}
TEST(list, sortString) {
  s21::list<std::string> our{"c", "b", "a", "h", "s"};
  std::list<std::string> stl{"c", "b", "a", "h", "s"};
  our.push_back("g");
  stl.push_back("g");
  our.sort();
  stl.sort();
  EXPECT_EQ(our.back(), stl.back());
  EXPECT_EQ(our.front(), stl.front());
}

TEST(list, reverse) {
  s21::list<std::string> our{"c", "b", "a", "h", "s"};
  std::list<std::string> stl{"c", "b", "a", "h", "s"};
  our.reverse();
  stl.reverse();
  EXPECT_EQ(our.back(), stl.back());
  EXPECT_EQ(our.front(), stl.front());
}
TEST(list, swap) {
  s21::list<std::string> our{"c", "b", "a", "h", "s"};
  s21::list<std::string> our1{"s", "h", "a", "b", "c"};
  std::list<std::string> stl{"c", "b", "a", "h", "s"};
  std::list<std::string> stl1{"s", "h", "a", "b", "c"};
  our.swap(our1);
  stl.swap(stl1);
  EXPECT_EQ(our.back(), stl.back());
  EXPECT_EQ(our.front(), stl.front());
}
TEST(list, swap_empty_first) {
  s21::list<std::string> our;
  s21::list<std::string> our1{"s", "h", "a", "b", "c"};
  std::list<std::string> stl;
  std::list<std::string> stl1{"s", "h", "a", "b", "c"};
  our.swap(our1);
  stl.swap(stl1);
  EXPECT_EQ(our.back(), stl.back());
  EXPECT_EQ(our.front(), stl.front());
}
TEST(list, swap_empty_second) {
  s21::list<std::string> our{"c", "b", "a", "h", "s"};
  s21::list<std::string> our1;
  std::list<std::string> stl{"c", "b", "a", "h", "s"};
  std::list<std::string> stl1;
  our.swap(our1);
  stl.swap(stl1);
  EXPECT_EQ(our.back(), "");
}
TEST(list, parametrized_const) {
  s21::list<std::string> our(6);
  EXPECT_EQ(our.back(), "");
  EXPECT_EQ(our.front(), "");
}
TEST(list, copy_const) {
  s21::list<std::string> our{"c", "b", "a", "h", "s"};
  s21::list<std::string> our1(our);
  EXPECT_EQ(our1.back(), "s");
  EXPECT_EQ(our1.front(), "c");
}

TEST(list, move_const) {
  s21::list<std::string> our{"c", "b", "a", "h", "s"};
  s21::list<std::string> our1(std::move(our));
  EXPECT_EQ(our1.back(), "s");
  EXPECT_EQ(our1.front(), "c");
}
TEST(list, max_size) {
  s21::list<std::string> our;
  std::list<std::string> stl;
  EXPECT_EQ(stl.max_size(), our.max_size());
}
TEST(list, defConstructor) {
  s21::list<int> our;
  std::list<int> stl;
  EXPECT_EQ(stl.front(), our.front());
}
TEST(list, moveConstructor) {
  s21::list<int> our{};
  s21::list<int> our1(std::move(our));
  EXPECT_EQ(our1.back(), 0);
}
TEST(list, emplace) {
  s21::list<int> our{1, 2, 7, 8, 9};
  auto it = our.begin();
  ++it;
  ++it;
  it = our.emplace(it, 4, 5, 6);
  EXPECT_EQ(*it, 6);
}
TEST(list, hard_test) {
  s21::list<int> list_empty_1;
  s21::list<int> list_empty_2;
  s21::list<int> list_1_1 = {1};
  s21::list<int> list_1_2 = {2};
  s21::list<int> list_few_1 = {2, 3, 7};
  s21::list<int> list_few_2 = {10000000, 2, 0, 4, 6, 8, 9, 10};
  list_few_2.reverse();
  EXPECT_EQ(list_few_2.front(), 10);
  EXPECT_EQ(list_few_2.back(), 10000000);
  list_few_2.sort();
  EXPECT_EQ(list_few_2.front(), 0);
  EXPECT_EQ(list_few_2.back(), 10000000);
  list_empty_1.merge(list_few_2);
  EXPECT_EQ(list_few_2.front(), 0);
  EXPECT_EQ(list_few_2.back(), 0);
  list_empty_1.pop_front();
  list_empty_1.push_back(90);
  auto it = list_empty_1.end();
  --it;
  list_empty_1.erase(it);
  EXPECT_EQ(list_empty_1.front(), 2);
  EXPECT_EQ(list_empty_1.back(), 10000000);
  list_empty_2.sort();
  list_empty_2.reverse();
  list_empty_2.unique();
  list_empty_2.clear();
  list_empty_2.push_back(1);
  list_empty_2.push_back(5);
  EXPECT_EQ(list_empty_2.front(), 1);
  EXPECT_EQ(list_empty_2.back(), 5);
  list_empty_2.clear();
  list_few_1.clear();
  list_few_2.clear();
  auto iter = list_few_1.begin();
  list_few_1.splice(iter, list_empty_2);
  EXPECT_EQ(list_few_1.front(), 0);
  EXPECT_EQ(list_few_1.back(), 0);
}
TEST(list, emplace_back) {
  s21::list<int> our{1, 2, 7, 8, 9};
  our.emplace_back(4, 5, 6);
  EXPECT_EQ(our.back(), 6);
}
TEST(list, emplace_front) {
  s21::list<int> our{1, 2, 7, 8, 9};
  our.emplace_front(4, 5, 6);
  EXPECT_EQ(our.front(), 6);
}
TEST(list, emplace_back_in_empty) {
  s21::list<int> our;
  our.emplace_back(4, 5, 6);
  EXPECT_EQ(our.back(), 6);
  EXPECT_EQ(our.front(), 4);
}
TEST(list, emplace_in_empty) {
  s21::list<int> our;
  our.emplace_front(4, 5, 6);
  EXPECT_EQ(our.front(), 6);
  EXPECT_EQ(our.back(), 4);
}
TEST(list, oper_move) {
  s21::list<int> our{1, 2, 3, 4};
  s21::list<int> our1;
  our1 = std::move(our);
  EXPECT_EQ(our1.front(), 1);
  EXPECT_EQ(our1.back(), 4);
}
TEST(list, swap_empty) {
  s21::list<int> our{1, 2, 3, 4};
  s21::list<int> our1;
  our1.swap(our);
  EXPECT_EQ(our1.front(), 1);
  EXPECT_EQ(our1.back(), 4);
}
