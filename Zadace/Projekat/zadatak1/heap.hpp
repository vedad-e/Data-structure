#pragma once
#include <algorithm>
#include <iostream>

const int DEFAULT_CAPACITY = 10;

template <typename T>
class Heap {
  public:
  Heap(int capacity = DEFAULT_CAPACITY) : capacity_(capacity), size_(0) {
    heap_ = new T[capacity];
  }

  Heap(const Heap& other)
      : capacity_{other.capacity_},
        size_{other.size_},
        heap_{new T{capacity_}} {
    for (auto i = 0; i < size_; ++i) {
      heap_[i] = other.heap_[i];
    }
  }

  Heap(Heap&& other)
      : capacity_{other.capacity_}, size_{other.size_}, heap_{other.heap_} {
    other.heap_ = nullptr;
    other.capacity_ = other.size_ = 0;
  }

  Heap& operator=(const Heap& other) {
    deleteAll();

    capacity_ = other.capacity_;
    size_ = other.size_;
    heap_ = new T[capacity_];

    for (auto i = 0; i < size_; ++i) {
      heap_[i] = other.heap_[i];
    }
    return *this;
  }

  Heap& operator=(Heap&& other) {
    deleteAll();

    capacity_ = other.capacity_;
    size_ = other.size_;
    heap_ = other.heap_;

    other.capacity_ = other.size_ = 0;
    other.heap_ = nullptr;

    return *this;
  }

  ~Heap() { deleteAll(); }

  int size() const { return size_; }
  bool empty() const { return size_ == 0; }
  int capacity() const { return capacity_; }

  void insert(T data) {
    if (size() == capacity()) {
      reallocate();
    }
    heap_[size_++] = data;
    int i = size() - 1;
    while ((i != 0) && heap_[parent(i)] < heap_[i]) {
      swap(&heap_[parent(i)], &heap_[i]);
      i = parent(i);
    }
  }

  void printHeap() const {
    if (empty()) {
      std::cout << "Heap je prazan" << std::endl;
    }
    for (int i = 0; i < size(); ++i) {
      std::cout << heap_[i] << " ";
    }
    std::cout << std::endl;
  }

  const T& max() const {
    if (empty()) {
      throw std::out_of_range{"Heap je prazan"};
    }
    return heap_[0];
  }

  T& max() {
    if (empty()) {
      throw std::out_of_range{"Heap je prazan"};
    }
    return heap_[0];
  }

  const T& min() const {
    if (empty()) {
      throw std::out_of_range{"Heap je prazan"};
    }

    T currentIndex = heap_[0];
    size_t s = 0;
    for (size_t i = 0; i < size_; ++i) {
      if (currentIndex > heap_[i]) {
        s = i;
        currentIndex = heap_[i];
      }
    }
    return heap_[s];
  }

  T& min() {
    if (empty()) {
      throw std::out_of_range{"Heap je prazan"};
    }

    T currentIndex = heap_[0];
    size_t s = 0;
    for (size_t i = 0; i < size_; ++i) {
      if (currentIndex > heap_[i]) {
        s = i;
        currentIndex = heap_[i];
      }
    }
    return heap_[s];
  }

  T removeMax() {
    if (empty()) {
      throw std::out_of_range{"Heap je prazan"};
    }
    T maxItem = heap_[0];

    heap_[0] = heap_[--size_];

    balanceDown(0);
    return maxItem;
  }

  T removeMin() {
    if (empty()) {
      throw std::out_of_range{"Heap je prazan"};
    }

    T currentIndex = heap_[0];
    size_t s = 0;
    for (size_t i = 0; i < size_; ++i) {
      if (currentIndex > heap_[i]) {
        s = i;
        currentIndex = heap_[i];
      }
    }

    std::swap(heap_[s], heap_[size_ - 1]);
    --size_;
    balanseUp(size_ - 1);
  }

  void deleteAll() {
    if (!heap_) {
      return;
    }
    delete heap_;
    heap_ = nullptr;
    capacity_ = 0;
    size_ = 0;
  }

  friend std::ostream& operator<<(std::ostream& os, const Heap& h) {
    for (int i = 0; i < h.size_; i++) {
      if (i < h.size_ - 1)
        os << h.heap_[i] << ", ";
      else
        os << h.heap_[i] << std::endl;
    }
    return os;
  }

  private:
  int size_;
  int capacity_;
  T* heap_;

  void reallocate() {
    std::cout << "Poziva se reallocate" << std::endl;
    int new_capacity = 2 * capacity_;
    T* temp = new T[new_capacity];
    std::copy(heap_, heap_ + capacity_, temp);
    delete heap_;
    heap_ = temp;
    capacity_ = new_capacity;
    std::cout << "Novi kapacitet heapa je: " << capacity_ << std::endl;
  }

  void swap(T* a, T* b) {
    T temp = *a;
    *a = *b;
    *b = temp;
  }

  int parent(int index) const { return (index - 1) / 2; }

  int leftChild(int index) const { return 2 * index + 1; }

  int rightChild(int index) const { return 2 * index + 2; }

  void balanceDown(int currentIndex) {
    T left = leftChild(currentIndex);
    T right = rightChild(currentIndex);
    T largest = currentIndex;

    if ((left <= size_) && (heap_[left] > heap_[largest])) {
      largest = left;
    }

    if ((right <= size_) && (heap_[right] > heap_[largest])) {
      largest = right;
    }

    if (largest != currentIndex) {
      T temp = heap_[currentIndex];
      heap_[currentIndex] = heap_[largest];
      heap_[largest] = temp;
      balanceDown(largest);
    }
  }

  void balanseUp(size_t index) {
    while (index > 0 && heap_[(index - 1) / 2] < heap_[index]) {
      std::swap(heap_[(index - 1) / 2], heap_[index]);
      index = (index - 1) / 2;
    }
  }
};
