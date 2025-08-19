#include <iostream>

#include "stddef.h"

namespace s21 {
template <typename val_type>
class Node {
 public:
  val_type value;
  int height_left = 0;
  int height_right = 0;
  Node<val_type> *parent = nullptr;
  Node<val_type> *left = nullptr;
  Node<val_type> *right = nullptr;

  Node() = default;
  explicit Node(val_type data) { value = data; }
  ~Node() {
    parent = nullptr;
    left = nullptr;
    right = nullptr;
  }
};
}  // namespace s21

namespace s21 {

template <typename T>
class AVLTree {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  class ConstIterator {
   public:
    Node<value_type> *cursor = nullptr;
    ConstIterator() = default;
    ConstIterator(const ConstIterator &other) { cursor = other.cursor; }
    ~ConstIterator() = default;
    explicit ConstIterator(Node<value_type> *first) { cursor = first; }
    ConstIterator &operator=(ConstIterator const &other) {
      if (this != &other) {
        cursor = other.cursor;
      }
      return *this;
    }

    ConstIterator &operator++() {
      cursor = StepPlus(cursor);
      return *this;
    }

    ConstIterator &operator--() {
      cursor = StepMinus(cursor);
      return *this;
    }

    const_reference operator*() { return this->cursor->value; }

    bool operator==(ConstIterator other) {
      return *this->cursor == other.cursor;
    }

    bool operator!=(ConstIterator other) {
      return this->cursor != other.cursor;
    }

   private:
    Node<T> *StepPlus(Node<T> *tmp) {
      if (tmp->right) {
        tmp = DiveIn(tmp->right);
      } else {
        tmp = DiveOut(tmp);
      }
      return tmp;
    }

    Node<T> *DiveIn(Node<T> *tmp) {
      if (tmp->left) {
        tmp = DiveIn(tmp->left);
      }
      return tmp;
    }

    Node<T> *DiveOut(Node<T> *tmp) {
      if (tmp->parent->left != tmp) {
        return DiveOut(tmp->parent);
      }
      return tmp->parent;
    }

    Node<T> *StepMinus(Node<T> *tmp) {
      if (tmp->left) {
        tmp = DiveInMinus(tmp->left);
      } else {
        tmp = DiveOutMinus(tmp);
      }
      return tmp;
    }

    Node<T> *DiveInMinus(Node<T> *tmp) {
      if (tmp->right) {
        tmp = DiveInMinus(tmp->right);
      }
      return tmp;
    }

    Node<T> *DiveOutMinus(Node<T> *tmp) {
      if (tmp->parent->right != tmp) {
        return DiveOutMinus(tmp->parent);
      }
      return tmp->parent;
    }
  };

  class Iterator : public ConstIterator {
   public:
    Iterator() : ConstIterator() {}
    explicit Iterator(Node<value_type> *first) : ConstIterator(first) {}
    explicit Iterator(Node<value_type> &other) : ConstIterator(other) {}
    reference operator*() { return this->cursor->value; }
  };

  AVLTree() = default;
  ~AVLTree() = default;

 protected:
  Node<T> *end_ = new Node<T>();
  Node<T> *begin_ = nullptr;
  Node<T> *root = nullptr;

  s21::Node<T> *Search(s21::Node<T> *target_node, s21::Node<T> *elem) {
    if (target_node->value > elem->value) {
      target_node = StepLeft(target_node, elem);
      target_node->height_left = 1 + std::max(target_node->left->height_left,
                                              target_node->left->height_right);
    } else {
      target_node = StepRight(target_node, elem);
      target_node->height_right =
          1 + std::max(target_node->right->height_left,
                       target_node->right->height_right);
    }
    target_node = Balance(target_node);
    return target_node;
  }

  s21::Node<T> *SearchMultiset(s21::Node<T> *target_node, s21::Node<T> *elem) {
    if (target_node->value >= elem->value) {
      target_node = StepLeft(target_node, elem);
      target_node->height_left = 1 + std::max(target_node->left->height_left,
                                              target_node->left->height_right);
    } else {
      target_node = StepRight(target_node, elem);
      target_node->height_right =
          1 + std::max(target_node->right->height_left,
                       target_node->right->height_right);
    }
    target_node = Balance(target_node);
    return target_node;
  }

  s21::Node<T> *Balance(s21::Node<T> *target_node) {
    if (abs(target_node->height_left - target_node->height_right) >= 2) {
      if (target_node->height_left > target_node->height_right) {
        if (target_node->left &&
            target_node->left->height_right > target_node->left->height_left) {
          target_node = BigTurnRight(target_node);
        } else {
          target_node = TurnRight(target_node);
        }
      } else {
        if (target_node->right && target_node->right->height_left >
                                      target_node->right->height_right) {
          target_node = BigTurnLeft(target_node);
        } else {
          target_node = TurnLeft(target_node);
        }
      }
    }
    return target_node;
  }

  void InsertMap(s21::Node<T> *inserted_val) {
    if (root == nullptr) {
      root = inserted_val;
      begin_ = inserted_val;
      inserted_val->right = end_;
      end_->parent = inserted_val;
    } else {
      root = Search(root, inserted_val);
    }
  }

  void InsertMultiset(s21::Node<T> *inserted_val) {
    if (root == nullptr) {
      root = inserted_val;
      begin_ = inserted_val;
      inserted_val->right = end_;
      end_->parent = inserted_val;
    } else {
      root = SearchMultiset(root, inserted_val);
    }
  }

