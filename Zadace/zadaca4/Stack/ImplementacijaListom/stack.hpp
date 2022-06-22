#pragma once
#include <iostream>

template <typename T>
class Stack {
  public:
  Stack() : head_{nullptr}, tail_{nullptr}, size_{0} {}

  Stack(const Stack& other) {
    auto temp = other.head_;
    while (temp != nullptr) {
      push_back(temp->data);
      temp = temp->next;
    }
  }

  Stack(Stack&& other)
      : head_{other.head_}, tail_{other.tail_}, size_{other.size_} {
    other.head_ = other.tail_ = nullptr;
    other.size_ = 0;
  }

  Stack& operator=(const Stack& other) {
    clear();
    auto temp = other.head_;
    while (temp != nullptr) {
      push_back(temp->data);
      temp = temp->next;
    }
    return *this;
  }

  Stack& operator=(Stack&& other) {
    clear();

    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;

    other.head_ = other.tail_ = nullptr;
    other.size_ = 0;

    return *this;
  }

  ~Stack() {
    while (head_ != nullptr) {
      auto temp = head_->next;
      delete head_;
      head_ = temp;
    }
  }

  void clear() {
    while (head_ != nullptr) {
      auto temp = head_->next;
      delete head_;
      head_ = temp;
    }
  }

  size_t size() { return size_; }

  bool empty() { return size_ == 0; }

  T& top() { return head_->data; }

  void pop() {
    auto temp = head_;
    head_ = head_->next;
    delete temp;
    size_--;
  }

  T& pop2() {
    auto temp = head_;
    head_ = head_->next;
    T d = std::move(temp->data);
    delete temp;
    return d;
  }

  void push(T&& element) {
    if (head_ == nullptr) {
      head_ = new Node{std::forward<T>(element), nullptr};
      tail_ = head_;
    } else {
      auto temp = new Node{std::forward<T>(element), nullptr};
      temp->next = head_;
      head_ = temp;
    }
    size_++;
  }

  private:
  struct Node {
    T data;
    Node* next;
  };
  Node* head_;
  Node* tail_;
  size_t size_;
};
