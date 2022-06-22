#pragma once
#include <iostream>

template <typename T>
class Queue {
  public:
  Queue() : capacity_{100}, size_{0}, data_{new T[capacity_]} {}

  Queue(const Queue& other)
      : capacity_{other.capacity_},
        size_{other.size_},
        data_{new T[other.capacity_]} {
    for (auto i = 0; i < other.capacity_; ++i) {
      data_[i] = other.data_[i];
    }
    front_ = other.front_;
    back_ = other.back_;
  }

  ~Queue() {
    delete[] data_;
    size_ = capacity_ = 0;
    front_ = back_ = -1;
  }

  size_t size() { return size_; }

  bool empty() const { return size_ == 0; }

  T& front() { return data_[front_]; }
  T& back() { return data_[back_]; }

  Queue& push(const T& element) {
    if (size_ == capacity_) {
      throw std::out_of_range("Queue is full");
    }
    data_[size_++] = element;
    back_ = size_ - 1;
    if(size_ == 1){
      front_ = 0;
    }
    return *this;
  }

  T pop() {
    if (size_ == 0) {
      throw std::out_of_range("Empty");
    }
    size_--;
    int temp_front = front_;
    if (size_ == 0) {
      front_ = -1;
      back_ = -1;
    } else {
      front_++;
    }
    return data_[temp_front];
  }

  void print() const {
    if (empty()) return;

    for (int i = front_; i <= back_; ++i) {
      std::cout << data_[i] << " ";
    }
    std::cout << std::endl;
  }

  private:
  size_t capacity_;
  size_t size_;
  T* data_;
  int front_ = -1;
  int back_ = -1;
};