  Node<T> *EraseElem(Node<T> *elem, Node<T> *target) {
    if (target->value < elem->value) {
      if (target->right) {
        target->right = EraseElem(elem, target->right);
        if (target->right) {
          target->right->parent = target;
          if (target->right == end_) {
            target->height_right = 0;
          }
        }
      }
    } else if (target->value > elem->value) {
      if (target->left) {
        target->left = EraseElem(elem, target->left);
        if (target->left) {
          target->left->parent = target;
        }
      }
    } else {
      if (target->right) {
        if (!target->right->left) {
          Node<T> *tmp = target->right;
          if (tmp->left) {
            tmp->left = target->left;
            target->left->parent = tmp;
          }
          delete target;
          return tmp;
        }
        Node<T> *tmp = StartErase(target->right, &(target->right));
        tmp->left = target->left;
        tmp->right = target->right;
        tmp->parent = target->parent;
        if (target->left) {
          target->left->parent = tmp;
        }
        if (target->right) {
          target->right->parent = tmp;
        }
        delete target;
        if (tmp->left) {
          tmp->height_left =
              std::max(tmp->left->height_left, tmp->left->height_right) + 1;
        }
        if (tmp->right) {
          tmp->height_right =
              std::max(tmp->right->height_left, tmp->right->height_right) + 1;
        }
        return Balance(tmp);
      } else if (target->left) {
        Node<T> *tmp = target->left;
        delete target;
        return tmp;
      } else {
        if (target == begin_) {
          if (target->parent) {
            begin_ = target->parent;
          } else {
            begin_ = nullptr;
          }
        }
        delete target;
        return nullptr;
      }
    }
    return Balance(target);
  }

  Node<T> *StartErase(Node<T> *root, Node<T> **target) {
    if (!root->left) {
      if (root->right) {
        root->parent->left = root->right;
        root->right->parent = root->parent;
      } else {
        root->parent->left = nullptr;
      }
      return root;
    }
    Node<T> *tmp = StartErase(root->left, &(root->left));
    if (root->left) {
      root->height_left =
          std::max(root->left->height_left, root->left->height_right) + 1;
    } else {
      root->height_left = 0;
    }
    if (root->right) {
      root->height_right =
          std::max(root->right->height_left, root->right->height_right) + 1;
    } else {
      root->height_right = 0;
    }
    *target = Balance(root);
    return tmp;
  }

  void Clear(s21::Node<T> *target_root) {
    if (!target_root) {
      delete end_;
      return;
    }
    if (target_root->left) {
      Clear(target_root->left);
    }
    if (target_root->right) {
      Clear(target_root->right);
    }
    delete target_root;
  }

  s21::Node<T> *At(s21::Node<T> *target, T &val) {
    auto result = target;
    if (target->left && target->value > val) {
      result = At(target->left, val);
    } else if (target->right && target->value < val) {
      result = At(target->right, val);
    } else {
      result = target;
    }
    return result;
  }

 private:
  s21::Node<T> *TurnRight(s21::Node<T> *current) {
    s21::Node<T> *tmp = current->left;
    current->left = tmp->right;
    if (current->left) {
      current->left->parent = current;
      current->height_left =
          std::max(current->left->height_left, current->left->height_right) + 1;
    } else {
      current->height_left = 0;
    }
    tmp->right = current;
    current->parent = tmp;
    tmp->height_right =
        std::max(current->height_right, current->height_left) + 1;
    return tmp;
  }

  s21::Node<T> *TurnLeft(s21::Node<T> *current) {
    s21::Node<T> *tmp = current->right;
    current->right = tmp->left;
    if (current->right) {
      current->right->parent = current;
      current->height_right =
          std::max(current->right->height_left, current->right->height_right) +
          1;
    } else {
      current->height_right = 0;
    }
    tmp->left = current;
    current->parent = tmp;
    tmp->height_left =
        std::max(current->height_right, current->height_left) + 1;
    return tmp;
  }

  s21::Node<T> *BigTurnLeft(s21::Node<T> *current) {
    //    auto tmp = current;
    current->right = TurnRight(current->right);
    current->right->parent = current;
    auto tmp = TurnLeft(current);
    return tmp;
  }

  s21::Node<T> *BigTurnRight(s21::Node<T> *current) {
    //    auto tmp = current;
    current->left = TurnLeft(current->left);
    current->left->parent = current;
    auto tmp = TurnRight(current);
    return tmp;
  }

  s21::Node<T> *StepLeft(s21::Node<T> *target_node, s21::Node<T> *elem) {
    if (!target_node->left) {
      target_node->left = elem;
      elem->parent = target_node;
      if (target_node == begin_) {
        begin_ = elem;
      }
    } else {
      target_node->left = Search(target_node->left, elem);
      target_node->left->parent = target_node;
    }
    return target_node;
  }

  s21::Node<T> *StepRight(s21::Node<T> *target_node, s21::Node<T> *elem) {
    if (!target_node->right) {
      target_node->right = elem;
      elem->parent = target_node;
    } else if (target_node->right == end_) {
      target_node->right = elem;
      elem->parent = target_node;
      elem->right = end_;
      end_->parent = elem;
    } else {
      target_node->right = Search(target_node->right, elem);
      target_node->right->parent = target_node;
    }
    return target_node;
  }
};

}  // namespace s21