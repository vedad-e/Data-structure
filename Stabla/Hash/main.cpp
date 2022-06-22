#include <iostream>
#include <vector>

size_t hash(const int& s) { return s; }

size_t hash(const std::string& s){
  size_t sum = 5381;
  for(char c : s){
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

struct Student {
  std::string index;
  std::string ime;
  std::string prezime;
};

class unordered_map {
  public:
  using key_type = std::string;
  using mapped_type = Student;

  unordered_map() { storage_.resize(storage_size); }

  void insert(const key_type& key, Student value) {
    auto index = hash(key) % storage_size;
    storage_[index] = std::move(value);
  }

  mapped_type& operator[](const key_type& key) {
    auto index = hash(key) % storage_size;
    return storage_[index];
  }

  void find() {}

  bool erase() {}

  private:
  std::vector<Student> storage_;
  const static int storage_size = 1000;
};

int main(void) {
  unordered_map studenti;

  std::cout << "Hash od 14137 je " << hash("14137") << std::endl;
  std::cout << "Hash od 14037 je " << hash("14037") << std::endl;

  auto s1 = Student{"14137", "Samir", "Halilcevic"};
  auto s2 = Student{"14037", "Asmir", "Halilcevic"};

  studenti.insert(s1.index, s1);
  studenti.insert(s2.index, s2);

  return 0;
}

