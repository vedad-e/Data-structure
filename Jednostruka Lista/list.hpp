#pragma once
#include <iostream>

template <typename T>
class List {
  public:
  List() = default;

  // copy konstruktor
  List(const List& other);

  // move konstr
  List(List&& other);

  // copy operator =
  List& operator=(const List& other);

  // move operator =
  List& operator=(List&& other);

  ~List();

  void clear();
  void push_back(const T& element);
  void push_front(const T& element);
  void push_back(T&& element);
  size_t size() const { return size_; }
  bool empty() const { return size_ == 0; }
  void pop_front();
  void pop_back();
  const T& at(size_t index) const;

  class iterator;

  iterator begin() { return iterator{front_}; }
  iterator end() { return iterator{nullptr}; }

  // Ovaj begin i end se rade kada imamo neku f-ju print u koju proslijedimo
  // listu
  /*
  const_iterator begin() const { return const_iterator{front_}; }
  const_iterator end() const { return const_iterator{nullptr}; }
  */

  void insert(iterator position, const T& element);
  // void insert(iterator position, T&& element);

  void erase(iterator position);
  // void insert(iterator position, T&& element);

  private:
  struct Node {
    T data;
    Node* next_;
  };

  Node* front_ = nullptr;
  Node* back_ = nullptr;
  size_t size_ = 0;
};

// copy konstruktor
template <typename T>
List<T>::List(const List& other) {
  auto temp = other.front_;
  while (temp != nullptr) {
    push_back(temp->data);
    temp = temp->next_;
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
    temp = temp->next_;
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
  other.size_ = 0;

  return *this;
}

template <typename T>
List<T>::~List() {
  while (front_ != nullptr) {
    auto temp = front_->next_;
    delete front_;
    front_ = temp;
  }
}

// clear() treba da obrise sve elemente ali da ostavi listu u stanju
// koje je validno za dalje koristenje
template <typename T>
void List<T>::clear() {
  while (front_ != nullptr) {
    auto temp = front_->next_;
    delete front_;
    front_ = temp;
  }
  back_ = nullptr;
  size_ = 0;
}

// obicni pushback
template <typename T>
void List<T>::push_back(const T& element) {
  if (front_ == nullptr) {
    front_ = new Node{element, nullptr};
    back_ = front_;
  } else {
    auto temp = new Node{element, nullptr};
    back_->next_ = temp;
    back_ = temp;
  }
  size_++;
}

// move pushback
template <typename T>
void List<T>::push_back(T&& element) {
  if (front_ == nullptr) {
    front_ = new Node{std::move(element), nullptr};
    back_ = front_;
  } else {
    auto temp = new Node{std::move(element), nullptr};
    back_->next_ = temp;
    back_ = temp;
  }
  size_++;
}
template <typename T>
void List<T>::push_front(const T& element) {
  // ako je niz prazan:
  if (back_ == nullptr) {
    push_back(element);
  } else {
    auto temp = new Node{element, nullptr};
    temp->next_ = front_;
    front_ = temp;
  }
  size_++;
}

template <typename T>
void List<T>::pop_front() {
  if (empty()) return;

  if (size() == 1) {
    clear();
    return;
  }

  auto temp = front_;
  front_ = front_->next_;
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

  // ovom petljom dolazimo do zadnjeg elementa
  auto temp = front_;
  while (temp->next_ != back_) {
    temp = temp->next_;
  }

  delete back_;
  back_ = temp;
  back_->next_ = nullptr;
  size_--;
}

template <typename T>
const T& List<T>::at(size_t index) const {
  if (index >= size_) {
    throw std::out_of_range{"Invalidan index"};
  }
  auto temp = front_;
  for (auto i = 0; i < index; ++i) {
    temp = temp->next_;
  }
  return temp->data;
}

// Prva implementacija inserta
/*
template <typename T>
void List<T>::insert(iterator position, const T& element) {
  auto new_node = new Node{element, nullptr};
  new_node->next_ = position.p_;

  if (front_ == position.p_) {
    front_ = new_node;
  } else {
    auto temp = front_;
    while (temp->next_ != position.p_) {
      temp = temp->next_;
    }
    temp->next_ = new_node;
  }
}
*/

// Druga implementacija inserta O(1)
template <typename T>
void List<T>::insert(iterator position, const T& element) {
  auto new_node = new Node{element, position.p_->next_};
  position.p_->next_ = new_node;
  std::swap(position.p_->data, new_node->data);
}

// Prva implementacija erasea O(n)
/*
template <typename T>
void List<T>::erase(iterator position) {
  if (front_ == position.p_) {
    pop_front();
  } else {
    auto temp = front_;
    while (temp->next_ != position.p_) {
      temp = temp->next_;
    }
    temp->next_ = position.p_->next_;
    delete position.p_;
  }
}
*/

// Druga implementacija erasea O(1)
template <typename T>
void List<T>::erase(iterator position) {
  if (back_ == position.p_) {
    pop_back();
  } else {
    std::swap(position.p_->data, position.p_->next_->data);
    auto temp = position.p_->next_;
    position.p_->next_ = position.p_->next_->next_;

    delete temp;
  }
}

// ITERATOR
template <typename T>
class List<T>::iterator : public std::iterator<std::forward_iterator_tag, T> {
  public:
  friend class List<T>;

  iterator(Node* p) : p_{p} {}

  iterator& operator++() {
    if (p_ != nullptr) p_ = p_->next_;
    return *this;
  }

  iterator operator++(int) {
    auto temp = iterator{p_};
    if (p_ != nullptr) p_ = p_->next_;
    return temp;
  }

  bool operator==(const iterator& other) { return p_ == other.p_; }
  bool operator!=(const iterator& other) { return p_ != other.p_; }

  T& operator*() { return p_->data; }
  T& operator->() { return p_->data; }

  private:
  Node* p_;
};

