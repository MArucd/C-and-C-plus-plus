#include <cstddef>
#include <iostream>
#include <limits>
#include <list>
namespace s21 {
template <typename T>
class list {
 private:
  struct ListNode {
   public:
    T value = T();
    ListNode *next = nullptr;
    ListNode *prev = nullptr;
    ListNode() = default;
    ListNode(T value_, ListNode *prev_, ListNode *next_) {
      value = value_;
      next = next_;
      prev = prev_;
    }
    ~ListNode() = default;
  };
  class ListConstIterator {
   public:
    explicit ListConstIterator(ListNode *first) { cursor = first; }
    ListConstIterator() { cursor = nullptr; }
    ListConstIterator(const ListConstIterator &other) { cursor = other.cursor; }
    ListConstIterator(ListConstIterator &&other) noexcept {
      cursor = std::exchange(other.cursor, nullptr);
      cursor->value = std::exchange(other.cursor->value, 0);
    }
    ~ListConstIterator() = default;
    ListConstIterator &operator=(const ListConstIterator &other) {
      if (this != &other) {
        cursor = other.cursor;
      }
      return *this;
    }
    const T &operator*() const { return cursor->value; }
    ListConstIterator &operator++() {
      if (cursor->next != nullptr) {
        cursor = cursor->next;
      }
      return *this;
    }
    ListConstIterator &operator--() {
      if (cursor->prev != nullptr) {
        cursor = cursor->prev;
      }
      return *this;
    }
    bool operator==(ListConstIterator &other) { return cursor == other.cursor; }
    bool operator!=(ListConstIterator &other) { return cursor != other.cursor; }

    ListNode *cursor = nullptr;
  };
  class ListIterator : public ListConstIterator {
   public:
    ListIterator() : ListConstIterator() {}
    ListIterator(ListNode *first) : ListConstIterator(first) {}
    ListIterator(ListConstIterator &other) : ListConstIterator(other) {}
    T &operator*() { return this->cursor->value; }
  };

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

 public:
  list() {
    head = tail = nullptr;
    end_ = new ListNode;
  }
  list(std::initializer_list<value_type> const &items) {
    if (items.size() != 0) {
      end_ = new ListNode;
      for (value_type n : items) {
        push_back(n);
      }
    }
  }
  list(size_type n) {
    end_ = new ListNode;
    for (size_type i = 0; i < n; i++) {
      push_back(T());
    };
  }
  list(const list &l) {
    end_ = new ListNode;
    auto it = l.begin();
    clear();
    while (it.cursor != l.end_) {
      push_back(*it);
      ++it;
    }
  }
  list(list &&l) noexcept {
    head = std::exchange(l.head, nullptr);
    tail = std::exchange(l.tail, nullptr);
    end_ = std::exchange(l.end_, nullptr);
    Size = std::exchange(l.Size, 0);
  }
  ~list() {
    if (!empty()) clear();
    PopEnd();
  }
  list &operator=(list &&l) noexcept {
    if (this != &l) {
      clear();
      PopEnd();
      head = std::exchange(l.head, nullptr);
      tail = std::exchange(l.tail, nullptr);
      end_ = std::exchange(l.end_, nullptr);
      Size = std::exchange(l.Size, 0);
    }
    return *this;
  }
  iterator begin() const {
    return Size == 0 ? iterator(end_) : iterator(head);
  };
  iterator end() const { return iterator(end_); }
  const_reference back() {
    if (Size == 0) {
      return end_->value;
    } else if (Size == 1) {
      return head->value;
    } else {
      return tail->value;
    }
  }
  const_reference front() {
    if (Size == 0) {
      return end_->value;
    } else {
      return head->value;
    }
  }
  bool empty() const noexcept { return Size == 0; }
  size_type max_size() const noexcept {
    return (std::numeric_limits<size_type>::max() / sizeof(ListNode) / 2);
  }
  size_type size() const noexcept { return Size; }
  void push_back(const_reference value) {
    auto *tmp = new ListNode(value, nullptr, nullptr);
    if (head == nullptr) {
      head = tmp;
      head->next = end_;
      head->prev = end_;
      end_->prev = head;
      end_->next = head;
    } else if (tail == nullptr) {
      tail = tmp;
      tail->next = end_;
      tail->prev = head;
      head->next = tail;
      end_->prev = tail;
    } else {
      tail->next = tmp;
      tmp->prev = tail;
      tail = tmp;
      tail->next = end_;
      end_->prev = tail;
    }
    Size++;
    end_->value = Size;
  }
  void push_front(const_reference value) {
    auto *tmp = new ListNode(value, nullptr, nullptr);
    if (head == nullptr) {
      head = tmp;
      head->next = end_;
      head->prev = end_;
      end_->prev = head;
      end_->next = head;
    } else if (tail == nullptr) {
      tail = head;
      tail->prev = tmp;
      tmp->next = tail;
      head = tmp;
      head->prev = end_;
    } else {
      tmp->next = head;
      head->prev = tmp;
      head = tmp;
      head->prev = end_;
      end_->next = head;
    }
    Size++;
    end_->value = Size;
  }
  void pop_front() {
    if (Size > 0) {
      if (Size == 1) {
        delete head;
        head = nullptr;
      } else {
        auto *tmp = head;
        head = head->next;
        delete tmp;
      }
      Size--;
      end_->value = Size;
    }
  }
  void pop_back() {
    if (Size > 0) {
      if (Size == 1) {
        delete head;
        head = nullptr;
      } else {
        auto *tmp = tail;
        tail = tail->prev;
        delete tmp;
      }
      Size--;
      end_->value = Size;
    }
  }
  void clear() noexcept {
    while (Size) {
      pop_back();
    }
  }
  iterator insert(iterator pos, const_reference value) {
    if (pos.cursor == nullptr) {
      throw std::logic_error("Invalid position");
    }
    if (pos.cursor == head) {
      push_front(value);
      end_->value = Size;
      return iterator(head);
    } else if (pos.cursor == end_) {
      push_back(value);
      end_->value = Size;
      return tail == nullptr ? iterator(head) : iterator(tail);
    } else {
      auto *tmp = new ListNode(value, nullptr, nullptr);
      tmp->next = pos.cursor;
      tmp->prev = pos.cursor->prev;
      pos.cursor->prev->next = tmp;
      pos.cursor->prev = tmp;
      tmp->value = value;
      Size++;
      end_->value = Size;
      return iterator(tmp);
    }
  }
  void erase(iterator pos) {
    if (pos.cursor == nullptr || pos.cursor == end_) {
      throw std::logic_error("Invalid position");
    }
    if (pos.cursor == head) {
      pop_front();
      end_->value = Size;
      if (Size == 0) {
        head = nullptr;
      }
    } else if (pos.cursor == tail) {
      pop_back();
      end_->value = Size;
    } else {
      pos.cursor->prev->next = pos.cursor->next;
      pos.cursor->next->prev = pos.cursor->prev;
      delete pos.cursor;
      Size--;
      end_->value = Size;
    }
  }
  void sort() {
    if (Size != 0) {
      head->prev = nullptr;
      tail->next = nullptr;
      MergeSort(&head);
      head->prev = end_;
      ListNode *tmp_back = head;
      while (tmp_back->next) {
        tmp_back = tmp_back->next;
      }
      tail = tmp_back;
      tail->next = end_;
    }
  }

