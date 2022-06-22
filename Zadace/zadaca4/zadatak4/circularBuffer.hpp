#pragma once
#include <iostream>
#include <stdexcept>
#include <type_traits>

template <typename T>
class CircularBuffer {
  public:
  CircularBuffer(size_t capacity = 10)
      : size_{0}, capacity_{capacity}, data_{new T[capacity]} {}

  CircularBuffer(const CircularBuffer& other)
      : size_{other.size_},
        capacity_{other.capacity_},
        data_{new T[other.capacity_]} {
    for (auto i = 0; i < other.capacity_; ++i) {
      data_[i] = other.data_[i];
    }
    front_ = other.front_;
    back_ = other.back_;
  }

  ~CircularBuffer() {
    delete[] data_;
    size_ = capacity_ = 0;
    front_ = back_ = -1;
  }

  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularBuffer& buffer) {
    if (buffer.front_ <= buffer.back_) {
      os << "[";
      for (auto i = buffer.front_; i <= buffer.back_; ++i) {
        os << buffer.data_[i] << " ";
      }
      os << "]" << std::endl;
    } else {
      os << "[";
      for (auto i = buffer.front_; i < buffer.capacity_; ++i) {
        os << buffer.data_[i] << " ";
      }
      for (auto i = 0u; i <= buffer.back_; ++i) {
        os << buffer.data_[i] << " ";
      }
      os << "]" << std::endl;
    }
    return os;
  }

  size_t size() const { return size_; }

  bool empty() const { return size_ == 0; }

  T& front() { return data_[front_]; }

  T& back() { return data_[back_]; }

  void reallocate() {
    T* temp = data_;
    size_t initialCapacity = capacity_;
    capacity_ *= 2;
    data_ = new T[capacity_];
    std::copy(temp, temp + initialCapacity, data_);
    delete[] temp;
  }

  template <typename U>
  CircularBuffer& push(U&& element) {
    if (size_ == capacity_) {
      reallocate();
    }
    size_t index;
    if (empty() || back_ == capacity_) {
      index = back_ = 0;
    } else {
      index = ++back_;
    }
    data_[index] = std::forward<U>(element);
    ++size_;
    return *this;
  }

  void print() const {
    if (empty()) return;

    for (int i = front_; i <= back_; ++i) {
      std::cout << data_[i] << " ";
    }
    std::cout << std::endl;
  }

  T pop() {
    if (size_ == 0) {
      throw std::out_of_range("Empty");
    }
    size_--;
    int temp_front = front_;
    if (size_ == 0) {
      front_ == 0;
      back_ == 0;
    } else {
      front_++;
    }
    return data_[temp_front];
  }

  private:
  T* data_;
  size_t size_;
  size_t capacity_;
  int front_ = 0;
  int back_ = 0;
};
