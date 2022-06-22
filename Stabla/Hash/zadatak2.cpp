#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
// OVDJE SE RADI OPEN HASHING

size_t hash(const int& s) { return s; }

size_t hash(const std::string& s) {
  size_t sum = 5381;
  for (char c : s) {
    sum += (sum << 4) + c;
  }
  return sum;
}

/*
size_t hash(const std::string& s) {
  size_t sum = 0;
  for (char c : s) {
    sum += c;
  }
  return sum;
}
*/

class unordered_map {
  public:
  using key_type = std::string;
  using mapped_type = std::string;
  using value_type = std::pair<key_type, mapped_type>;
  using bucket_type = std::list<value_type>;

  unordered_map() { storage_.resize(storage_size); }

  void insert(const key_type& key, std::string value) {
    auto index = hash(key) % storage_size;
    auto& bucket = storage_[index];
    bucket.push_back(value_type{key, std::move(value)});
  }

  mapped_type& operator[](const key_type& key) {
    auto index = hash(key) % storage_size;
    auto& bucket = storage_[index];
    // ovdje u ovoj petlji ispod par predstavlja gore value_type
    // a first je string iz value_type, second je Mapa iz value type
    for (auto& par : bucket) {
      if (par.first == key) {
        return par.second;
      }
    }
    throw std::runtime_error("Nismo nasli elem");
  }

  mapped_type* find(const key_type& key) {
    auto index = hash(key) % storage_size;
    auto& bucket = storage_[index];

    auto it = find_if(bucket.begin(), bucket.end(),
                      [&key](const auto& el) { return el.first == key; });

    if (it != bucket.end()) {
      std::cout << "Nasli smo element" << std::endl;
      return &it->second;
    } else {
      std::cout << "Nismo nasli element" << std::endl;
      return nullptr;
    }
  }

  bool erase(const key_type& key) {
    auto index = hash(key) % storage_size;
    auto& bucket = storage_[index];

    auto it = find_if(bucket.begin(), bucket.end(),
                      [&key](const auto& el) { return el.first == key; });

    if (it != bucket.end()) {
      bucket.erase(it);
      return true;
    } else {
      return false;
    }
  }

  private:
  std::vector<bucket_type> storage_;
  const static int storage_size = 1000;
};

int main(void) {
  unordered_map mapa;
  mapa.insert("kljuc1", "vrijednost1");
  mapa["kljuc1"] = "vrijednost2";
  auto it2 = mapa.begin();

  auto it = mapa.find("kljuc1");
  std::cout << mapa["kljuc1"] << std::endl;
  std::cout << it->size() << std::endl;

  bool erased = mapa.erase("kljuc1");
  if(erased){
    std::cout << "Element izbrisan" << std::endl;
  }
  return 0;
}

