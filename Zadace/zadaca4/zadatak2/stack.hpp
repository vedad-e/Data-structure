#pragma once

#include <iostream>

template <typename T>
class Stack {
  public:
  Stack() : capacity_{100}, size_{0}, data_{new T[capacity_]} {}

  Stack(const size_t capacity)
      : capacity_{capacity}, size_{0}, data_{new T[capacity_]} {}

  Stack(const Stack& other)
      : capacity_{other.capacity_},
        size_{other.size_},
        data_{new T[capacity_]} {
    for (auto i = 0; i < size_; ++i) {
      data_[i] = other.data_[i];
    }
  }

  Stack(Stack&& other)
      : capacity_{other.capacity_}, size_{other.size_}, data_{other.data_} {
    other.data_ = nullptr;
    other.capacity_ = other.size_ = 0;
  }

  Stack& operator=(const Stack& other) {
    delete[] data_;

    capacity_ = other.capacity_;
    size_ = other.size_;
    data_ = new T[capacity_];

    for (auto i = 0; i < size_; ++i) {
      data_[i] = other.data_[i];
    }
    return *this;
  }

  Stack& operator=(Stack&& other) {
    delete[] data_;

    capacity_ = other.capacity_;
    size_ = other.size_;
    data_ = other.data_;

    other.capacity_ = other.size_ = 0;
    other.data_ = nullptr;

    return *this;
  }

  ~Stack() { delete[] data_; }

  size_t size() { return size_; }

  bool empty() { return size_ == 0; }

  T& top() { return data_[size_ - 1]; }

  // obicni pop
  void pop() { size_--; }

  /* pop koji vraca referencu
  T& pop2() {
    T temp = std::move(data_[size_ - 1]);
    size_--;
    return temp;
  }
  */

  void reallocate() {
    auto new_capacity = new T[2 * capacity_];
    for (auto i = 0; i < size_; ++i) {
      new_capacity[i] = std::move(data_[i]);
    }
  }

  // ovaj reallocate radi tako sto mu se proslijedi nova vrijednost kapaciteta
  // ako je ona manja od stare vrijednosti izbrisat ce visak elemenata
  void reallocate(size_t new_capacity) {
    if (capacity_ == new_capacity) {
      return;
    }
    T* temp = new T[new_capacity];

    auto new_size = size_;
    if (size_ > new_capacity) {
      new_size = new_capacity;
    }

    for (auto i = 0; i < new_size; ++i) {
      temp[i] = std::move(data_[i]);
    }
    delete[] data_;
    data_ = temp;
    capacity_ = new_capacity;
    size_ = new_size;
  }

  void push(const T& element) {
    if (size_ == capacity_) {
      reallocate();
    }
    data_[size_++] = element;
  }

  void push(T&& element) {
    if (size_ == capacity_) {
      reallocate();
    }
    data_[size_++] = std::move(element);
  }

  private:
  size_t capacity_;
  size_t size_;
  T* data_;
};

/*
template <typename T>
std::ostream& operator<<(std::ostream& s, const Stack<T>& stack) {
  for (int i = stack.top(); i >= 0; --i) {
  }
}
*/

