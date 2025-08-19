#ifndef CPP2_S21_CONTAINERS_1_SRC_MAP_S21_MAP_H_
#define CPP2_S21_CONTAINERS_1_SRC_MAP_S21_MAP_H_

#include <stddef.h>

#include <utility>
#include <vector>

#include "../AVLTree/s21_avltree.h"

namespace s21 {
template <typename Key, typename T>
class map : public s21::AVLTree<std::pair<Key, T>> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using iterator = typename AVLTree<value_type>::Iterator;
  using const_iterator = typename AVLTree<value_type>::ConstIterator;

  map() = default;
  map(std::initializer_list<value_type> const &items) {
    for (auto &el : items) {
      insert(el);
    }
  }

  map(const map &other) {
    this->root = RecursiveCopy(other.root);
    this->root->value = other.root->value;
    this->root->height_right = other.root->height_right;
    this->root->height_left = other.root->height_left;
    auto tmp = this->root;
    while (tmp->left) {
      tmp = tmp->left;
    }
    this->begin_ = tmp;
    auto tmp2 = this->root;
    while (tmp2->right) {
      tmp2 = tmp2->right;
    }
    delete this->end_;
    this->end_ = tmp2;
  }

  map(map &&m) noexcept {
    this->root = std::exchange(m.root, nullptr);
    this->begin_ = std::exchange(m.begin_, nullptr);
    delete this->end_;
    this->end_ = std::exchange(m.end_, nullptr);
    Size = std::exchange(m.Size, 0);
  }

  ~map() { this->Clear(this->root); }

  map &operator=(map &&m) noexcept {
    if (this != &m) {
      this->Clear(this->root);
      this->root = std::exchange(m.root, nullptr);
      this->begin_ = std::exchange(m.begin_, nullptr);
      this->end_ = std::exchange(m.end_, nullptr);
      Size = std::exchange(m.Size, 0);
    }
    return *this;
  }
  T &operator[](const Key &key) {
    if (contains(key)) {
      return at(key);
    } else {
      auto tmp = std::pair<Key, T>();
      tmp.first = key;
      auto res = insert(tmp);
      return res.first.cursor->value.second;
    }
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

  size_type max_size() { return (size_t(-1) / sizeof(map<Key, T>)); }

  std::pair<iterator, bool> insert(const value_type &value) {
    iterator it;
    bool result = false;
    if (!contains(value.first)) {
      auto *elem = new Node<value_type>(value);
      it = iterator(elem);
      this->InsertMap(elem);
      result = true;
      Size++;
    }
    return std::pair<iterator, bool>(it, result);
  }

  std::pair<iterator, bool> insert(const Key &key, const T &obj) {
    std::pair<Key, T> value(key, obj);
    return map<Key, T>::insert(value);
  }

  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj) {
    std::pair<iterator, bool> result;
    if (contains(key)) {
      this->operator[](key) = obj;
      result.first = iterator(tmp_at(this->root, key));
      result.second = false;
    } else {
      result = insert(std::pair<Key, T>(key, obj));
    }
    return result;
  }

  T &at(const Key &key) {
    auto result = tmp_at(this->root, key);
    return result->value.second;
  }

  bool contains(const Key &key) { return search_contains(this->root, key); }
  bool empty() {
    if (Size == 0) {
      return true;
    }
    return false;
  }

  void merge(map &other) {
    if (this != &other) {
      for (auto it = other.begin(); it != other.end(); ++it) {
        insert(it.cursor->value);
      }
    }
  }

  void swap(map &other) {
    if (this != &other) {
      std::swap(this->root, other.root);
      std::swap(this->begin_, other.begin_);
      std::swap(this->end_, other.end_);
      std::swap(this->Size, other.Size);
    }
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> emplace(Args &&...args) {
    std::vector<std::pair<iterator, bool>> result;
    for (auto element : {std::forward<Args>(args)...}) {
      result.push_back(insert(element));
    }
    return result;
  }

 private:
  size_type Size = 0;

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

  s21::Node<value_type> *tmp_at(Node<value_type> *target, Key key) {
    auto result = target;
    if (target->left && target->value.first > key) {
      result = tmp_at(target->left, key);
    } else if (target->right && target->value.first < key) {
      result = tmp_at(target->right, key);
    } else {
      result = target;
    }
    return result;
  }

  bool search_contains(Node<value_type> *target, const Key &key) {
    if (target && target->value.first > key) {
      if (target->left) {
        return search_contains(target->left, key);
      } else {
        return false;
      }
    } else if (target && target->value.first < key) {
      if (target->right) {
        return search_contains(target->right, key);
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

#endif  // CPP2_S21_CONTAINERS_1_SRC_MAP_S21_MAP_H_