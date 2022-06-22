#include "studenti.hpp"

short getOption() {
  short option;
  do {
    std::cout << "Vas izbor: " << std::endl;
    std::cin >> option;
    if (option < 1 || option > 6) {
      std::cout << "Nema te opcije, pokusajte ponovo" << std::endl;
    }
  } while (option < 1 || option > 6);
  return option;
}

void dodajStudenta() {
  unordered_map studenti;
  std::string unosIndexa, unosImena, unosPrezimena;

  std::cout << "Unesite index, ime i prezime studenta: " << std::endl;
  std::cin >> unosIndexa >> unosImena >> unosPrezimena;

  auto s1 = Student{unosIndexa, unosImena, unosPrezimena};
  studenti.insert(s1.index, s1);
}

int main(void) {
  unordered_map studenti;

  while (1) {
    std::cout << "--------------------------" << std::endl;
    std::cout << "Opcije" << std::endl;
    std::cout << "\t1. Dodaj studenta" << std::endl;
    std::cout << "\t2. Izadji" << std::endl;

    switch (getOption()) {
      case 1:
        dodajStudenta();
      case 2:
        return 0;
        break;
    }

  }

  return 0;
}
