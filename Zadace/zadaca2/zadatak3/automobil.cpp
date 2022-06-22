#include <iostream>
#include "automobil.hpp"

std::ostream& operator << (std::ostream& out, const Automobil& automobil){
  return out << 
    automobil.getModel() << " " <<
    automobil.getBoja() << " " <<
    automobil.getGodiste();
}
