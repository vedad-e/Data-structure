#include <iostream>
#include "vozac.hpp"

std::ostream& operator << (std::ostream& out, const Vozac& vozac){
  return out << 
    vozac.getIme() << " " <<
    vozac.getPrezime() << " " <<
    vozac.getGodine() << " " <<
    vozac.getGodineStaza() << " " <<
    vozac.getAutomobil() << " " <<
    vozac.getVrijeme() << " ";
}
