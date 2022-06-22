#include "PostfixCalc.hpp"
#include <cstddef>
#include <sstream>

double PostfixCalc::parse(const std::string& exp) {
  std::istringstream ss(exp);
  std::string op;
  while (ss >> op) {
    if (is_operator(op)) {
      return do_operation(op);
    } else if (is_number(op)) {
      char* p;
      rpn_stack.push(strtod(op.c_str(), &p));
    }
  }
  throw "Expression not valid !";
}
