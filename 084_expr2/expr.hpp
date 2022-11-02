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
  virtual ~PlusExpression() {
    delete l;
    delete r;
  }
};

class MinusExpression : public Expression {
  Expression * l;
  Expression * r;

 public:
  MinusExpression(Expression * lhs, Expression * rhs) {
    l = lhs;
    r = rhs;
  }
  virtual std::string toString() const {  //actually implement it
    std::stringstream s1;
    s1 << "(" << l->toString() << " - " << r->toString() << ")";
    return s1.str();
  }  //actually implement it
  virtual ~MinusExpression() {
    delete l;
    delete r;
  }
};

class TimesExpression : public Expression {
 private:
  Expression * l;
  Expression * r;

 public:
  TimesExpression(Expression * lhs, Expression * rhs) {
    l = lhs;
    r = rhs;
  }
  virtual std::string toString() const {  //actually implement it
    std::stringstream s1;
    s1 << "(" << l->toString() << " * " << r->toString() << ")";
    return s1.str();
  }  //actually implement it
  virtual ~TimesExpression() {
    delete l;
    delete r;
  }
};

class DivExpression : public Expression {
 private:
  Expression * l;
  Expression * r;

 public:
  DivExpression(Expression * lhs, Expression * rhs) {
    l = lhs;
    r = rhs;
  }
  virtual std::string toString() const {  //actually implement it
    std::stringstream s1;
    s1 << "(" << l->toString() << " / " << r->toString() << ")";
    return s1.str();
  }  //actually implement it
  virtual ~DivExpression() {
    delete l;
    delete r;
  }
};
