#ifndef CPP2_S21_CONTAINERS_1_SRC_QUEUE_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_1_SRC_QUEUE_S21_QUEUE_H_

#include <stddef.h>

#include <iostream>
#include <queue>

namespace s21 {
template <typename T>
class queue {
 private:
  class ListNode {
   public:
    T value = T();
    ListNode *next = nullptr;
    ListNode() = default;
    explicit ListNode(T value_) { value = value_; }
    ~ListNode() = default;
  };

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  // size_type amount_of_nodes = 0;

 private:
  ListNode *head = nullptr;
  ListNode *tail = nullptr;
  size_type amount_of_nodes = 0;

 public:
  queue() = default;

  queue(const std::initializer_list<value_type> &items) {
    if (items.size() != 0) {
      for (auto elems : items) {
        push(elems);
      }
    }
  }
  queue(const queue<value_type> &s) {
    if (s.empty()) {
      throw std::out_of_range("Cant copy empty queue in constructor of copy");
    }
    ListNode *buf_other = s.head;
    while (buf_other != nullptr) {
      push(buf_other->value);
      buf_other = buf_other->next;
    }
    amount_of_nodes = s.amount_of_nodes;
  }

  queue(queue<value_type> &&s) noexcept {
    if (this != &s) {
      head = s.head;
      tail = s.tail;
      s.head = nullptr;
      s.tail = nullptr;
      amount_of_nodes = s.amount_of_nodes;
      s.amount_of_nodes = 0;
    }
  }

  queue<value_type> &operator=(queue<value_type> &&s) noexcept {
    if (this != &s) {
      if (amount_of_nodes > 0) {
        clear();
      }
      head = s.head;
      tail = s.tail;
      s.head = nullptr;
      s.tail = nullptr;
      amount_of_nodes = s.amount_of_nodes;
      s.amount_of_nodes = 0;
    }
    return *this;
  }

  ~queue() { clear(); };

  bool empty() const noexcept {
    if (amount_of_nodes > 0) {
      return false;
    }
    return true;
  }
  void clear() {
    while (amount_of_nodes != 0) {
      if (tail != nullptr) {
        pop();
      } else {
        throw std::logic_error(
            "Cant clear queue, amount_of_nodes not equal of real nodes");
      }
    }
  }

  void push(T data) {
    auto *tmp = new ListNode(data);
    if (tail == nullptr) {
      head = tmp;
      tail = tmp;

    } else {
      tail->next = tmp;
      tail = tmp;
    }
    amount_of_nodes++;
  }

  void pop() {
    if (amount_of_nodes == 0) {
      throw std::out_of_range("Cant pop node from empty queue in pop function");
    }
    ListNode *buf = head->next;
    if (head != nullptr) {
      delete head;
    }
    head = buf;
    amount_of_nodes--;
  }

  const_reference front() { return head->value; }
  const_reference back() { return tail->value; }

  size_type size() const noexcept { return amount_of_nodes; }

  void swap(queue<value_type> &s) {
    std::swap(head, s.head);
    std::swap(tail, s.tail);
    std::swap(amount_of_nodes, s.amount_of_nodes);
  }

  template <typename... Args>
  void emplace_back(Args &&...args) {
    ([&] { push(args); }(), ...);
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_QUEUE_S21_QUEUE_H_