#include "stack.hpp"

int main(void)
{
  Stack<int> s;
  s.push(1);
  s.push(2);
  s.push(3);

  std::cout << s.top() << std::endl;
  s.pop();
  std::cout << s.top() << std::endl;
  return 0;
}
