#pragma once
#include <iostream>

template <typename T>
class Queue {
  public:
  Queue() = default;

  Queue(const Queue& other) {
    auto temp = other.head_;
    while (temp != nullptr) {
      push(temp->data);
      temp = temp->next;
    }
  }

  Queue(Queue&& other)
      : head_{other.head_}, tail_{other.tail_}, size_{other.size_} {
    other.head_ = other.tail_ = nullptr;
    other.size_ = 0;
  }

  Queue& operator=(const Queue& other) {
    clear();
    auto temp = other.head_;
    while (temp != nullptr) {
      push(temp->data);
      temp = temp->next;
    }
    return *this;
  }

  Queue& operator=(Queue&& other) {
    clear();

    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;

    other.head_ = other.tail_ = nullptr;
    other.size_ = 0;

    return *this;
  }

  ~Queue() {
    while (head_ != nullptr) {
      auto temp = head_->next;
      delete head_;
      head_ = temp;
    }
  }

  size_t size() { return size_; }

  bool empty() const { return size_ == 0; }

  T& top() { return head_->data; }

  void clear() {
    while (head_ != nullptr) {
      auto temp = head_->next;
      delete head_;
      head_ = temp;
    }
    tail_ = nullptr;
    size_ = 0;
  }

  template <typename F>
  Queue& push(F&& element) {
    if (head_ == nullptr) {
      head_ = new Node{std::forward<F>(element), nullptr};
      tail_ = head_;
    } else {
      auto temp = new Node{std::forward<F>(element), nullptr};
      tail_->next = temp;
      tail_ = temp;
    }
    return *this;
  }

  void pop() {
    if (empty()) return;

    if (size() == 1) {
      clear();
      return;
    }
    auto temp = head_;
    head_ = head_->next;
    delete temp;
    size_--;
  }

  void print(std::ostream& il) {
    auto temp = head_;
    while (temp) {
      std::cout << temp->data << std::endl;
      temp = temp->next;
    }
    std::cout << std::endl;
  }

  private:
  struct Node {
    T data;
    Node* next;
  };
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
  size_t size_ = 0;
};

