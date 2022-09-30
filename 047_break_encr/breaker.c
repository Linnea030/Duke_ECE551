#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void breaker(FILE * f) {
  int c;
  int freq[26] = {0};
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      c -= 'a';
      freq[c]++;
    }
  }
  int maxf = 0, maxi = 0;
  for (int i = 0; i < 26; i++) {
    if (maxf < freq[i]) {
      maxi = i;
      maxf = freq[i];
    }
  }
  if (maxi >= 4) {
    fprintf(stdout, "%d\n", maxi - 4);
  }
  else if (maxf == 0) {
    fprintf(stderr, "nothing in the file\n");
    exit(EXIT_FAILURE);
  }
  else {
    fprintf(stdout, "%d\n", maxi + 22);
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: encrypt inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  breaker(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
