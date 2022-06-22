#include <iostream>

#include "list.hpp"

/*
void print(const List<std::string>& lista) {
  for (auto it = lista.begin(); it != lista.end(); ++it) {
    std::cout << *it << std::endl;
  }
}
*/

int main(void) {
  List<int> moja1;

  moja1.push_back(2);
  moja1.push_back(3);
  moja1.push_back(4);

  auto moja2 = moja1;
  auto moja3 = std::move(moja1);
  moja2 = std::move(moja3);

  std::cout << moja2.at(1) << std::endl;

  std::cout << std::endl;

  moja2.pop_back();
  moja2.pop_front();
  for (auto i = 0; i < moja2.size(); ++i) {
    std::cout << moja2.at(i) << std::endl;
  }

  std::cout << "Iteratori" << std::endl;
  auto begin = moja2.begin();
  std::cout << *begin << std::endl;
  std::cout << ++*begin << std::endl;

  std::cout << "Iteratori 2" << std::endl;
  for (auto iter = moja2.begin(); iter != moja3.end(); ++iter) {
    std::cout << *iter << std::endl;
  }

  // OD NOVOG VIDEA

  List<std::string> lista;
  std::string unos;
  lista.push_back("Vedad");
  lista.push_back("Eleskovic");
  lista.push_back("1999");

  /*
  while (std::cin >> unos) {
    lista.push_back(unos);
  }

  for (auto it = lista.begin(); it != lista.end(); ++it) {
    std::cout << *it << std::endl;
  }
  */

  auto pos = lista.begin();
  pos++;
  pos++;
  lista.insert(pos, "Zadaca");
  lista.erase(++lista.begin());
  lista.erase(lista.begin());

  for (auto it = lista.begin(); it != lista.end(); ++it) {
    std::cout << *it << std::endl;
  }

  return 0;
}
