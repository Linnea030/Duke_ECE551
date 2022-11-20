#ifndef _CLINE_H
#define _CLINE_H
#include "line.hpp"
//line for choose and pagenumber
class Cline : public Line {
 public:
  virtual bool isValid(std::string s1) const {}
  virtual void printText(std::string s1) const {}
};
#endif
