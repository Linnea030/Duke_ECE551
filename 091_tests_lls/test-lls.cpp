#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    IntList il;
    assert(il.getSize() == 0);
    const int a = 1;
    il.addFront(a);  // 1
    assert(il.head != NULL && il.tail != NULL);
    assert(il.head->data == 1);
    assert(il.tail->data == 1);
    assert(il.head->next == NULL);
    assert(il.tail->prev == NULL);
    assert(il.head == il.tail);
    assert(il.getSize() == 1);
    assert(il.head->prev == NULL);
    assert(il.tail->next == NULL);

    il.addFront(2);  //2 1
    assert(il.head != NULL && il.tail != NULL);
    assert(il.head->data == 2);
    assert(il.tail->data == 1);
    assert(il.head->next == il.tail);
    assert(il.tail->prev == il.head);
    assert(il.getSize() == 2);
    assert(il.head->prev == NULL);
    assert(il.tail->next == NULL);

    il.addBack(3);  //2 1 3
    assert(il.head != NULL && il.tail != NULL);
    assert(il.head->data == 2 && il.tail->data == 3 && il.head->next->data == 1);
    assert(il.head->next == il.tail->prev);
    assert(il.getSize() == 3);
    assert(il.head->prev == NULL);
    assert(il.tail->next == NULL);

    // WRITE ME
  }
  void testaddBack() {
    IntList il;
    assert(il.getSize() == 0);
    const int a = 11;
    const int b = 12;
    il.addBack(a);  //11
    assert(il.head->data == 11);
    assert(il.tail->data == 11);
    assert(il.head == il.tail);
    assert(il.getSize() == 1);
    assert(il.head->prev == NULL);
    assert(il.head->next == NULL);
    assert(il.tail->prev == NULL);
    assert(il.tail->next == NULL);

    il.addBack(b);  //11 12
    assert(il.head->data == 11);
    assert(il.tail->data == 12);
    assert(il.getSize() == 2);
    assert(il.head->prev == NULL);
    assert(il.head->next == il.tail);
    assert(il.tail->prev == il.head);
    assert(il.tail->next == NULL);
  }

  void testRo3() {
    IntList il1;
    il1.addBack(1);  //1
    IntList il2(il1);
    assert(il2.head != NULL && il2.tail != NULL);
    assert(il2.head->data == 1);
    assert(il2.tail->data == 1);
    assert(il2.head->next == NULL);
    assert(il2.tail->prev == NULL);
    assert(il2.head == il2.tail);
    assert(il2.getSize() == 1);
    assert(il2.head->prev == NULL);
    assert(il2.tail->next == NULL);

    il1.addFront(2);  //2 1
    IntList il3;
    il3.addFront(1);
    il3 = il1;
    assert(il3.head != NULL && il3.tail != NULL);
    assert(il3.head->data == 2);
    assert(il3.tail->data == 1);
    assert(il3.head->next == il3.tail);
    assert(il3.tail->prev == il3.head);
    assert(il3.getSize() == 2);
    assert(il3.head->prev == NULL);
    assert(il3.tail->next == NULL);

    il2.addBack(2);  //1 2
    IntList il4(il2);
    assert(il4.head != NULL && il4.tail != NULL);
    assert(il4.head->data == 1);
    assert(il4.tail->data == 2);
    assert(il4.head->next == il4.tail);
    assert(il4.tail->prev == il4.head);
    assert(il4.getSize() == 2);
    assert(il4.head->prev == NULL);
    assert(il4.tail->next == NULL);
  }

  void testRemove() {
    IntList il;
    il.addFront(1);  //1
    assert(il.remove(1) == true);
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
    assert(il.remove(1) == false);

    IntList il1;  //1 2 3
    assert(il1.remove(0) == false);
    il1.addBack(1);
    il1.addBack(2);
    il1.addBack(3);

    assert(il1.head != NULL && il1.tail != NULL);
    assert(il1.head->data == 1 && il1.tail->data == 3 && il1.head->next->data == 2);
    assert(il1.head->next == il1.tail->prev);
    assert(il1.getSize() == 3);
    assert(il1.head->prev == NULL);
    assert(il1.tail->next == NULL);

    assert(il1.remove(0) == false);
    assert(il1.head != NULL && il1.tail != NULL);
    assert(il1.head->data == 1 && il1.tail->data == 3 && il1.head->next->data == 2);
    assert(il1.head->next == il1.tail->prev);
    assert(il1.getSize() == 3);
    assert(il1.head->prev == NULL);
    assert(il1.tail->next == NULL);

    bool r = il1.remove(3);  //1 2
    assert(r == true);
    assert(il1.head != NULL && il1.tail != NULL);
    assert(il1.head->data == 1);
    assert(il1.tail->data == 2);
    assert(il1.head->next == il1.tail);
    assert(il1.tail->prev == il1.head);
    assert(il1.getSize() == 2);
    assert(il1.head->prev == NULL);
    assert(il1.tail->next == NULL);

    il1.addBack(1);           //1 2 1
    bool r1 = il1.remove(1);  //2 1
    assert(r1 == true);
    assert(il1.head != NULL && il1.tail != NULL);
    assert(il1.head->data == 2);
    assert(il1.tail->data == 1);
    assert(il1.head->next == il1.tail);
    assert(il1.tail->prev == il1.head);
    assert(il1.getSize() == 2);
    assert(il1.head->prev == NULL);
    assert(il1.tail->next == NULL);

    il1.addBack(3);                 //2 1 3
    assert(il1.remove(1) == true);  //2 3
    assert(il1.head != NULL && il1.tail != NULL);
    assert(il1.head->data == 2);
    assert(il1.tail->data == 3);
    assert(il1.head->next == il1.tail);
    assert(il1.tail->prev == il1.head);
    assert(il1.getSize() == 2);
    assert(il1.head->prev == NULL);
    assert(il1.tail->next == NULL);

    il1.addBack(6);                 //2 3 6
    il1.addFront(1);                //1 2 3 6
    il1.addBack(3);                 // 1 2 3 6 3
    assert(il1.remove(3) == true);  //1 2 6 3
    assert(il1.head != NULL && il1.tail != NULL);
    assert(il1.head->data == 1);
    assert(il1.tail->data == 3);
    assert(il1[1] == 2 && il1[2] == 6);
    //  assert(il1.head->next->data == 2 && il1.head->next->next->data == 6 &&  il1.head->next->next->next == il.tail);
    assert(il1.tail->prev == il1.head->next->next);
    assert(il1.head->next == il1.tail->prev->prev);
    assert(il1.getSize() == 4);
    assert(il1.head->prev == NULL);
    assert(il1.tail->next == NULL);
  }
  // many more tester methods
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testaddBack();
  t.testRo3();
  t.testRemove();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
