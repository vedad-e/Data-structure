#include <iostream>
#include <string>
#include "stablo.hpp"


int main(void) {
  Tree<int> moj_tree;

  moj_tree.insert(5);
  moj_tree.insert(1);
  moj_tree.insert(2);
  moj_tree.insert(3);
  moj_tree.insert(10);
  moj_tree.insert(11);
  moj_tree.insert(12);

  moj_tree.print();

  std::cout << "Dubina " << moj_tree.depth() << std::endl;

  auto it = moj_tree.find(3);
  if (it) {
    std::cout << "Pronadjen je element " << it->value << std::endl;
  } else {
    std::cout << "Nismo pronasli element" << std::endl;
  }
  it = moj_tree.find(12);
  if (it) {
    std::cout << "Pronadjen je element " << it->value << std::endl;
  } else {
    std::cout << "Nismo pronasli element" << std::endl;
  }
  it = moj_tree.find(16);
  if (it) {
    std::cout << "Pronadjen je element " << it->value << std::endl;
  } else {
    std::cout << "Nismo pronasli element" << std::endl;
  }

  std::cout << "Copy ctor" << std::endl;
  auto moj_tree1 = moj_tree;
  std::cout << "mojtree ";
  moj_tree.print();
  std::cout << "mojtree1 ";
  moj_tree.print();

  std::cout << "Move ctor" << std::endl;
  auto moj_tree2 = std::move(moj_tree);
  std::cout << "mojtree2 ";
  moj_tree2.print();

  std::cout << "Copy=" << std::endl;
  moj_tree = moj_tree1;
  std::cout << "mojtree ";
  moj_tree.print();

  std::cout << "Move=" << std::endl;
  std::cout << "mojtree ";
  moj_tree = std::move(moj_tree1);
  moj_tree.print();

//  moj_tree.clear();
  
  moj_tree.print();

  moj_tree.erase(10);
  moj_tree.print();

  return 0;
}
