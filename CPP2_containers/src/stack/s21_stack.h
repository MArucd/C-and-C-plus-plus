#ifndef CPP2_S21_CONTAINERS_1_SRC_STACK_S21_STACK_H_
#define CPP2_S21_CONTAINERS_1_SRC_STACK_S21_STACK_H_

#include <stddef.h>

#include <iostream>
#include <stack>

namespace s21 {
template <typename T>
class stack {
 private:
  class ListNode {
   public:
    T value = T();
    ListNode *next = nullptr;
    ListNode() = default;
    ListNode(T value_) { value = value_; }
    ~ListNode() = default;
  };

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 private:
  size_type amount_of_nodes = 0;
  ListNode *head = nullptr;

 public:
  stack() {
    head = nullptr;
    amount_of_nodes = 0;
  };

  stack(std::initializer_list<value_type> const &items) {
    if (items.size() != 0) {
      for (auto elems : items) {
        push(elems);
      }
    }
  }
  stack(const stack<value_type> &s) {
    if (s.empty()) {
      throw std::out_of_range("Cant copy empty stack in constructor of copy");
    }
    ListNode *buf_other = s.head;
    buf_other = buf_other->next;
    head = new ListNode(s.head->value);
    ListNode *buf_this = head;
    while (buf_other != nullptr) {
      buf_this->next = new ListNode(buf_other->value);
      buf_this = buf_this->next;
      buf_other = buf_other->next;
    }
    amount_of_nodes = s.amount_of_nodes;
  }

  stack(stack<value_type> &&s) noexcept {
    if (this != &s) {
      head = s.head;
      s.head = nullptr;
      amount_of_nodes = s.amount_of_nodes;
      s.amount_of_nodes = 0;
    }
  }

  stack<value_type> &operator=(stack<value_type> &&s) noexcept {
    if (this != &s) {
      if (amount_of_nodes > 0) {
        clear();
      }
      head = s.head;
      s.head = nullptr;
      amount_of_nodes = s.amount_of_nodes;
      s.amount_of_nodes = 0;
    }
    return *this;
  }

  ~stack() { clear(); };

  bool empty() const noexcept {
    if (amount_of_nodes > 0) {
      return false;
    }
    return true;
  }
  void clear() {
    while (amount_of_nodes > 0) {
      if (head != nullptr) {
        pop();
      }
    }
  }

  void push(T data) {
    auto *tmp = new ListNode(data);
    if (head == nullptr) {
      head = tmp;
    } else {
      tmp->next = head;
      head = tmp;
    }
    amount_of_nodes++;
  }

  void pop() {
    if (amount_of_nodes == 0) {
      throw std::out_of_range("Cant pop node from empty stack in pop function");
    }
    ListNode *buf = head->next;
    if (head != nullptr) {
      delete head;
      head = nullptr;
    }
    head = buf;
    amount_of_nodes--;
  }

  const_reference top() const { return head->value; }

  size_type size() const { return amount_of_nodes; }

  void swap(stack<value_type> &s) {
    std::swap(head, s.head);
    value_type buf = amount_of_nodes;
    amount_of_nodes = s.amount_of_nodes;
    s.amount_of_nodes = buf;
  }
  template <typename... Args>
  void emplace_front(Args &&...args) {
    ([&] { push(args); }(), ...);
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_STACK_S21_STACK_H_