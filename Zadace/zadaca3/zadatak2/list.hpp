#pragma once
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

template <typename T>
struct Node {
  T element_;
  Node* prev_ = nullptr;
  Node* next_ = nullptr;

  Node(const T& e, Node* p = nullptr, Node* n = nullptr)
      : element_{e}, prev_{p}, next_{n} {}
  Node(T&& e, Node* p = nullptr, Node* n = nullptr)
      : element_{std::move(e)}, prev_{p}, next_{n} {}
};

template <typename T>
class mojaLista {
  public:
  Node<T>* getHead() const { return head_; }
  Node<T>* getTail() const { return tail_; }
  mojaLista() = default;
  mojaLista(const mojaLista& other);
  mojaLista(const std::initializer_list<T>&);
  mojaLista(mojaLista&& other);
  mojaLista& operator=(const mojaLista& other);
  mojaLista& operator=(mojaLista&& other);
  ~mojaLista();

  size_t size() const { return size_; }
  bool empty() const { return size_ == 0; }
  void clear();
  T back();
  T front();
  void pop_back();
  void pop_front();

  template <typename U>
  mojaLista& push_back(U&&);
  template <typename U>
  mojaLista& push_front(U&&);
  //  bool operator==(const mojaLista&);
  //  bool operator!=(const mojaLista&);

  class iterator;

  iterator begin() { return iterator(nullptr, head_); }
  iterator end() { return iterator(tail_, nullptr); }

  template <typename U>
  iterator find(U predicate);
  iterator find(const T& value);

  template <typename U>
  iterator insert(const iterator&, U&&);
  void erase(iterator position);

  friend std::ostream& operator<<(std::ostream& out, mojaLista& l) {
    auto temp = l.head;
    while (temp) {
      std::cout << temp->value << " ";
      temp = temp->next;
    }
    std::cout << std::endl;
    return out;
  }

  private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  size_t size_ = 0;
};

// copy konstr
template <typename T>
mojaLista<T>::mojaLista(const mojaLista& other) : size_{other.size_} {
  head_ = tail_ = new Node<T>(other.head_->element_);
  auto temp = other.head_->next_;
  while (temp) {
    auto new_node = new Node<T>(temp->element_);
    tail_->next_ = new_node;
    new_node->prev_ = tail_;
    tail_ = new_node;
    temp = temp->next_;
  }
}

// lista za inicijalizaciju
template <typename T>
mojaLista<T>::mojaLista(const std::initializer_list<T>& il) : size_{il.size()} {
  auto temp = il.begin() + 1;
  head_ = tail_ = new Node<T>(*(il.begin()));
  auto temp2 = head_;
  for (auto it = temp; it != il.end(); ++it) {
    auto new_node = new Node<T>(*it);
    new_node->prev_ = temp2;
    temp2 = new_node;
    tail_->next_ = new_node;
    tail_ = new_node;
  }
}

// move kontsr
template <typename T>
mojaLista<T>::mojaLista(mojaLista&& other)
    : head_{other.head_}, tail_{other.tail_}, size_{other.size_} {
  other.head_ = other.tail_ = nullptr;
  other.size_ = 0;
}

// copy operator =
template <typename T>
mojaLista<T>& mojaLista<T>::operator=(const mojaLista& other) {
  if (this != &other) {
    clear();
    if (!other.empty()) {
      head_ = tail_ = new Node<T>(other.head_->element_);
      auto temp = other.head_->next_;
      while (temp) {
        auto new_node = new Node<T>(temp->element_);
        tail_->next_ = new_node;
        new_node->prev_ = tail_;
        temp = temp->next_;
        tail_ = new_node;
      }
      size_ = other.size_;
    }
  }
  return *this;
}

// move operator =
template <typename T>
mojaLista<T>& mojaLista<T>::operator=(mojaLista&& other) {
  clear();
  size_ = other.size_;
  head_ = other.head_;
  tail_ = other.tail_;
  other.head_ = other.tail_ = nullptr;
  other.size_ = 0;
  return *this;
}

template <typename T>
mojaLista<T>::~mojaLista() {
  clear();
}

template <typename T>
void mojaLista<T>::clear() {
  auto temp = head_;
  if (!empty()) {
    while (temp != nullptr) {
      delete head_;
      temp = temp->next_;
      head_ = temp;
    }
    head_ = tail_ = nullptr;
    size_ = 0;
  }
}

template <typename T>
T mojaLista<T>::back() {
  return tail_->element_;
}

template <typename T>
T mojaLista<T>::front() {
  return head_->element_;
}

template <typename T>
void mojaLista<T>::pop_back() {
  auto temp = tail_;
  temp->prev_->next_ = nullptr;
  tail_ = temp->prev_;
  delete temp;
  --size_;
}

template <typename T>
void mojaLista<T>::pop_front() {
  auto temp = head_;
  temp->next_->prev_ = nullptr;
  head_ = temp->next_;
  delete temp;
  --size_;
}

