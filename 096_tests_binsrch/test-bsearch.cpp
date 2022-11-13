#include <cmath>
#include <cstdio>
#include <cstdlib>
//using namespace std;
#include "function.h"

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n), f(fn), mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};
int binarySearchForZero(Function<int, int> * f, int low, int high);

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int res;
  if (high > low) {
    res = log(high - low) / log(2) + 1;
  }
  else {
    res = 1;
  }
  CountedIntFn f1(res, f, mesg);
  int num = binarySearchForZero(&f1, low, high);
  if (num != expected_ans) {
    fprintf(stderr, "Error! %s \n", mesg);
    exit(EXIT_FAILURE);
  }
}

class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class Negative : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return -100; }
};

class Postive : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 100; }
};

class Fun1 : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return -arg * 6 + 6; }
};

class Fun2 : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 6 * arg + 6; }
};

class Fun3 : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return log(arg); }
};

int main() {
  SinFunction f1;
  Negative f2;
  Postive f3;
  Fun1 f4;
  Fun2 f5;
  Fun3 f6;
  check(&f1, 0, 150000, 52359, "Sin");
  check(&f2, 0, 0, 0, "negative");
  check(&f2, 0, 90, 89, "negative");
  check(&f2, -6, 66, 65, "negative");
  check(&f3, 0, 90, 0, "postive");
  check(&f3, -16, 90, -16, "postive");
  check(&f4, 76, 90, 89, "f4");
  check(&f4, 0, 0, 0, "f4");
  check(&f5, -10, 10, -1, "f4");
}
