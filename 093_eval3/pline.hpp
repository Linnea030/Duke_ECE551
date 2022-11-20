#ifndef _PLINE_H
#define _PLINE_H
#include "line.hpp"
//line for page.txt and pagenumber
class Pline : public Line {
 public:
  virtual bool isValid(std::string s1) const {}
  virtual void printText(std::string s1) const {}
};
#endif
