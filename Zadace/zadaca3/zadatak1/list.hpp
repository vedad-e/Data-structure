#pragma once
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

// OSTALO TI JE JOS add() i lista za inicijaliazciju konstruktor

template <typename T>
class List {
  public:
  List() = default;
  List(const std::initializer_list<T> il);
  List(const List& other);
  List(List&& other);
  List& operator=(const List& other);
  List& operator=(List&& other);
  ~List();

  size_t size() const { return size_; }
  void push_back(const T& element);
  void push_back(T&& element);
  void push_front(const T& element);
  void add(const T& element);
  void clear();
  bool empty() const { return size_ == 0; }
  void pop_front();
  void pop_back();
  const T& at(size_t index) const;

  template <typename U>
  void transform(U predicate);

  class iterator;

  iterator begin() { return iterator{front_}; }
  iterator end() { return iterator{nullptr}; }

  void insert(iterator position, const T& element);
  void remove(iterator position);

  template <typename U>
  iterator find(U predicate);
  iterator find(const T& value);

  private:
  struct Node {
    T data;
    Node* next;
  };
  Node* front_ = nullptr;
  Node* back_ = nullptr;
  size_t size_ = 0;
};

// PITAT LEJLU
template <typename T>
List<T>::List(std::initializer_list<T> il) {
  for (auto i = il.begin(); i < il.end(); ++i) {
    push_back(*i);
  }
}

// copy konstr
template <typename T>
List<T>::List(const List& other) {
  auto temp = other.front_;
  while (temp != nullptr) {
    push_back(temp->data);
    temp = temp->next;
  }
}

// move konstr
template <typename T>
List<T>::List(List&& other)
    : front_{other.front_}, back_{other.back_}, size_{other.size_} {
  other.front_ = nullptr;
  other.back_ = nullptr;
  other.size_ = 0;
}

// copy operator =
template <typename T>
List<T>& List<T>::operator=(const List& other) {
  clear();
  auto temp = other.front_;
  while (temp != nullptr) {
    push_back(temp->data);
    temp = temp->next;
  }
  return *this;
}

// move operator =
template <typename T>
List<T>& List<T>::operator=(List&& other) {
  clear();

  front_ = other.front_;
  back_ = other.back_;
  size_ = other.size_;

  other.front_ = nullptr;
  other.back_ = nullptr;
  size_ = 0;

  return *this;
}

// destruktor
template <typename T>
List<T>::~List() {
  while (front_ != nullptr) {
    auto temp = front_->next;
    delete front_;
    front_ = temp;
  }
}

/////////////////////////////////////////

template <typename T>
void List<T>::push_back(const T& element) {
  if (front_ == nullptr) {
    front_ = new Node{element, nullptr};
    back_ = front_;
  } else {
    auto temp = new Node{element, nullptr};
    back_->next = temp;
    back_ = temp;
  }
  size_++;
}

template <typename T>
void List<T>::push_back(T&& element) {
  if (front_ == nullptr) {
    front_ = new Node{std::move(element), nullptr};
    back_ = front_;
  } else {
    auto temp = new Node{std::move(element), nullptr};
    back_->next = temp;
    back_ = temp;
  }
  size_++;
}

template <typename T>
void List<T>::push_front(const T& element) {
  if (back_ == nullptr) {
    push_back(element);
  } else {
    auto temp = new Node{element, nullptr};
    temp->next = front_;
    front_ = temp;
  }
  size_++;
}

// PITAT LEJLU
template <typename T>
void List<T>::add(const T& element) {}

template <typename T>
void List<T>::clear() {
  while (front_ != nullptr) {
    auto temp = front_->next;
    delete front_;
    front_ = temp;
  }
  back_ = nullptr;
  size_ = 0;
}

template <typename T>
void List<T>::pop_front() {
  if (empty()) return;

  if (size() == 1) {
    clear();
    return;
  }
  auto temp = front_;
  front_ = front_->next;
  delete temp;
  size_--;
}

template <typename T>
void List<T>::pop_back() {
  if (empty()) return;

  if (size() == 1) {
    clear();
    return;
  }

  auto temp = front_;
  while (temp->next != back_) {
    temp = temp->next;
  }
  delete back_;
  back_ = temp;
  back_->next = nullptr;
  size_--;
}

template <typename T>
const T& List<T>::at(size_t index) const {
  if (index >= size_) {
    throw std::out_of_range{"Invalidan index"};
  }
  auto temp = front_;
  for (auto i = 0; i < index; ++i) {
    temp = temp->next;
  }
  return temp->data;
}

template <typename T>
template <typename U>
void List<T>::transform(U predicate) {
  auto it = begin();
  while (it != end()) {
    predicate(*it);
    ++it;
  }
}

template <typename T>
void List<T>::insert(iterator position, const T& element) {
  auto new_node = new Node{element, position.p_->next};
  position.p_->next = new_node;
  std::swap(position.p_->data, new_node->data);
}

template <typename T>
void List<T>::remove(iterator position) {
  if (back_ == position.p_) {
    pop_back();
  } else {
    std::swap(position.p_->data, position.p_->next->data);
    auto temp = position.p_->next;
    position.p_->next = position.p_->next->next;
    delete temp;
  }
}

template <typename T>
template <typename U>
typename List<T>::iterator List<T>::find(U predicate) {
  auto it = begin();
  while (it != end()) {
    if (predicate(*it)) {
      return it;
    }
    ++it;
  }
  return end();
}

/*
template <typename T>
typename List<T>::iterator List<T>::find(const T& value) {
  auto temp = front_;
  auto temp_prev = nullptr;

  while (temp != nullptr) {
    if (temp->value == value) {
      return iterator{temp_prev, temp};
    }
    temp_prev = temp;
    temp = temp->next;
  }
  return end();
}


template <typename T>
typename List<T>::iterator List<T>::find(const T& value) {
  find([](T value){return *it == value};)
}
*/

template <typename T>
class List<T>::iterator : public std::iterator<std::forward_iterator_tag, T> {
  public:
  friend class List<T>;

  iterator(Node* p) : p_{p} {}

  iterator& operator++() {
    if (p_ != nullptr) p_ = p_->next;
    return *this;
  }
  iterator operator++(int) {
    auto temp = iterator{p_};
    if (p_ != nullptr) p_ = p_->next;
    return *this;
  }

  bool operator==(const iterator& other) { return p_ == other.p_; }
  bool operator!=(const iterator& other) { return p_ != other.p_; }

  T& operator*() { return p_->data; }
  T& operator->() { return p_->data; }

  private:
  Node* p_;
};

