#pragma once
#include <algorithm>
#include <iterator>
#include <iostream>
#include <type_traits>

template <typename T>
class Array {
  public:
  Array() = default;

  Array(const std::size_t kapacitet)
      : kapacitet_{kapacitet}, velicina_{0}, elementi_{new T[kapacitet_]} {}

  // copy konstruktor
  Array(const Array& drugi)
      : kapacitet_{drugi.kapacitet_},
        velicina_{drugi.velicina_},
        elementi_{new T[kapacitet_]} {
    for (auto i = 0; i < velicina_; ++i) {
      elementi_[i] = drugi.elementi_[i];
    }
  }

  // move konstruktor, isti kao copy samo sto umjesto da unistimo
  // dinamicki alocirani niz, prihvatimo ga kao svoj
  Array(Array&& drugi)
      : kapacitet_{drugi.kapacitet_},
        velicina_{drugi.velicina_},
        elementi_{drugi.elementi_} {
    drugi.elementi_ = nullptr;
    drugi.kapacitet_ = drugi.velicina_ = 0;
  }

  // copy assignment je ustvari operator =, i on za razliku od
  // copy konstruktora mora vratiti referencu. Isto tako ne smijemo
  // imati listu za inicijalizaciju nego sve moramo pisati u bloku
  Array& operator=(const Array& drugi) {
    delete[] elementi_;

    kapacitet_ = drugi.kapacitet_;
    velicina_ = drugi.velicina_;
    elementi_ = new T[kapacitet_];

    for (auto i = 0; i < velicina_; ++i) {
      elementi_[i] = drugi.elementi_[i];
    }
    return *this;
  }

  // move assignment - slican kao move konstruktor, ali implementiramo
  // operator =. Moramo vratiti referencu
  Array& operator=(Array&& drugi) {
    if (this == &drugi) return *this;
    delete[] elementi_;  // ove dvije linije koda radimo radi
    // self assignmenta

    kapacitet_ = drugi.kapacitet_;
    velicina_ = drugi.velicina_;
    elementi_ = drugi.elementi_;

    drugi.elementi_ = nullptr;
    drugi.kapacitet_ = drugi.velicina_ = 0;

    return *this;
  }

  ~Array() { delete[] elementi_; }

  // implementacija push_backa
  void push_back(const T& novi_elem) {
    if (velicina_ == kapacitet_) {
      throw std::out_of_range{"Dostignut je maksimalni kapacitet."};
    }
    elementi_[velicina_] = novi_elem;
    ++velicina_;
  }

  // implementacija pop_backa koji nam smanjuje velicinu niza za 1
  void pop_back() {
    if (velicina_ > 0) {
      velicina_--;
    }
  }

  // implementacija cleara() gdje velicinu setujemo na 0,
  // a kapacitet i pointer ne diramo jer cemo mozda zeljeti ponovo
  // unijeti nesto u nas niz
  void clear() { velicina_ = 0; }

  // implementacija operatora []
  T& operator[](size_t index) { return elementi_[index]; }
  const T& operator[](size_t index) const { return elementi_[index]; }

  // implementacija metoda at
  T& at(size_t index) {
    if (index >= velicina_) {
      throw std::out_of_range(
          "Proslijedjeni indeks se nalazi izvan granica niza");
    }
    return elementi_[index];
  }

  const T& at(size_t index) const {
    if (index >= velicina_) {
      throw std::out_of_range(
          "Proslijedjeni indeks se nalazi izvan granica niza");
    }
    return elementi_[index];
  }

  // implementacija fronta i backa, front vraca referencu na prvi elem niza
  // a back vraca referencu na zadnji elem niza
  T& front() { return elementi_[0]; }

  T& back() { return elementi_[velicina_ - 1]; }

  const T& front() const { return elementi_[0]; }

  const T& back() const { return elementi_[velicina_ - 1]; }

  // metod empty
  bool empty() const { return velicina_ == 0; }

  // metod size koji nam vraca velicinu niza
  size_t size() const { return velicina_; }

  // metod sort, primamo lambda funkciju u sort
  template <typename F>
  void sort(F func) {
    std::sort(elementi_, elementi_ + velicina_, func);
  }

  // ITERATOR
  class iterator{
  private:
    T* p_;

  public:
    //petorka za iteratore da bi mogli raditi u algoritmima, ili ljepse je da se
    //gore u listi za inicijalizaciji ovo navede poslije class iterator : ...
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using reference = T&;
    using pointer = T*;
    using difference_type = size_t;

    // konstruktor
    iterator(T* p) : p_{p} {}

    // ++iter -> referenca na sebe
    iterator& operator++() {
      ++p_;
      return *this;
    }

    // iter++ -> vrijednost novog iteratora
    iterator operator++(int) { return iterator{p_++}; }
  
    // --iter -> referenca na sebe

    iterator& operator--() {
      --p_;
      return *this;
    }

    // iter-- -> vrijednost novog iteratora
    iterator operator--(int) { return iterator{p_--}; }


    //operator dereferenciranja *
    T& operator*(){
      return *p_;
    }

    bool operator != (const iterator& drugi){
      return p_ != drugi.p_;
    }
    bool operator == (const iterator& drugi){
      return p_ == drugi.p_;
    }
    bool operator < (const iterator& drugi){
      return p_ < drugi.p_;
    }


    iterator operator+(int n) {
      return iterator{p_ + n};
    }

    iterator operator-(int n) {
      return iterator{p_ + n};
    }


    //oduzimanje 2 iteratora
    //kad ih oduzimemo dobijemo neki broj, odnosno njihovu razdaljinu
    size_t operator-(const iterator& drugi) {
      return p_ - drugi.p_; 
    }

  };

  iterator begin() {
    return iterator{elementi_};
  }

  iterator end() {
    return iterator{elementi_ + velicina_};
  }

  private:
  std::size_t kapacitet_ = 100;
  std::size_t velicina_ = 0;
  int* elementi_ = new T[kapacitet_];  // pointer na prvi element niza

  // u private sekciji clanovi su inicijalizirani na 0,0,nullptr iz razloga
  // sto kada se pozove defaultni konstruktor pointer mora biti nullptr
  // inace ne znamo gdje gleda nas pointer

  // ovo je bilo prije videa3, sada kada default konstruisemo nas niz setujemo
  // ga da ima 100 elemenata, i dodijelili smo mu dinamicku alokaciju
};

