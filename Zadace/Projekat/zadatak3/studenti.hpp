#pragma once
#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

size_t hash(const int& s) { return s; }

size_t hash(const std::string& s) {
  size_t sum = 5381;
  for (char c : s) {
    sum += (sum << 4) + c;
  }
  return sum;
}

struct Student {
  std::string index;
  std::string ime;
  std::string prezime;
};

class unordered_map {
  public:
  using key_type = std::string;
  using mapped_type = Student;
  using value_type = std::pair<key_type, mapped_type>;
  using bucket_type = std::list<value_type>;

  unordered_map() { storage_.resize(storage_size); }

  void insert(const key_type& key, Student value) {
    auto index = hash(key) % storage_size;
    auto& bucket = storage_[index];
    bucket.push_back(value_type{key, std::move(value)});
  }

  mapped_type& operator[](const key_type& key) {
    auto index = hash(key) % storage_size;
    auto& bucket = storage_[index];
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
