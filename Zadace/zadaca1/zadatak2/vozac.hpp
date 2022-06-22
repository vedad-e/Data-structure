#pragma once
#include "osoba.hpp"
#include "automobil.hpp"

class Vozac : public Osoba{
  public:
    Vozac() = default;

    Vozac(const std::string& ime, const std::string& prezime, int godine,
        int godineStaza, const Automobil& automobil, double vrijeme) 
      : Osoba{ime, prezime, godine}, godineStaza_{godineStaza}, auto_{automobil}, vrijeme_{vrijeme}
    {}
    

    const int& getGodineStaza() const {return godineStaza_;}
    void setGodineStaza(const int& gs) {godineStaza_ = gs;}
    
    const Automobil& getAutomobil() const {return auto_;}
    void setAutomobil(const Automobil& a) {auto_ = a;}

    const double& getVrijeme() const {return vrijeme_;}
    void setVrijeme(const double& v) {vrijeme_ = v;}



  private:
    int godineStaza_;
    Automobil auto_;
    double vrijeme_;

};

std::ostream& operator << (std::ostream& out, const Vozac& vozac);
