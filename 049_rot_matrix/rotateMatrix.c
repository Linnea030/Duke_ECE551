#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rotate_m(FILE * f) {
  int n = 10;
  char matrix[10][10];
  char line[12];
  int m = 0;
  while (fgets(line, 12, f) != NULL) {
    if (strchr(line, '\n') == NULL) {
      fprintf(stderr, "This is not a string\n");
      exit(EXIT_FAILURE);
    }
    m++;
    if (m > 10) {
      fprintf(stderr, "Output file has more than 10 lines\n");
      exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
      matrix[i][n - m] = line[i];
    }
  }
  if (m < 10) {
    fprintf(stderr, "The matrix's row is less than 10\n");
    exit(EXIT_FAILURE);
  }
  for (int j = 0; j < n; j++) {
    for (int k = 0; k < n; k++) {
      fprintf(stdout, "%c", matrix[j][k]);
    }
    fprintf(stdout, "\n");
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Wrong number of arguments\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("No such file\n");
    return EXIT_FAILURE;
  }
  rotate_m(f);
  if (fclose(f) != 0) {
    perror("Can not close the file");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
