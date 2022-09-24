#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  size_t max = 0;
  size_t c = 0;
  if (array == NULL || n == 0) {
    return max;
  }
  c = 1;
  int a = 0;
  while (a < n - 1) {
    if (array[a] < array[a + 1]) {
      c++;
    }
    else {
      max = c > max ? c : max;
      c = 1;
    }
    a++;
  }
  max = c > max ? c : max;

  return max;
}
