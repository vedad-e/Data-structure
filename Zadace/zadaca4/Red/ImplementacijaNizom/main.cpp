#include "queue.hpp"

int main(void)
{
  Queue<int> queue;
  queue.push(1).push(2).push(3);

  queue.print();

  queue.pop();

  queue.print();
  return 0;
}
