#include <algorithm>
#include <iostream>
#include "array.h"

int main(int argc, char *argv[]) {
  Array<int> moja_lista;

  moja_lista.push_back(1);
  moja_lista.push_back(2);

  if (moja_lista.size() != 0) {
    std::cout << "Broj elemenata: " << moja_lista.size() << std::endl;
  } else {
    std::cout << "Lista je prazna!!" << std::endl;
  }

  moja_lista.push_back(3);
  std::cout << moja_lista.front() << std::endl;
  std::cout << moja_lista.back() << std::endl;
  moja_lista.front() *= 100;
  std::cout << moja_lista.front() << std::endl;

  std::cout << std::endl;

  std::cout << "Pop back:" << std::endl;
  std::cout << "Broj elemenata: " << moja_lista.size() << std::endl;
  moja_lista.pop_back();
  std::cout << "Broj elemenata: " << moja_lista.size() << std::endl;

  moja_lista.clear();
  std::cout << "Broj elemenata: " << moja_lista.size() << std::endl;

  std::cout << std::endl;

  moja_lista.push_back(1);
  moja_lista.push_back(2);
  moja_lista.push_back(3);
  moja_lista.push_back(4);
  moja_lista.push_back(5);
  moja_lista.push_back(6);
  moja_lista.push_back(7);
  moja_lista.push_back(8);
  moja_lista.push_back(9);
  moja_lista.push_back(10);
  std::cout << "Broj elemenata: " << moja_lista.size() << std::endl;

  std::cout << std::endl;

  // copy ctor
  // Array<int> list2(moja_lista);
  // Array<int> list2 = moja_lista;
  Array<int> list2{moja_lista};

  // move ctor
  {
    // ctor list2
    Array<int> list2{moja_lista};

    // std::move - napravi R&& za list2
    // lista3 ctor
    Array<int> list3 = std::move(list2);

    // dtor list3
    // dtor list2
  }

  // copy assignment
  list2 = moja_lista;

  // move assignment
  Array<int> list3 = std::move(list2);

  list2 = std::move(list3);
  for (size_t i = 0; i < list2.size(); i++) {
    std::cout << list2[i] << std::endl;
  }

  // self assignment
  list2 = std::move(list2);

  std::cout << "Ispis sadzaja list2" << std::endl;
  for (size_t i = 0; i < list2.size(); i++) {
    std::cout << list2[i] << std::endl;
  }
  //

  // iteratori
  for (auto iter = moja_lista.begin(); iter != moja_lista.end(); ++iter) {
    std::cout << *iter << std::endl;
  }

  // find - potreban operator- iter - iter
  auto iter = std::find(moja_lista.begin(), moja_lista.end(), 5);
  if (iter != moja_lista.end()) {
    std::cout << "clan postoji: " << *iter << std::endl;
  }

  // partition - potreban operator-- i operator==
  // partition prima lambda izraz koji treba vratiti true/false
  // u nasem slucaju to je return el%2
  // pretumbat ce nase clanve i na pocetak liste stavlja one elemente nad
  // kojim je zadovoljen uslov
  std::partition(moja_lista.begin(), moja_lista.end(),
                 [](auto el) { return el % 2; });
  std::cout << "Nakon partitiona" << std::endl;
  for (auto iter = moja_lista.begin(); iter != moja_lista.end(); ++iter) {
    std::cout << *iter << std::endl;
  }

    // sort - potrebni operaori iter + n, iter - n, iter < iter
    std::sort(moja_lista.begin(), moja_lista.end());
    std::cout << "Nakon sorta" << std::endl;
    for (auto iter = moja_lista.begin(); iter != moja_lista.end(); ++iter) {
      std::cout << *iter << std::endl;
    }

  return 0;
}
