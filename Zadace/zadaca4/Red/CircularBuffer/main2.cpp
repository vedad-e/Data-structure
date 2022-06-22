#include <iostream>
#include "circular.hpp"

int main(int argc, char* argv[]) {
  Queue<int> buffer;
  buffer.push(1).push(2).push(3);
  buffer.push(4).push(5).push(6);
  buffer.transform([](int x){return x*2;});
  std::cout << buffer;
  std::cout << buffer.front() << std::endl;
  std::cout << buffer.back() << std::endl;
  std::cout << std::endl;

  buffer.pop();
  buffer.pop();
  buffer.pop();
  buffer.pop();
  std::cout << buffer;
  std::cout << buffer.front() << std::endl;
  std::cout << buffer.back() << std::endl;
  std::cout << std::endl;

  buffer.push(7).push(8).push(9);
  buffer.push(10).push(11).push(12);
  std::cout << buffer;
  std::cout << buffer.front() << std::endl;
  std::cout << buffer.back() << std::endl;
  std::cout << std::endl;

  buffer.pop();
  buffer.pop();
  buffer.pop();
  buffer.pop();
  buffer.pop();
  buffer.pop();
  buffer.pop();
  std::cout << buffer;
  std::cout << buffer.front() << std::endl;
  std::cout << buffer.back() << std::endl;
  std::cout << std::endl;

  buffer.push(13).push(14).push(15);
  buffer.push(16).push(17).push(18);
  buffer.push(19).push(20).push(21);
  //   buffer.pop();
  //   buffer.pop();
  //   buffer.pop();
  //   buffer.pop();

  std::cout << buffer;
  std::cout << buffer.front() << std::endl;
  std::cout << buffer.back() << std::endl;
  std::cout << std::endl;

  return 0;
}
