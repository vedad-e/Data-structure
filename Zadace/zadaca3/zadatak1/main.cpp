#include <iostream>
#include "list.hpp"

int main(void) {
  List<int> moja1;
  moja1.push_back(5);
  moja1.push_back(1);
  moja1.push_back(3);
  moja1.push_back(9);
  moja1.add(8);
  moja1.remove(moja1.begin());

  moja1.transform([](int a) { std::cout << a << std::endl; });

  for (auto it = moja1.begin(); it != moja1.end(); ++it) {
    std::cout << *it << std::endl;
  }

  std::cout << "Testiranje finda" << std::endl;
  auto it = moja1.find([](int a) { return a == 80; });
  if (it != moja1.end()) {
    std::cout << *it << std::endl;
  } else {
    std::cout << "Ne postoji" << std::endl;
  }
  std::cout << "----" << std::endl;

  return 0;
}
