#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>
#include <iostream>

//YOUR CODE GOES HERE

class error : public std::exception {
 public:
  const char * Error() { return "ERROR!"; }
};

template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node(T d) : data(d), next(NULL), prev(NULL) {}
    ~Node() {}
  };
  Node * head;
  Node * tail;
  int sz;

 public:
  LinkedList() : head(NULL), tail(NULL), sz(0) {}
  //copy

  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), sz(0) {
    Node * temp = rhs.head;
    for (int i = 0; i < rhs.sz; i++) {
      addBack(temp->data);
      temp = temp->next;
    }
  }

  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      delete this;
      LinkedList lhs(rhs);
      this->head = lhs.head;
      this->tail = lhs.tail;
      this->sz = lhs.sz;
    }
    return *this;
  }
  //deconstructor
  void addFront(const T & item) {
    Node * n1 = new Node(item);
    sz++;
    if (head == NULL) {
      head = n1;
      tail = n1;
      return;
    }
    head->prev = n1;
    n1->next = head;
  }
  void addBack(const T & item) {
    Node * n1 = new Node(item);
    sz++;
    if (head == NULL) {
      head = n1;
      tail = n1;
      return;
    }
    tail->next = n1;
    n1->prev = tail;
  }
  bool remove(const T & item) {
    Node * temp = head;
    if (head == NULL) {
      return false;
    }
    if (head->data == item) {
      if (sz == 1) {
        sz--;
        head = NULL;
        tail = NULL;
        delete temp;
        return true;
      }
      sz--;
      head = head->next;
      head->prev = NULL;
      delete temp;
      return true;
    }
    while (temp != NULL) {
      if (item == temp->data) {
        sz--;
        if (temp->next != NULL) {
          temp->prev->next = temp->next;
          temp->next->prev = temp->prev;
        }
        else {
          temp->prev->next = temp->next;
          tail = temp->prev;
        }
        delete temp;
        return true;
      }
      temp = temp->next;
    }
    return false;
  }

  T & operator[](int index) {
    try {
      if (index > sz - 1 || index < 0) {
        throw error();
      }
    }
    catch (error & a) {
      std::cerr << a.Error() << std::endl;
    }
    if (head == NULL)
      throw error();
    int i = 0;
    Node * temp = head;
    while (i != index && temp->next != NULL) {
      temp = temp->next;
    }
    if (i == index) {
      return temp->data;
    }
    else
      throw error();
  }

  T & operator[](int index) const {
    try {
      if (index > sz - 1 || index < 0) {
        throw error();
      }
    }
    catch (error & a) {
      std::cerr << a.Error() << std::endl;
    }
    if (head == NULL)
      throw error();
    int i = 0;
    Node * temp = head;
    while (i != index && temp->next != NULL) {
      temp = temp->next;
    }
    if (i == index) {
      return temp->data;
    }
    else
      throw error();
  }

  int find(const T & item) const {
    for (int i = 0; i < sz; i++) {
      if ((*this)[i] == item) {
        return i;
      }
    }
    return -1;
  }

  int getSize() const { return sz; }
  friend void testList(void);

  ~LinkedList() {
    Node * temp = head;
    while (temp != NULL) {
      Node * t = temp;
      temp = temp->next;
      delete t;
    }
    sz = 0;
  }
};

#endif
