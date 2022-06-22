#pragma once
#include <iostream>
#include <string>
#include "stack.hpp"

class PostfixCalc {
  private:
  Stack<double> rpn_stack;
  bool is_operator(const std::string &);
  bool is_number(const std::string &);
  double do_operation(const std::string &);

  public:
  double parse(const std::string &);
};
