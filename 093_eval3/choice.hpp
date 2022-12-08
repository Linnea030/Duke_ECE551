#include <iostream>
#include <string>
#include <vector>
#ifndef _choice_H
#define _choice_H
class Choice {
 public:
  size_t pagenum;    //page number for this choice
  size_t destnum;    //destnation number for this choice
  std::string text;  //text of this choice
  long cnum;         //the choice number for this page
  //value needed in step4
  bool needVar;    //if this choice is related to variable, needVar is true
  bool available;  //if this choice is avaiable in, avaiable is true
  std::pair<long int, std::string> choiceVar;  //the variable key and value
  //constructor
  Choice(size_t pn, size_t dn, std::string text, long cnum) :
      pagenum(pn), destnum(dn), text(text), cnum(cnum), needVar(false), available(true) {}
  //copy constructor
  Choice(const Choice & rhs) :
      pagenum(rhs.pagenum),
      destnum(rhs.destnum),
      text(rhs.text),
      cnum(rhs.cnum),
      needVar(rhs.needVar),
      available(rhs.available),
      choiceVar(rhs.choiceVar) {}
  //implement in cpp
  //copy assignment operator
  Choice & operator=(const Choice & rhs);
  //input: nothing, return void
  //print choice text in step 1 2 3
  void print_c();
  //input: nothing, return voide
  //print choice text in step 4
  void print_var();
  //destructor
  ~Choice() {}
};
#endif
