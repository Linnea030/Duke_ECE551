#include <iostream>
#include <string>
#include <vector>
#ifndef _choice_H
#define _choice_H
class Choice {
 public:
  size_t pagenum;
  size_t destnum;
  std::string text;
  long cnum;
  bool needVar;
  bool available;
  std::pair<long int, std::string> choiceVar;
  Choice(size_t pn, size_t dn, std::string text, long cnum) :
      pagenum(pn), destnum(dn), text(text), cnum(cnum), needVar(false), available(true) {}

  void print_c();
  void print_var();
};
#endif
