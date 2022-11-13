#include <cstdlib>
#include <stdexcept>

#include "map.h"

template<typename K, typename V>

class BstMap : public Map<K, V> {
 private:
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node(K key, V value) {
      this->key = key;
      this->value = value;
      this->left = NULL;
      this->right = NULL;
    }
    Node() : right(NULL), left(NULL) {}
    ~Node() {}
  };
  Node * root;
  int size;

 public:
  BstMap() : root(NULL) {}
  virtual void add(const K & key, const V & value) {
    Node * temp = root;
    if (temp == NULL) {
      Node * t = new Node(key, value);
      root = t;
      return;
    }
    while (temp != NULL) {
      if (key > temp->key) {
        if (temp->right == NULL) {
          temp->right = new Node(key, value);
          break;
        }
        else {
          temp = temp->right;
        }
      }
      if (key == temp->key) {
        temp->value = value;
        break;
      }
      if (key < temp->key) {
        if (temp->left == NULL) {
          temp->left = new Node(key, value);
          break;
        }
        else {
          temp = temp->left;
        }
      }
    }
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * temp = root;
    while (temp != NULL) {
      if (key == temp->key) {
        return temp->value;
      }
      else if (key > temp->key) {
        temp = temp->right;
        break;
      }
      else if (key < temp->key) {
        temp = temp->left;
        break;
      }
    }
    if (temp == NULL)
      throw std::invalid_argument("No such key!\n");
    return temp->value;
  }

  virtual void remove(const K & key) {
    Node * temp = root;
    while (temp != NULL) {
      if (key == temp->key) {
        break;
      }
      else if (key > temp->key) {
        temp = temp->right;
        break;
      }
      else if (key < temp->key) {
        temp = temp->left;
        break;
      }
    }
    if (temp == NULL)
      throw std::invalid_argument("No such key!\n");
    else if (temp->right == NULL) {
      Node * t = temp->left;
      delete temp;
      temp = t;
    }
    else if (temp->left == NULL) {
      Node * t = temp->right;
      delete temp;
      temp = t;
    }
    else {
      Node * t = temp;
      temp = temp->right;
      while (temp->left != NULL) {
        temp = temp->left;
      }
      K key1 = temp->key;
      V value1 = temp->value;
      t->key = key1;
      t->value = value1;
      remove(temp->key);
    }
    return;
  };
  //virtual ~Map<K, V>() {}
};
