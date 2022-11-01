#include <string.h>

#include <cstdlib>
#include <iostream>
#include <sstream>

class Expression {
 public:
  Expression() {}
  virtual std::string toString() const = 0;  //abstract method
  virtual ~Expression() {}
};

class NumExpression : public Expression {
  long num;

 public:
  NumExpression(long n) : num(n) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << num;
    std::string text = ss.str();
    return text;
  }  //actually implement it
  virtual ~NumExpression() {}
};

class PlusExpression : public Expression {
 private:
  Expression * l;
  Expression * r;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) {
    l = lhs;
    r = rhs;
  }
  virtual std::string toString() const {
    std::stringstream s1;
    s1 << "(" << l->toString() << " + " << r->toString() << ")";
    return s1.str();
  }  //actually implement it
  virtual ~PlusExpression() {}
};
