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

void getStory_line(FILE * f) {
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

catarray_t * getWord_cat(FILE * f) {
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

  catarray_t * categories = malloc(sizeof(*categories));  //words for categories
  size_t num_cat = 0;                                     //number of cataegories
  size_t num_word = 0;  //number of words for one caraegories
  for (size_t j = 0; j < i; j++) {
    char * temp = NULL;
    size_t len_line = strlen(larray[j]);  //get length of larray, that is size of lin
    if (strchr(larray[j], ':') == NULL) {
      fprintf(stderr, "No : in the line %ld \n", j);
      return NULL;
    }
    categories->arr = realloc(categories->arr, (num_cat + 1) * sizeof(*categories->arr));
    categories->arr[num_cat].n_words = 0;
    size_t index = 0;
    int x = 0;  //index for name
    for (size_t k = 0; k < len_line; k++) {
      if (larray[j][k] == ':') {
        temp[k] = '\0';
        x = contains(temp, categories->arr[num_cat].name);
        if (x == -1) {
          //categories->arr[num_cat].name[k] = '\0';
          index = k;
          categories->arr[num_cat].name = strndup(temp, k + 1);
        }
        else
          break;
      }
      temp[k] = larray[j][k];
      //categories->arr[num_cat].name[k] = larray[j][k];
    }
    temp = NULL;
    for (size_t m = index + 1; m < len_line; m++) {
      if (larray[j][m] == '\0' || larray[j][m] == '\n') {
        temp[m - index - 1] = '\0';
        categories->arr[num_cat].words[x] = strndup(temp, m - index);
      }
      temp[m - index - 1] = larray[j][m];
      //categories->arr[num_cat].words[][m-index-1] = larray[j][m];
    }
    num_cat++;
  }
}
