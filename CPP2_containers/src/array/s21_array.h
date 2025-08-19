#ifndef CPP2_S21_CONTAINERS_1_SRC_ARRAY_S21_ARRAY_H_
#define CPP2_S21_CONTAINERS_1_SRC_ARRAY_S21_ARRAY_H_

#include <cstddef>
#include <exception>
#include <utility>

namespace s21 {
template <typename T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  array() {
    values = new T[N];
    size_ = N;
  };
  array(std::initializer_list<value_type> const &items) {
    values = new T[N]{};
    size_type i = 0;
    for (auto element : items) values[i++] = element;
    size_ = N;
  };
  array(const array &a) {
    values = new T[N];
    for (size_type i = 0; i < N; i++) values[i] = a.values[i];
    size_ = a.size_;
  };
  array(array &&a) noexcept : array() { std::swap(values, a.values); };
  ~array() {
    size_ = 0;
    delete[] values;
  };
  array &operator=(array &&a) noexcept {
    if (this != &a) std::swap(values, a.values);
    return *this;
  };

  reference at(size_type pos) {
    if (pos >= size_) throw std::out_of_range("Index out of range");
    return values[pos];
  };
  reference operator[](size_type pos) { return values[pos]; };
  const_reference front() { return values[0]; };
  const_reference back() { return values[size_ - 1]; };
  iterator data() noexcept { return values; };

  iterator begin() noexcept { return &values[0]; };
  iterator end() noexcept { return &values[size_]; };

  bool empty() noexcept { return size_ == 0; };
  size_type size() noexcept { return size_; };
  size_type max_size() noexcept { return size_; };

  void swap(array &other) noexcept {
    if (this != &other) {
      for (size_type i = 0; i < size_; i++)
        std::swap(values[i], other.values[i]);
    }
  };
  void fill(const_reference value) {
    for (size_type i = 0; i < size_; i++) values[i] = value;
  };

 private:
  T *values;
  size_type size_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_ARRAY_S21_ARRAY_H_