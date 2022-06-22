#include "heap.hpp"

int main(void) {
  Heap<int> heap1(3);
  Heap<int> heap2;

  heap2 = heap1;
  heap2 = std::move(heap1);

  try {
    heap2.max();
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  heap2.insert(14);
  heap2.insert(20);
  heap2.insert(29);
  heap2.insert(1);
  heap2.insert(50);
  heap2.insert(31);
  heap2.insert(3);

  std::cout << std::endl;

  std::cout << "Ispis elemenata" << std::endl;
  std::cout << heap2;
  std::cout << std::endl;

  std::cout << "Brisanje najmanjeg elementa" << std::endl;
  heap2.removeMin();
  std::cout << "Ispis nakon brisanja najmanjeg elementa" << std::endl;
  heap2.printHeap();
  std::cout << std::endl;

  std::cout << "Brisanje najveceg elementa" << std::endl;
  heap2.removeMax();
  std::cout << "Ispis nakon brisanja najveceg elementa" << std::endl;
  heap2.printHeap();
  std::cout << std::endl;

  std::cout << "Najmanji element: " << heap2.min() << std::endl;

  std::cout << "Najveci element:" << heap2.max() << std::endl;

  return 0;
}
