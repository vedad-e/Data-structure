#include <iostream>
#include "circularBuffer.hpp"

int main(void) {
  CircularBuffer<int> buffer;
  buffer.push(1).push(2);
  buffer.push(3).push(4);
  buffer.push(5).push(6);

  std::cout << buffer << std::endl;
  buffer.pop();
  buffer.pop();
  buffer.pop();
  buffer.pop();

  std::cout << buffer << std::endl;
  buffer.push(1).push(2);
  buffer.push(3).push(4);
  buffer.push(5).push(6);

  std::cout << buffer << std::endl;

  buffer.pop();
  buffer.pop();
  buffer.pop();
  buffer.pop();
  buffer.pop();
  buffer.pop();
  buffer.pop();
  std::cout << buffer << std::endl;
  buffer.push(1).push(2);
  buffer.push(3).push(4);
  buffer.push(5).push(6);

  std::cout << buffer << std::endl;

  return 0;
}
