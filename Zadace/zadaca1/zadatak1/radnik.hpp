#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class Radnik{
  public:
    Radnik() = default;

    Radnik(const std::string& ime, const std::string& prezime, int godineStarosti,
        int godineStaza, int plata, std::string brojTelefona)
      : ime_{ime}, prezime_{prezime}, godineStarosti_{godineStarosti},
      godineStaza_{godineStaza}, plata_{plata}, brojTelefona_{brojTelefona} {} 

    const std::string& getIme() const {return ime_;}
    void setIme(const std::string& i) {ime_ = i;}

    const std::string& getPrezime() const {return prezime_;}
    void setPrezime(const std::string& p) {prezime_ = p;}

    const int& getGodineStarosti() const {return godineStarosti_;}
    void setGodineStarosti(const int& gs) {godineStarosti_ = gs;}
    
    const int& getGodineStaza() const {return godineStaza_;}
    void setGodineStaza(const int& gst) {godineStaza_ = gst;}
    
    const int& getPlata() const {return plata_;}
    void setPlata(const int& p) {plata_ = p;}
    
    const std::string& getBrojTelefona() const {return brojTelefona_;}
    void setBrojTelefona(const std::string& brt) {brojTelefona_ = brt;}


  private:
    std::string ime_;
    std::string prezime_;
    int godineStarosti_;
    int godineStaza_;
    int plata_;
    std::string brojTelefona_;

};


std::ostream& operator <<(std::ostream& out, Radnik& radnik);


std::vector<std::string> ucitaj(const char*, const char*);


void upis(std::vector<std::string>&);

std::vector<Radnik> r();

void sortiranje(std::vector<Radnik>&);
