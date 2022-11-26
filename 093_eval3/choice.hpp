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

  Choice(long pn, long dn, std::string text, long cnum) :
      pagenum(pn), destnum(dn), text(text), cnum(cnum) {}

  void print_c();
};
#endif
