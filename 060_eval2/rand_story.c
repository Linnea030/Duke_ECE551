#include "rand_story.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void freeArr(size_t i, char ** larray) {
  for (size_t j = 0; j < i; j++) {
    free(larray[j]);
  }
  free(larray);
}
void getStory_cat(FILE * f) {
  char * line = NULL;
  char ** larray = NULL;
  size_t sz = 0;
  size_t i = 0;
  while (getline(&line, &sz, f) >= 0) {
    larray = realloc(larray, (i + 1) * sizeof(larray));
    larray[i] = line;
    line = NULL;
    i++;
  }
  free(line);

  for (size_t j = 0; j < i; j++) {
    char * res = NULL;
    size_t len = strlen(larray[j]);
    size_t len_res = 0;
    const char * cword;

    for (size_t k = 0; k < len; k++) {
      if (larray[j][k] != '_') {
        res = realloc(res, (len_res + 1) * sizeof(*res));
        res[len_res] = larray[j][k];
        len_res++;
      }
      else {
        cword = chooseWord(NULL, NULL);
        size_t len_c = strlen(cword);
        k++;
        for (size_t m = 0; m < len_c; m++) {
          res = realloc(res, (len_res + 1) * sizeof(*res));
          res[len_res] = cword[m];
          len_res++;
        }
        while (larray[j][k] != '_') {
          k++;
          if (k >= len) {
            free(res);
            freeArr(i, larray);
            fprintf(stderr, "No matching underscore");
            exit(EXIT_FAILURE);
          }
        }
      }
    }
    res = realloc(res, (len_res + 1) * sizeof(res));
    res[len_res] = '\0';
    printf("%s", res);
    free(res);
  }
  freeArr(i, larray);
}
