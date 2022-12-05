#include <iostream>
#include <string>
#include <vector>
#ifndef _choice_H
#define _choice_H
class Choice {
 public:
  long pagenum;
  long destnum;
  std::string text;
  long cnum;
  bool needVar;
  bool available;
  std::pair<long int, std::string> choiceVar;
  Choice(long pn, long dn, std::string text, long cnum) :
      pagenum(pn), destnum(dn), text(text), cnum(cnum), needVar(false), available(true) {}

  void print_c();
  void print_var();
};
#endif
