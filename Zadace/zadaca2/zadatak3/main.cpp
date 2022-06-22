#include <algorithm>
#include <iostream>
#include "automobil.hpp"
#include "osoba.hpp"
#include "vozac.hpp"

#include "../zadatak1/MojVektor.hpp"

std::istream& operator>>(std::istream& ulaz, Vozac& vozac) {
  std::string unos;
  int godine;
  Automobil automobil;
  double vrijeme;

  // Unos osobe
  std::cout << "Unesite ime, prezime, godine od vozaca, te godine staza vozaca:"
            << std::endl;
  ulaz >> unos;
  vozac.setIme(unos);
  ulaz >> unos;
  vozac.setPrezime(unos);
  ulaz >> godine;
  vozac.setGodine(godine);
  ulaz >> godine;
  vozac.setGodineStaza(godine);

  // Unos automobila
  std::cout << "Unesite model, boju i godiste automobila:" << std::endl;
  ulaz >> unos;
  automobil.setModel(unos);
  ulaz >> unos;
  automobil.setBoja(unos);
  ulaz >> godine;
  automobil.setGodiste(godine);

  vozac.setAutomobil(automobil);

  std::cout << "Unesite vrijeme vozaca:" << std::endl;
  ulaz >> vrijeme;
  vozac.setVrijeme(vrijeme);

  return ulaz;
}

int main(void) {
  int brojac;
  Vozac v;

  std::cout << "Unesite broj vozaca: " << std::endl;
  std::cin >> brojac;

  MojVector<Vozac> vozaci(brojac);

  for (auto i = 0; i < brojac; ++i) {
    std::cin >> v;
    vozaci.push_back(v);
  }

  vozaci.sort([](const Vozac& prvi, const Vozac& drugi) {
    return prvi.getVrijeme() < drugi.getVrijeme();
  });

  std::cout << std::endl;

  for (auto i = 0; i < brojac; ++i) {
    std::cout << vozaci[i] << std::endl;
  }

  return 0;
}
