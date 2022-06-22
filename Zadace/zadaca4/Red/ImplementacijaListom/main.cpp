#include "queue.hpp"

int main(void) {
  Queue<int> q;

  q.push(1);
  q.print(std::cout);

  q.pop();

  std::cout << q.top() << std::endl;
  q.print(std::cout);

  return 0;
}