template <typename T>
template <typename U>
mojaLista<T>& mojaLista<T>::push_back(U&& x) {
  auto new_Node = new Node<T>(std::forward<U>(x));
  if (empty()) {
    head_ = tail_ = new_Node;
  } else {
    tail_->next_ = new_Node;
    new_Node->prev_ = tail_;
    tail_ = new_Node;
  }
  ++size_;
  return *this;
}

template <typename T>
template <typename U>
mojaLista<T>& mojaLista<T>::push_front(U&& x) {
  auto new_Node = new Node<T>(std::forward<U>(x));
  if (empty())
    head_ = tail_ = new_Node;
  else {
    new_Node->next_ = head_;
    head_->prev_ = new_Node;
    head_ = new_Node;
  }
  ++size_;
  return *this;
}

template <typename T>
bool operator!=(const mojaLista<T>& left, const mojaLista<T>& right) {
  return !(left == right);
}

template <typename T>
bool operator==(const mojaLista<T>& left, const mojaLista<T>& right) {
  if ((left.getHead()->element_) != (right.getHead()->element_)) return false;
  if ((left.getTail()->element_) != (right.getTail()->element_)) return false;
  if (left.size() != right.size()) return false;

  auto temp = left.getHead();
  auto temp2 = right.getHead();
  while (temp) {
    if (temp->element_ != temp2->element_) return false;
    temp = temp->next_;
    temp2 = temp2->next_;
  }
  return true;
}

template <typename T>
template <typename U>
typename mojaLista<T>::iterator mojaLista<T>::find(U predicate) {
  for (auto it = begin(); it != end(); ++it) {
    if (predicate(*it)) return it;
  }
  return end();
}

template <typename T>
typename mojaLista<T>::iterator mojaLista<T>::find(const T& value) {
  for (auto it = begin(); it != end(); ++it) {
    if (*it == value) return it;
  }
  return end();
}

template <typename T>
template <typename U>
typename mojaLista<T>::iterator mojaLista<T>::insert(const iterator& it,
                                                     U&& x) {
  auto newNode = new Node<T>(std::forward<U>(x));
  if (empty()) {
    head_ = tail_ = newNode;
    ++size_;
    return begin();
  }
  if (it.myNode == head_) {
    newNode->next_ = head_;
    head_->prev_ = newNode;
    head_ = newNode;
    ++size_;
    return begin();
  }
  if (it.myNode == tail_) {
    tail_->next_ = newNode;
    newNode->prev_ = tail_;
    tail_ = newNode;
    ++size_;
    return iterator(tail_->prev_, tail_);
  }

  else {
    auto temp = head_;
    while (temp != (it.myNode)) {
      temp = temp->next_;
    }
    temp->prev_->next_ = newNode;
    newNode->prev_ = temp->prev_;
    temp->prev_ = newNode;
    newNode->next_ = temp;

    ++size_;
    return iterator(temp->prev_->prev_, temp->prev_);
  }
}

template <typename T>
void mojaLista<T>::erase(iterator position) {
  if (size_ < 2)
    clear();
  else {
    if (position.myNode == head_) {
      head_ = head_->next_;
      head_->prev_ = nullptr;
    } else if (position.myNode == tail_) {
      tail_ = position.prevNode;
      if (tail_) tail_->next_ = nullptr;
    } else {
      position.prevNode->next_ = position.myNode->next_;
      (position.myNode->next_)->prev_ = position.prevNode;
    }
    delete position.myNode;
    size_--;
  }
}

template <typename T>
class mojaLista<T>::iterator
    : public std::iterator<std::bidirectional_iterator_tag, T> {
  public:
  friend class mojaLista<T>;

  iterator() = default;
  iterator(Node<T>* p, Node<T>* m) : myNode{m}, prevNode{p} {}

  iterator& operator++() {
    prevNode = myNode;
    if (myNode) myNode = myNode->next_;
    return *this;
  }

  iterator operator++(int) {
    auto oldThis = *this;
    prevNode = myNode;
    if (myNode) myNode = myNode->next_;
    return oldThis;
  }

  iterator& operator--() {
    myNode = prevNode;
    if (prevNode) prevNode = prevNode->previous;
    return *this;
  }
  iterator operator--(int) {
    auto oldThis = *this;
    myNode = prevNode;
    if (prevNode) prevNode = prevNode->previous;
    return oldThis;
  }

  bool operator==(const iterator& other) const {
    return myNode == other.myNode;
  }
  bool operator!=(const iterator& other) const {
    return myNode != other.myNode;
  }

  T& operator*() { return myNode->element_; }
  const T& operator*() const { return myNode->element_; }
  T& operator->() { return myNode->element_; }

  private:
  Node<T>* myNode = nullptr;
  Node<T>* prevNode = nullptr;
};
