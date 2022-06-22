#include <fstream>
#include <iostream>
#include "stack.hpp"

bool otvorena_zagrada(char c) {
  return c == '<' || c == '(' || c == '[' || c == '{';
}

bool zatvorena_zagrada(char c) {
  return c == '>' || c == ')' || c == ']' || c == '}';
}

bool podudarne_zagrade(char lijeva, char desna) {
  return (lijeva == '<' && desna == '>') || (lijeva = '(' && desna == ')') ||
         (lijeva == '[' && desna == ']') || (lijeva == '{' && desna == '}');
}

int main(void) {
  Stack<char> zagrade;
  char c;
  while (std::cin >> c) {
    if (otvorena_zagrada(c)) {
      zagrade.push(c);
    } else if (zatvorena_zagrada(c)) {
      if (!zagrade.empty() && podudarne_zagrade(zagrade.top(), c)) {
        zagrade.pop();
      } else {
        std::cout << "Zagrade nisu pravilno rasporedjene" << std::endl;
        return 1;
      }
    }
  }
  if (zagrade.empty()) {
    std::cout << "Zagrade su pravilno rasporedjene" << std::endl;
  } else {
    std::cout << "Zagrade nisu pravilno rasporedjene" << std::endl;
  }

  return 0;
}
