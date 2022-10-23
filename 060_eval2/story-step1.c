#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  //If there are not two command line arguments
  if (argc != 2) {
    fprintf(stderr, "argc invalid\n");
    exit(EXIT_FAILURE);
  }
  //If there is no input file
  if (argv[1] == NULL) {
    fprintf(stderr, "No input file\n");
    exit(EXIT_FAILURE);
  }
  //using function to parsing the story

  FILE * f = fopen(argv[1], "r");
  //open file is fail
  if (f == NULL) {
    fprintf(stderr, "Input file is NULL\n");
    exit(EXIT_FAILURE);
  }
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
    // int num_under=0;
    for (size_t k = 0; k < len; k++) {
      if (larray[j][k] != '_') {
        //	num_under++;
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
            //for (size_t j = 0; j < i; j++) {
            //free(larray[j]);
            //}
            //free(larray);
            fprintf(stderr, "No matching underscore");
            exit(EXIT_FAILURE);
          }
        }
        //	num_under++;
      }
    }
    res = realloc(res, (len_res + 1) * sizeof(res));
    res[len_res] = '\0';
    printf("%s", res);
    free(res);
  }
  // for (size_t j = 0; j < i; j++) {
  //free(larray[j]);
  //}
  //free(larray);
  freeArr(i, larray);
  assert(fclose(f) == 0);
  return EXIT_SUCCESS;
}
