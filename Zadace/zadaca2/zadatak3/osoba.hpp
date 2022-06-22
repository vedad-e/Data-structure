#pragma once
#include <string>

class Osoba{
  public:

    Osoba() = default;

    Osoba(const std::string& ime, const std::string& prezime, int godine)
      : ime_{ime}, prezime_{prezime}, godine_{godine} {}

    const std::string& getIme() const {return ime_;}
    void setIme(const std::string& i) {ime_ = i;}
    
    const std::string& getPrezime() const {return prezime_;}
    void setPrezime(const std::string& p) {prezime_ = p;}

    const int& getGodine() const {return godine_;}
    void setGodine(const int& g) {godine_ = g;}


  private:
    std::string ime_;
    std::string prezime_;
    int godine_;
};


