#include "radnik.hpp"

std::ostream& operator <<(std::ostream& out, Radnik& radnik){
  return out <<
    radnik.getIme() << " " <<
    radnik.getPrezime() << " " <<
    radnik.getGodineStarosti() << " " <<
    radnik.getGodineStaza() << " " <<
    radnik.getPlata() << " " <<
    radnik.getBrojTelefona() << " ";
}


std::vector<std::string> ucitaj(const char* imeFajla, const char* imeFajla2){

  std::ifstream acme{imeFajla};
  std::ifstream globex{imeFajla2};
  std::vector<std::string> corp_radnici;
  std::string a,b;

  while(std::getline(acme, a, ',')){
    corp_radnici.push_back(a);
  }
  acme.close();
  std::cin.clear();

  while(std::getline(globex, b, ',')){
    corp_radnici.push_back(b);
  }
  globex.close();

  return corp_radnici;
}


void upis(std::vector<std::string>& u) {
  std::ofstream corp{"corp.txt"}; 
  for (auto& a : u) corp << a << " " ;

}

std::vector<Radnik> r(){
  std::vector<Radnik> radnici;
  Radnik radnik;
  std::ifstream unos{"corp.txt"};
  std::string a;
  int d;

  while(!unos.eof()){
    unos >> a;
    radnik.setIme(a);

    unos >> a;
    radnik.setPrezime(a);

    unos >> d;
    radnik.setGodineStarosti(d);

    unos >> d;
    radnik.setGodineStaza(d);

    unos >> d;
    radnik.setPlata(d);
    
    unos >> a;
    radnik.setBrojTelefona(a);
  }
  unos.close();

  return radnici;
  
}

void sortiranje(std::vector<Radnik>& v){
 std::sort(v.begin(), v.end(), [](Radnik prvi, Radnik drugi){
      return prvi.getGodineStarosti() < drugi.getGodineStarosti();
      });
  
  for(auto& a : v){
    if(a.getGodineStarosti() >= 55)
      a.setBrojTelefona("Penzija");
    if(a.getGodineStaza() >= 15){
      int povecanje = a.getPlata();
      a.setPlata(povecanje + (povecanje*20/100));
    }
  } 
/*
  for(auto i=0; i<15; ++i){
    auto povecanje = v[i].getPlata();
    v[i].setPlata(povecanje+(povecanje*10/100));
  }
  */

  std::sort(v.begin(), v.end(), [](Radnik prvi, Radnik drugi){
        return prvi.getIme() < drugi.getIme();
      });


}
