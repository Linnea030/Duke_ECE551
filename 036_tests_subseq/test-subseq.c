#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void doTest(int * array, size_t n, size_t expect) {
  printf("array(");
  if (array == NULL) {
    printf("NULL");
  }
  else {
    printf("{");
    for (int i = 0; i < n; i++) {
      printf("%d", array[i]);
      if (i < n - 1) {
        printf(", ");
      }
    }
    printf("}");
  }
  printf(")\n");

  size_t m = maxSeq(array, n);

  if (m != expect) {
    printf("Failed\n");
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  int array1[] = {3, 1, 2, 6, 7, 9, 29, 35, 16, 29};
  int array2[] = {-3, -42, -2, -9, 0, 1, -6};
  int array3[] = {59, 60, -3, 77, 0, 36};
  int array4[] = {6, 16, -3, -6, 26};
  int array5[] = {5, 6, 5, 5, 5, 7, 9};
  size_t a = 10;
  size_t b = 7;
  doTest(array1, a, b);
  a = 7;
  b = 3;
  doTest(array5, a, b);
  a = 7;
  b = 3;
  doTest(array2, a, b);
  a = 0;
  b = 0;
  doTest(NULL, a, b);
  a = 3;
  b = 2;
  doTest(array2, a, b);
  a = 2;
  b = 2;
  doTest(array3, a, b);
  a = 6;
  b = 3;
  doTest(array2, a, b);
  a = 6;
  b = 5;
  doTest(array1, a, b);
  a = 6;
  b = 2;
  doTest(array3, a, b);
  a = 4;
  b = 2;
  doTest(array2, a, b);
  a = 0;
  b = 0;
  doTest(array2, a, b);
  a = 2;
  b = 1;
  doTest(&array4[1], a, b);
  a = 0;
  b = 0;
  doTest(NULL, a, b);
  a = 3;
  b = 2;
  doTest(array5, a, b);
  a = 1;
  b = 1;
  doTest(array5, a, b);
  printf("succeed\n");
  return EXIT_SUCCESS;
}
