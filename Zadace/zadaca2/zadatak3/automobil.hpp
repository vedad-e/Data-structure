#pragma once
#include <string>

class Automobil{
  public:
    Automobil() = default;

    Automobil(const std::string& model, const std::string& boja, int godiste)
      : model_{model}, boja_{boja}, godiste_{godiste} {}

    const std::string& getModel() const {return model_;}
    void setModel(const std::string& m) {model_ = m;}
    
    const std::string& getBoja() const {return boja_;}
    void setBoja(const std::string& b) {boja_ = b;}

    const int& getGodiste() const {return godiste_;}
    void setGodiste(const int& g) {godiste_ = g;}

  private:
    std::string model_;
    std::string boja_;
    int godiste_ = 1999;
};

std::ostream& operator << (std::ostream& out, const Automobil& automobil);
