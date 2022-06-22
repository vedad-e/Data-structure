#include <algorithm>
#include <iostream>
#include <vector>

void print(const std::vector<int>& v) {
  for (int item : v) std::cout << item << std::endl;
  std::cout << std::endl;
}

int main(void) {
  std::vector<int> h{2, 7, 26, 25, 29, 17, 1};

  std::cout << "Prije make heap" << std::endl;
  print(h);
  std::make_heap(h.begin(), h.end());
  std::cout << "Poslije make heap" << std::endl;
  print(h);

  h.push_back(90);
  std::push_heap(h.begin(), h.end());
  print(h);

  h.push_back(3);
  std::push_heap(h.begin(), h.end());
  h.push_back(36);
  std::push_heap(h.begin(), h.end());

  print(h);

  std::pop_heap(h.begin(), h.end());
  print(h);

  std::cout << "Extract max " << std::endl;
  h.pop_back();

  std::pop_heap(h.begin(), h.end());
  std::cout << "Extract max " << std::endl;
  h.pop_back();

  print(h);

  return 0;
}