  void merge(list &other) {
    if (this != &other) {
      auto it(begin());
      while (other.Size > 0) {
        if (*it >= other.head->value || it.cursor == end_) {
          it = (insert(it, other.head->value));
          other.pop_front();
          ++it;
        } else {
          ++it;
        }
      }
    }
  }
  void splice(const_iterator pos, list &other) {
    if (this != &other) {
      while (other.Size > 0) {
        insert(pos, other.head->value);
        other.pop_front();
      }
    }
  }
  void unique() {
    if (!empty()) {
      auto it(begin());
      ++it;
      while (it.cursor != end_) {
        if (*it == it.cursor->prev->value) {
          it = EraseForUnique(it);
        } else {
          ++it;
        }
      }
    }
  }
  void reverse() {
    if (!empty() && Size != 1) {
      std::swap(tail, head);
      std::swap(end_->prev, end_->next);
      auto it = begin();
      while (it.cursor != end_) {
        std::swap(it.cursor->next, it.cursor->prev);
        ++it;
      }
    }
  }
  void swap(list &other) {
    if (this != &other && (!empty() || !other.empty())) {
      std::swap(head, other.head);
      std::swap(tail, other.tail);
      std::swap(end_, other.end_);
      std::swap(Size, other.Size);
    }
  }

  template <typename... Args>
  void emplace_back(Args &&...args) {
    for (auto element : {std::forward<Args>(args)...}) {
      push_back(element);
    }
  }

  template <typename... Args>
  void emplace_front(Args &&...args) {
    for (auto element : {std::forward<Args>(args)...}) {
      push_front(element);
    }
  }

  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args) {
    iterator it(pos);
    for (auto element : {std::forward<Args>(args)...}) {
      insert(it, element);
    }
    return --it;
  }

 private:
  void Split(ListNode *tmp, ListNode **a, ListNode **b) {
    ListNode *slow = tmp;
    ListNode *fast = tmp->next;
    while (fast != nullptr) {
      fast = fast->next;
      if (fast != nullptr) {
        slow = slow->next;
        fast = fast->next;
      }
    }
    *a = tmp;
    *b = slow->next;
    slow->next = nullptr;
  }
  void PopEnd() { delete end_; }
  void MergeSort(ListNode **tmp) {
    if (*tmp == nullptr || (*tmp)->next == nullptr) {
      return;
    }
    ListNode *a = nullptr;
    ListNode *b = nullptr;
    Split(*tmp, &a, &b);
    MergeSort(&a);
    MergeSort(&b);
    *tmp = MergeForSort(a, b);
  }
  ListNode *MergeForSort(ListNode *a, ListNode *b) {
    ListNode *tmp = nullptr;
    if (a == nullptr) {
      return b;
    } else if (b == nullptr) {
      return a;
    }
    if (a->value <= b->value) {
      tmp = a;
      tmp->next = MergeForSort(a->next, b);
      tmp->next->prev = tmp;
      tmp->prev = nullptr;
      return tmp;
    }

    tmp = b;
    tmp->next = MergeForSort(a, b->next);
    tmp->next->prev = tmp;
    tmp->prev = nullptr;
    return tmp;
  }
  iterator EraseForUnique(iterator pos) {
    if (pos.cursor == nullptr || pos.cursor == end_) {
      throw std::logic_error("Invalid position");
    }
    if (pos.cursor == head) {
      pop_front();
      end_->value = Size;
      if (Size == 0) {
        head = nullptr;
      }
      return Size == 0 ? iterator(end_) : iterator(head);
    } else if (pos.cursor == tail) {
      pop_back();
      end_->value = Size;
      return iterator(end_);
    }
    pos.cursor->prev->next = pos.cursor->next;
    pos.cursor->next->prev = pos.cursor->prev;
    auto *tmp = pos.cursor->next;
    delete pos.cursor;
    Size--;
    end_->value = Size;
    return iterator(tmp);
  }

  size_type Size = 0;
  ListNode *head = nullptr;
  ListNode *tail = nullptr;
  ListNode *end_ = nullptr;
};
}  // namespace s21