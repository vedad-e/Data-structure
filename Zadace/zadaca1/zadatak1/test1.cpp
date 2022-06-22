#include <iostream>
#include "radnik.hpp"


int main(int argc, char *argv[]){
  auto ucitavanje = ucitaj("acme.txt", "globex.txt");
  upis(ucitavanje);
  auto radnici = r();
  sortiranje(radnici);
}
