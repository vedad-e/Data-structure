#pragma once

#include <iostream>

struct Node {
  Node(int v) : value{v} {}
  int value;
  Node* l_link = nullptr;
  Node* r_link = nullptr;
};

class Tree {
  private:
  Node* root_ = nullptr;
  size_t size_ = 0;

  void print_subtree(Node* root) const {
    if (root == nullptr) {
      return;
    }
    std::cout << root->value << " ";
    print_subtree(root->l_link);
    print_subtree(root->r_link);
  }

  int depth(Node* current) const {
    if (current == nullptr) {
      return 0;
    }
    int dubina_lijevo = depth(current->l_link);
    int dubina_desno = depth(current->r_link);
    return 1 + std::max(dubina_lijevo, dubina_desno);
  }

  void insert_subtree(Node* root) {
    if (root == nullptr) {
      return;
    }
    insert(root->value);
    insert_subtree(root->l_link);
    insert_subtree(root->r_link);
  }

  void clear_subtree(Node* root) {
    if (root == nullptr) return;
    clear_subtree(root->l_link);
    clear_subtree(root->r_link);
    delete root;
  }

  public:
  Tree() = default;
  Tree(const Tree& other) {
    insert_subtree(other.root_);
    size_ = other.size_;
  }
  Tree(Tree&& other) : root_{other.root_}, size_{other.size_} {
    other.root_ = nullptr;
    other.size_ = 0;
  }
  Tree& operator=(const Tree& other) {
    clear();
    insert_subtree(other.root_);
    return *this;
  }
  Tree& operator=(Tree&& other) {
    clear();
    root_ = other.root_;
    size_ = other.size_;

    other.root_ = nullptr;
    other.size_ = 0;
    return *this;
  }
  ~Tree() { clear(); }

  void clear() {
    clear_subtree(root_);
    size_ = 0;
    root_ = nullptr;
  }

  void print() const {
    print_subtree(root_);
    std::cout << std::endl;
  }

  bool empty() const { return root_ == nullptr; }

  int depth() const { return depth(root_); }

  bool size() const { return size_; }

  const Node* find(const int& v) const {
    Node* current = root_;
    if (empty()) return nullptr;

    while (current != nullptr) {
      if (current->value == v) {
        return current;
      } else if (v < current->value) {
        current = current->l_link;
      } else if (v > current->value) {
        current = current->r_link;
      }
    }
    return nullptr;
  }

  void insert(int v) {
    if (empty()) {
      root_ = new Node(v);
    } else {
      Node* prev;
      Node* current = root_;

      while (current != nullptr) {
        if (v < current->value) {
          prev = current;
          current = current->l_link;
        } else if (v > current->value) {
          prev = current;
          current = current->r_link;
        } else {
          // kad su jednaki
        }
      }
      auto novi_cvor = new Node(v);
      if (v < prev->value) {
        prev->l_link = novi_cvor;
        size_++;
      } else if (v > prev->value) {
        prev->r_link = novi_cvor;
        size_++;
      } else {
        // kad su jednaki
      }
    }
  }
};
