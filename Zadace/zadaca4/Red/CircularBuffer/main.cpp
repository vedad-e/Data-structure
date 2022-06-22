#include "CircularBufferDzemo.hpp"

int main(void)
{
  using Types::CircularBuffer;
  CircularBuffer<int> cb;
  cb.push(1).push(2).push(3).push(4).push(5);
//  cb.push(11);

  cb.pop();
  cb.pop();
  cb.pop();

  cb.push(11);

  std::cout << cb << std::endl;

 // std::cout << cb.front() << std::endl;
 // std::cout << cb.back() << std::endl;
  return 0;
}
