#include <iostream>
#include "MojVektor.hpp"

// funkcija print za ispis elemenata niza
template <typename U>
void print(const MojVector<U>& niz) {
  for (auto i = 0; i < niz.size(); ++i) {
    std::cout << niz[i] << std::endl;
  }
}

int main(void) {
  MojVector<int> moj{100};

  moj.push_back(2);
  moj.push_back(3);

  MojVector<int> moj2{moj};

  print(moj);
  std::cout << std::endl;

  for (auto it = moj.begin(); it != moj.end(); ++it) {
    std::cout << *it << std::endl;
  }

  return 0;
}
