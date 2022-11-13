#include <cstdlib>
#include <stdexcept>

#include "assert.h"
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
    Node(K key, V value) : key(key), value(value), left(NULL), right(NULL) {}

    //Node() : right(NULL), left(NULL) {}
    ~Node() {}
  };
  Node * root;

 public:
  BstMap() : root(NULL) {}

  virtual void add(const K & key, const V & value) {
    Node * temp = root;
    if (root == NULL) {
      root = new Node(key, value);
      //root = t;
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
      }
      else if (key < temp->key) {
        temp = temp->left;
      }
    }
    if (temp == NULL)
      throw std::invalid_argument("No such key!\n");
    return temp->value;
  }

  /*  Node remove(Node * node, K key) {
    if (node == NULL)
      return NULL;

    if (key < node->key) {
      node->left = remove(node->left, key);
      return node;
    }
    else if (key > node->key) {
      node->right = remove(node->right, key);
      return node;
    }
    else {
      if (node->left == NULL) {  //左孩子为空
        Node rightNode = node->right;
        node->right = NULL;
        //size--;
        return rightNode;
      }
      else if (node->right == NULL) {  //右孩子为空
        Node leftNode = node->left;
        node->left = NULL;
        //        size--;
        return leftNode;
      }
      else {  //左右孩子均不为空
        Node min = minimum(node->right);

        min.left = node->left;
        min.right = removeMin(node->left);
        node->left = NULL;
        node->right = NULL;

        return min;
      }
    }
  }
  Node minimum(Node * node) {
    if (node->left == NULL) {
      return node;
    }
    return minimum(node->left);
  }

  //删除最小元素,并返回新树的根结点
  Node removeMin(Node * node) {
    if (node->left == NULL) {
      Node newRight = node->right;
      node->right = NULL;
      size--;
      return newRight;
    }
    node->left = removeMin(node->left);
    return node;
    }*/
  virtual Node * remhelp(Node * root, const K & key) {
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

        K key1 = t->key;
        V value1 = t->value;
        //remove(temp->key);
        temp->key = key1;
        temp->value = value1;
        temp->left = remhelp(temp->left, temp->key);
        return temp;
      }
    }
    return temp;
  }

  virtual void remove(const K & key) { root = remhelp(root, key); }
  void des(Node * temp) {
    if (temp == NULL)
      return;
    des(temp->left);
    des(temp->right);
    delete temp;
  }

  virtual ~BstMap<K, V>() { des(root); }
};
