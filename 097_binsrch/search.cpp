#include <cstdlib>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (high <= low + 1) {
    return low;
  }
  int m = (high - low) / 2 + low;
  int ans = f->invoke(m);
  if (ans > 0) {
    return binarySearchForZero(f, low, m);
  }
  else if (ans < 0) {
    return binarySearchForZero(f, m, high);
  }
  else if (ans == 0)
    return m;
  return low;
}
