#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void sortfile(FILE * f) {
  size_t i = 0;
  size_t sz = 0;
  char ** lines = NULL;
  char * curr = NULL;
  while (getline(&curr, &sz, f) >= 0) {
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    lines[i] = curr;
    curr = NULL;
    i++;
  }
  free(curr);
  sortData(lines, i);
  for (size_t j = 0; j < i; j++) {
    printf("%s", lines[j]);
    free(lines[j]);
  }
  free(lines);
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    FILE * f = stdin;
    sortfile(f);
  }
  if (argc > 1) {
    for (size_t k = 1; k < argc; k++) {
      FILE * f = fopen(argv[k], "r");
      if (f == NULL) {
        perror("No such file\n");
        exit(EXIT_FAILURE);
      }
      sortfile(f);
      if (fclose(f) != 0) {
        perror("The input file can not be closed\n");
        exit(EXIT_FAILURE);
      }
    }
  }
  return EXIT_SUCCESS;
}
