#ifndef CPP2_S21_CONTAINERS_1_SRC_VECTOR_S21_VECTOR_H_
#define CPP2_S21_CONTAINERS_1_SRC_VECTOR_S21_VECTOR_H_

#include <stddef.h>

#include <exception>
#include <iterator>
#include <limits>
#include <utility>

namespace s21 {
template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  vector() noexcept : values(nullptr), capacity_(0), size_(0){};
  vector(size_type n) {
    values = new T[n]{};
    size_ = n;
    capacity_ = n;
  };
  vector(std::initializer_list<value_type> const &items)
      : capacity_(0), size_(0) {
    values = new T[items.size()]{};
    size_ = items.size();
    capacity_ = items.size();
    size_type i = 0;
    for (auto element : items) values[i++] = element;
  };
  vector(const vector &v) {
    values = new T[v.size_];
    for (size_type i = 0; i < v.size_; i++) values[i] = v.values[i];
    capacity_ = v.size_;
    size_ = v.size_;
  };
  vector(vector &&v) noexcept : vector() {
    std::swap(size_, v.size_);
    std::swap(capacity_, v.capacity_);
    std::swap(values, v.values);
  };
  vector &operator=(vector &&v) noexcept {
    if (this != &v) {
      std::swap(size_, v.size_);
      std::swap(capacity_, v.capacity_);
      std::swap(values, v.values);
    }
    return *this;
  };
  ~vector() {
    capacity_ = 0;
    size_ = 0;
    delete[] values;
  };

  reference at(size_type pos) {
    if (pos >= size_) throw std::out_of_range("Index out of range");
    return values[pos];
  };
  reference operator[](size_type pos) { return values[pos]; };
  const_reference front() { return values[0]; };
  const_reference back() { return values[size_ - 1]; };
  T *data() { return values; };

  iterator begin() noexcept { return &values[0]; };
  iterator end() { return &values[size_]; };

  bool empty() { return begin() == end(); };
  size_type size() { return size_; };
  size_type max_size() { return std::numeric_limits<std::ptrdiff_t>::max(); };
  void reserve(size_type size) {
    if (size > capacity_) {
      T *new_storage = new T[size]{};
      for (size_type i = 0; i < size_; i++)
        new_storage[i] = std::move(values[i]);
      delete[] values;
      values = std::move(new_storage);
      capacity_ = size;
    }
  };
  size_type capacity() { return capacity_; };
  void shrink_to_fit() {
    if (size_ < capacity_) {
      T *new_storage = new T[size_]{};
      for (size_type i = 0; i < size_; i++)
        new_storage[i] = std::move(values[i]);
      delete[] values;
      values = std::move(new_storage);
      capacity_ = size_;
    }
  }

  void clear() noexcept {
    for (size_type i = 0; i < size_; i++) values[i].~T();
    size_ = 0;
  };
  iterator insert(iterator pos, const_reference value) {
    if (size_ == capacity_) {
      size_type new_capacity = 1;
      if (capacity_ != 0) new_capacity = capacity_ * 2;
      iterator old_begin = begin();
      reserve(new_capacity);
      pos = begin() + (pos - old_begin);
    }
    for (iterator i = end(); i > pos; --i) *i = std::move(*(i - 1));
    *pos = value;
    size_ += 1;
    return pos;
  }
  void erase(iterator pos) {
    (*pos).~T();
    while (pos < std::prev(end())) {
      *pos = std::move(*(pos + 1));
      ++pos;
    }
    size_ -= 1;
  };
  void push_back(const_reference value) {
    if (size_ == capacity_ && capacity_ != 0) reserve(capacity_ * 2);
    if (capacity_ == 0) reserve(1);
    values[size_] = value;
    size_ += 1;
  };
  void pop_back() {
    values[size_ - 1].~T();
    size_ -= 1;
  }
  void swap(vector &other) noexcept {
    if (this != &other) std::swap(*this, other);
  };

  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args) {
    iterator old_begin = begin();
    if (capacity_ < size_ + sizeof...(args)) reserve(size_ + sizeof...(args));
    iterator new_pos = begin() + (pos - old_begin);
    iterator new_pos_copy = new_pos;
    iterator last_element = std::prev(end());
    size_ += sizeof...(args);
    for (iterator i = std::prev(end()); i >= new_pos + sizeof...(args); i--) {
      *i = *std::move(last_element);
      last_element--;
    }
    vector<T> arg_values = {args...};
    for (auto element : arg_values) {
      *new_pos = std::move(element);
      new_pos++;
    }
    return new_pos_copy;
  };

  template <typename... Args>
  void emplace_back(Args &&...args) {
    if (capacity_ < size_ + sizeof...(args)) reserve(size_ + sizeof...(args));
    iterator new_pos = end();
    size_ += sizeof...(args);
    vector<T> arg_values = {args...};
    for (auto element : arg_values) {
      *new_pos = std::move(element);
      new_pos++;
    }
  };

 private:
  T *values;
  size_type capacity_;
  size_type size_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_VECTOR_S21_VECTOR_H_