#ifndef CPP2_S21_CONTAINERS_1_SRC_MULTISET_S21_MULTISET_H_
#define CPP2_S21_CONTAINERS_1_SRC_MULTISET_S21_MULTISET_H_

#include <stddef.h>

#include <utility>
#include <vector>

#include "../AVLTree/s21_avltree.h"

namespace s21 {
template <typename Key>
class multiset : public s21::AVLTree<Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using iterator = typename AVLTree<value_type>::Iterator;
  using const_iterator = typename AVLTree<value_type>::ConstIterator;

  multiset() = default;
  multiset(std::initializer_list<value_type> const &items) {
    for (auto &el : items) {
      insert(el);
    }
  }

  multiset(const multiset &other) {
    this->root = RecursiveCopy(other.root);
    this->root->value = other.root->value;
    this->root->height_right = other.root->height_right;
    this->root->height_left = other.root->height_left;
    auto tmp = this->root;
    while (tmp->left) {
      tmp = tmp->left;
    }
    this->begin_ = tmp;
    tmp = this->root;
    while (tmp->right) {
      tmp = tmp->right;
    }
    delete this->end_;
    this->end_ = tmp;
  }

  multiset(multiset &&m) noexcept {
    this->root = std::exchange(m.root, nullptr);
    this->begin_ = std::exchange(m.begin_, nullptr);
    delete this->end_;
    this->end_ = std::exchange(m.end_, nullptr);
    Size = std::exchange(m.Size, 0);
  }

  ~multiset() { this->Clear(this->root); }

  multiset &operator=(multiset &&m) noexcept {
    if (this != &m) {
      this->Clear(this->root);
      this->root = std::exchange(m.root, nullptr);
      this->begin_ = std::exchange(m.begin_, nullptr);
      this->end_ = std::exchange(m.end_, nullptr);
      Size = std::exchange(m.Size, 0);
    }
    return *this;
  }

  iterator begin() { return iterator(this->begin_); };
  iterator end() { return iterator(this->end_); };

  size_type size() { return Size; }
  void erase(iterator pos) {
    if (Size != 0) {
      this->EraseElem(pos.cursor, this->root);
      Size--;
    }
  }

  size_type max_size() { return (size_t(-1) / sizeof(multiset<Key>)); }

  iterator insert(const value_type &value) {
    auto *elem = new Node<value_type>(value);
    iterator it = iterator(elem);
    this->InsertMultiset(elem);
    Size++;
    return it;
  }

  bool contains(const Key &key) { return SearchContains(this->root, key); }
  bool empty() {
    if (Size == 0) {
      return true;
    }
    return false;
  }

  void merge(multiset &other) {
    if (this != &other) {
      for (auto it = other.begin(); it != other.end(); ++it) {
        insert(it.cursor->value);
      }
    }
  }

  void swap(multiset &other) {
    if (this != &other) {
      std::swap(this->root, other.root);
      std::swap(this->begin_, other.begin_);
      std::swap(this->end_, other.end_);
      std::swap(this->Size, other.Size);
    }
  }

  iterator find(const Key &key) {
    auto tmp = this->At(this->root, key);
    if (tmp->value != key) {
      tmp = this->end_;
    }
    return iterator(tmp);
  }

  std::pair<iterator, iterator> equal_range(const Key &key) {
    iterator start;
    iterator finish;
    bool check = false;
    for (auto it = iterator(this->begin_); it != iterator(this->end_); ++it) {
      if (check && *it == key) {
        finish = it;
      }
      if (!check && *it == key) {
        start = it;
        check = true;
      }
    }
    return std::pair<iterator, iterator>(start, finish);
  }

  iterator lower_bound(const Key &key) {
    auto target = iterator(FindNode(key));
    if (*target != key) {
      while (*target < key && target != end()) {
        ++target;
      }
    } else {
      while (*target >= key && target != end()) {
        --target;
      }
      ++target;
    }
    return target;
  }

  iterator upper_bound(const Key &key) {
    auto target = iterator(FindNode(key));
    while (*target <= key && target != end()) {
      ++target;
    }
    return target;
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> emplace(Args &&...args) {
    std::vector<std::pair<iterator, bool>> result;
    for (auto element : {std::forward<Args>(args)...}) {
      result.push_back(std::pair<iterator, bool>(insert(element), true));
    }
    return result;
  }

 private:
  size_type Size = 0;

  Node<value_type> *FindNode(const Key &key) {
    auto tmp = this->root;
    while (tmp) {
      if (tmp->value >= key) {
        if (tmp->left) {
          tmp = tmp->left;
        } else {
          return tmp;
        }
      } else {
        if (tmp->right) {
          tmp = tmp->right;
        } else {
          return tmp;
        }
      }
    }
    return this->end_;
  }

  Node<value_type> *RecursiveCopy(Node<value_type> *target) {
    auto *new_obj = new Node<value_type>();
    new_obj->value = target->value;
    new_obj->height_left = target->height_left;
    new_obj->height_right = target->height_right;
    if (target->left) {
      new_obj->left = RecursiveCopy(target->left);
      new_obj->left->parent = new_obj;
    }
    if (target->right) {
      new_obj->right = RecursiveCopy(target->right);
      new_obj->right->parent = new_obj;
    }
    return new_obj;
  }

  bool SearchContains(Node<value_type> *target, const Key &key) {
    if (target && target->value > key) {
      if (target->left) {
        return SearchContains(target->left, key);
      } else {
        return false;
      }
    } else if (target && target->value < key) {
      if (target->right) {
        return SearchContains(target->right, key);
      } else {
        return false;
      }
    } else if (!target) {
      return false;
    } else {
      return true;
    }
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_MULTISET_S21_MULTISET_H_