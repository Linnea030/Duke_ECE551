
#include <cstdlib>
#include <ostream>
#include <string>
#ifndef _LINE_H
#define _LINE_H
class Line {
 public:
  virtual bool isValid(std::string s1) const = 0;
  virtual void printText(std::string s1) const = 0;
};
#endif
