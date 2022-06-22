#pragma once

#include <iostream>
#include <queue>

template <typename T>
struct Node {
  Node(T v) : value{v} {}
  T value;
  Node* l_link = nullptr;
  Node* r_link = nullptr;
};

template <typename T>
class Tree {
  private:
  Node<T>* root_ = nullptr;
  size_t size_ = 0;

  void print_subtree(Node<T>* root) const {
    if (root == nullptr) {
      return;
    }
    std::cout << root->value << " ";
    print_subtree(root->l_link);
    print_subtree(root->r_link);
  }

  int depth(Node<T>* current) const {
    if (current == nullptr) {
      return 0;
    }
    int dubina_lijevo = depth(current->l_link);
    int dubina_desno = depth(current->r_link);
    return 1 + std::max(dubina_lijevo, dubina_desno);
  }

  void insert_subtree(Node<T>* root) {
    if (root == nullptr) {
      return;
    }
    insert(root->value);
    insert_subtree(root->l_link);
    insert_subtree(root->r_link);
  }

  void clear_subtree(Node<T>* root) {
    if (root == nullptr) return;
    clear_subtree(root->l_link);
    clear_subtree(root->r_link);
    delete root;
  }

  void eraseNode(Node<T>*& e) {
    if (e == nullptr) {
      return;
    } else if (e->l_link == nullptr && e->r_link == nullptr) {
      // cvor e ovdje nema djece
      auto temp = e;
      e = nullptr;
      delete temp;
    } else if (e->r_link == nullptr) {
      // cvor e ovdje ima jedno dijete -> lijevo
      auto temp = e;
      e = e->l_link;
      delete temp;
    } else if (e->l_link == nullptr) {
      // cvor e ovdje ima jedno dijete -> desno
      auto temp = e;
      e = e->r_link;
      delete temp;
    } else {
      // cvor sa 2 djece
      Node<T>* previous = nullptr;
      auto current = e->l_link;

      while (current->l_link != nullptr) {
        previous = current;
        current = current->r_link;
      }
      e->value = current->value;

      if (previous != nullptr) {
        previous->r_link = current->l_link;
      } else {
        e->l_link = current->l_link;
      }

      delete current;
    }
    size_--;
  }

  void preorder(Node<T>* current) {
    if (current == nullptr) {
      return;
    }
    std::cout << current->value << " ";
    preorder(current->l_link);
    preorder(current->r_link);
  }

  void inorder(Node<T>* current) {
    if (current == nullptr) {
      return;
    }
    inorder(current->l_link);
    std::cout << current->value << " ";
    inorder(current->r_link);
  }

  void postorder(Node<T>* current) {
    if (current == nullptr) {
      return;
    }
    postorder(current->l_link);
    postorder(current->r_link);
    std::cout << current->value << " ";
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

  const Node<T>* find(const T& v) const {
    Node<T>* current = root_;
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

  void insert(T v) {
    if (empty()) {
      root_ = new Node<T>(v);
    } else {
      Node<T>* prev;
      Node<T>* current = root_;

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
      auto novi_cvor = new Node<T>(v);
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

  void erase(const T& element) {
    Node<T>* previous = nullptr;
    Node<T>* current = root_;

    while (current != nullptr) {
      if (current->value == element) {
        break;
      } else if (element < current->value) {
        previous = current;
        current = current->l_link;
      } else if (element > current->value) {
        previous = current;
        current = current->r_link;
      }
    }
    if (!previous) {
      eraseNode(root_);
    } else if (previous->l_link == current) {
      eraseNode(previous->l_link);
    } else {
      eraseNode(previous->r_link);
    }
  }

  void breatdh_first() {
    std::queue<Node<T>*> order;
    order.push(root_);

    while (!order.empty()) {
      auto current = order.front();
      std::cout << current->value << std::endl;
      if (current->l_link) order.push(current->l_link);
      if (current->r_link) order.push(current->r_link);
      order.pop();
    }
  }

  void preorder() { preorder(root_); }

  void inorder() { inorder(root_); }

  void postorder() { postorder(root_); }
};
