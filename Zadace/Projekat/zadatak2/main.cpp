#include "unorderedmap.hpp"

int main(void) {
  unordered_map mapa;

  mapa.emplace("kljuc1", "vrijednost1");
  mapa.emplace("kljuc2", "vrijednost2");
  mapa.emplace("kljuc3", "vrijednost3");
  mapa["kljuc1"] = "novaVrijednost1";

  auto it = mapa.find("kljuc1");
  std::cout << "Vrijednost kljuca1: " << mapa["kljuc1"] << std::endl;
  std::cout << "Size vrijednosti od kljuca1: " << it->size() << std::endl;

  bool erased = mapa.erase("kljuc1");
  if(erased){
    std::cout << "Element izbrisan" << std::endl;
  }
  return 0;
}

