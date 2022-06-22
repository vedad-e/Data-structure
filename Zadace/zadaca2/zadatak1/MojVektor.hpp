#pragma once
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <type_traits>

template <typename T>
class MojVector {
  public:
  MojVector() = default;
  MojVector(const std::size_t capacity)
      : capacity_{capacity}, size_{0}, data_{new T[capacity_]} {}

  MojVector(const std::initializer_list<T> &il) {
    size_ = il.size();
    capacity_ = 1.5 * il.size();
    data_ = new T[capacity_];
    std::copy(il.begin(), il.end(), data_);
  }

  // copy kontr
  MojVector(const MojVector &drugi)
      : capacity_{drugi.capacity_},
        size_{drugi.size_},
        data_{new T[capacity_]} {
    for (auto i = 0; i < size_; ++i) {
      data_[i] = drugi.data_[i];
    }
  }

  // copy assignment
  MojVector &operator=(const MojVector &drugi) {
    delete[] data_;

    capacity_ = drugi.capacity_;
    size_ = drugi.size_;
    data_ = new T[capacity_];

    for (auto i = 0; i < size_; ++i) {
      data_[i] = drugi.data_[i];
    }

    return *this;
  }

  // move konstruktor
  MojVector(MojVector &&drugi)
      : capacity_{drugi.capacity_}, size_{drugi.size_}, data_{drugi.data_} {
    drugi.data_ = nullptr;
    drugi.capacity_ = drugi.size_ = 0;
  }

  // move assignment
  MojVector &operator=(MojVector &&drugi) {
    if (this == &drugi) return *this;
    delete[] data_;

    capacity_ = drugi.capacity_;
    size_ = drugi.size_;
    data_ = drugi.data_;

    drugi.data_ = nullptr;
    drugi.capacity_ = drugi.size_ = 0;

    return *this;
  }

  // Destruktor
  ~MojVector() { delete[] data_; }

  // Implementacija push_backa
  MojVector &push_back(const T &novi_element) {
    if (size_ == capacity_) {
      throw std::out_of_range{"Dostignut je maksimalni kapcitet niza"};
    }
    data_[size_] = novi_element;
    ++size_;
  }

  // Implementiranje at (vrsi provjeru granica, baca iznimku ako granice nisu
  // okej)
  T &at(size_t index) {
    if (index >= size_) {
      throw std::out_of_range{"Proslijedjeni indeks je van granica niza"};
    }
    return data_[index];
  }

  const T &at(size_t index) const {
    if (index >= size_) {
      throw std::out_of_range{"Proslijedjeni indeks je van granica niza"};
    }
    return data_[index];
  }

  // Implementacija operatora []
  T &operator[](size_t index) { return data_[index]; }
  const T &operator[](size_t index) const { return data_[index]; }

  // brise cijeli sadrzaj, ali ne treba sve nulirati
  void clear() { size_ = 0; }

  // vraca velicinu niza
  size_t size() const { return size_; }

  // metod empty vraca da li je niz prazan
  bool empty() const { return size_ == 0; }

  const T &back() const { return data_[size_ - 1]; }

  const T &front() const { return data_[0]; }
  T &back() { return data_[size_ - 1]; }

  T &front() { return data_[0]; }

  // ELMIROV RESIZE
  void resize(size_t novi) {
    MojVector<T> tmp{*this};
    if (novi <= capacity_)
      size_ = novi;
    else {
      delete[] data_;
      T *data_ = new T[novi];
      std::copy(tmp.data_, tmp.data_ + tmp.size_, data_);
      capacity_ = novi;
      size_ = novi;
    }
  }

  void reallocate(size_t novi){
      auto temp = new T[novi];
      for(auto i=0; i<size_; ++i){
        temp[i] = data_[i];
      }
      capacity_ = novi;
      delete[] data_;
      data_ = temp;
    }

  MojVector &pop_back() {
    if (size_ > 0) {
      size_--;
    }
  }
  size_t capacity() const;

  bool operator!=(const MojVector &drugi) const { return !(*this == drugi); }
  bool operator==(const MojVector &drugi) const {
    if (size_ != drugi.size_) return false;
    for (auto i = 0u; i < size_; ++i) {
      if (drugi.data_[i] != data_[i]) return false;
    }
    return true;
  }

  class Iterator;

  Iterator begin() const { return Iterator{data_}; }
  Iterator end() const { return Iterator{data_ + size_}; }

  Iterator find(const T &element) const;

MojVector &insert(Iterator it, T element){
   /* if(size_>=capacity_){reallocate(2*capacity_);}
    int temp = it-begin();
for(size_t i=size_;i>temp;i--){
  arr_[i]=arr_[i-1];
}

  size_++;
  arr_[temp]=element;*/
  int index = it - begin();
    if (index < 0 || index > size_)
        throw std::out_of_range(" ");

    if (size_ == capacity_)
        reallocate(2*capacity_);

    for(int i = size_ - 1; i >= index; --i)
        data_[i+1] = data_[i];

    data_[index] = element;
    ++size_;
  return *this;
  };

  // brisemo element na datoj poziciji, i sve elemente poslije tog
  // pomijeramo unazad

  Iterator erase(Iterator pos);
  Iterator erase(Iterator beginIt, Iterator endIt);

  // metod sort
  template <typename F>
  void sort(F func) {
    std::sort(data_, data_ + size_, func);
  }

  private:
  size_t capacity_ = 100;
  size_t size_ = 0;
  T *data_ = new T[capacity_];
};

template <typename T>
class MojVector<T>::Iterator
    : public std::iterator<std::random_access_iterator_tag, T> {
  private:
  T *p_;

  public:
  Iterator(T *ptr) { p_ = ptr; }

  T &operator*() const { return *p_; }
  T *operator->() const;

  Iterator &operator++() {
    ++p_;
    return *this;
  }
  Iterator operator++(int) { return Iterator{p_++}; }

  Iterator &operator--() {
    --p_;
    return *this;
  }
  Iterator operator--(int) { return Iterator{p_--}; }

  Iterator operator+(size_t index) { return Iterator{p_ + index}; }

  Iterator operator-(size_t index) { return Iterator{p_ - index}; };

  size_t operator-(Iterator other) { return p_ - other.p_; }

  bool operator==(const Iterator &it) const { return p_ == it.p_; }
  bool operator!=(const Iterator &it) const { return p_ != it.p_; }
  bool operator<(const Iterator &it) const { return p_ < it.p_; }
  bool operator<=(const Iterator &it) const { return p_ <= it.p_; }
  bool operator>=(const Iterator &it) const { return p_ >= it.p_; }
};

template <typename T>
typename MojVector<T>::Iterator MojVector<T>::erase(Iterator pos) {
  auto e = end() - 1;
  for (auto it = pos; it < e; ++it) {
    *it = *(it + 1);
  }
  size_--;
  return pos;
}

template <typename T>
typename MojVector<T>::Iterator MojVector<T>::erase(
    MojVector<T>::Iterator beginIt, MojVector<T>::Iterator endIt) {
  for (auto it = endIt - 1; it >= beginIt; --it) {
    erase(it);
  }
  return Iterator{begin()};
}
