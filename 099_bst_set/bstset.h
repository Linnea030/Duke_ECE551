#include <cstdlib>
#include <stdexcept>

#include "assert.h"
#include "set.h"

template<typename T>

class BstSet : public Set<T> {
 private:
  class Node {
   public:
    T key;
    // V value;
    Node * left;
    Node * right;
    Node(T key) : key(key), left(NULL), right(NULL) {}

    //Node() : right(NULL), left(NULL) {}
    ~Node() {}
  };
  Node * root;

 public:
  BstMap() : root(NULL) {}

  virtual void add(const T & key) {
    Node * temp = root;
    if (root == NULL) {
      root = new Node(key);
      //root = t;
      return;
    }
    while (temp != NULL) {
      if (key > temp->key) {
        if (temp->right == NULL) {
          temp->right = new Node(key);
          break;
        }
        else {
          temp = temp->right;
        }
      }
      if (key == temp->key) {
        // temp->value = value;
        break;
      }
      if (key < temp->key) {
        if (temp->left == NULL) {
          temp->left = new Node(key);
          break;
        }
        else {
          temp = temp->left;
        }
      }
    }
    return;
  }

  virtual bool contains(const T & key) const {
    Node * temp = root;
    while (temp != NULL) {
      if (key == temp->key) {
        return true;
      }
      else if (key > temp->key) {
        temp = temp->right;
      }
      else if (key < temp->key) {
        temp = temp->left;
      }
    }
    if (temp == NULL)
      return false;  //throw std::invalid_argument("No such key!\n");
    return false;
  }

  //  virtual const K & lookup(const K & key) const throw(std::invalid_argument) {}

  virtual Node * remhelp(Node * root, const T & key) {
    Node * temp = root;
    if (temp == NULL) {
      return NULL;
    }
    if (temp->key > key) {
      temp->left = remhelp(temp->left, key);
      return temp;
    }
    else if (temp->key < key) {
      temp->right = remhelp(temp->right, key);
      return temp;
    }
    else if (temp->key == key) {
      if (temp->left == NULL) {
        Node * t = temp->right;
        delete temp;
        return t;
      }
      else if (temp->right == NULL) {
        Node * t = temp->left;
        delete temp;
        return t;
      }
      else {
        Node * t = temp->left;
        while (t->right != NULL) {
          t = t->right;
        }
        T key1 = t->key;
        //V value1 = t->value;
        //remove(temp->key);
        temp->key = key1;
        //temp->value = value1;
        temp->left = remhelp(temp->left, temp->key);
        return temp;
      }
    }
    return temp;
  }

  virtual void remove(const T & key) { root = remhelp(root, key); }

  void des(Node * temp) {
    if (temp == NULL)
      return;
    des(temp->left);
    des(temp->right);
    delete temp;
  }

  void copy(Node * temp) {
    if (temp == NULL)
      return;
    add(temp->key, temp->value);
    copy(temp->left);
    copy(temp->right);
  }

  BstMap & operator=(const BstSet<T> & rhs) {
    if (this != &rhs) {
      BstMap t1(rhs);
      std::swap(t1.root, root);
    }
    return *this;
  }

  BstMap(const BstSet<T> & rhs) : root(NULL) { copy(rhs.root); }

  virtual ~BstSet<T>() { des(root); }
};
