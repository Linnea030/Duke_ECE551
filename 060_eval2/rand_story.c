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
    larray = realloc(larray, (i + 1) * sizeof(*larray));
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
    res = realloc(res, (len_res + 1) * sizeof(*res));
    res[len_res] = '\0';
    printf("%s", res);
    free(res);
  }
  freeArr(i, larray);
}

int contains(char * temp, category_t * arr, size_t num_cat) {
  int x = -1;                             //declare index of arr
  for (size_t i = 0; i < num_cat; i++) {  //traverse to compare each name with temp
    int y = strcmp(arr[i].name, temp);
    if (y != 0)
      x = -1;  //if not equal, index is -1
    else
      x = i;  //if equal, index is current index i
  }
  return x;
}

catarray_t * getWord_cat(FILE * f) {
  char * line = NULL;
  char ** larray = NULL;
  size_t sz = 0;
  size_t i = 0;
  while (getline(&line, &sz, f) >= 0) {
    larray = realloc(larray, (i + 1) * sizeof(*larray));
    larray[i] = line;
    line = NULL;
    i++;
  }
  free(line);

  //declare cat as return result
  catarray_t * cat = malloc(sizeof(*cat));
  cat->arr = malloc(sizeof(*cat->arr));
  cat->n = 0;
  //traverse each line to get cat
  for (size_t j = 0; j < i; j++) {
    //if there is no : in the line
    if (strchr(larray[j], ':') == NULL) {
      fprintf(stderr, "No : in the line %ld \n", j);
      return NULL;
    }

    //get new name
    size_t len_line = strlen(larray[j]);  // get length of this line
    size_t index_line = 0;                //declare index in line
    int x = -1;                           //declare x to save the index of exist arr
    for (size_t k = 0; k < len_line; k++) {
      if (larray[j][k] == ':') {
        size_t len_name = k;
        char * temp = strndup(larray[j], len_name + 1);  //malloc address for temp
        temp[len_name] = '\0';                           //make temp as a string

        //compare temp with exist name
        x = contains(temp, cat->arr, cat->n);
        //temp is not in arr
        if (x == -1) {
          //alloc memory for cat->arr
          cat->arr = realloc(cat->arr, (cat->n + 1) * sizeof(*(cat->arr)));
          cat->arr[cat->n].n_words = 0;
          //printf("%s\n", temp);
          cat->arr[cat->n].name = temp;
          x = cat->n;  //index of categories
          cat->n++;
          cat->arr[x].words = malloc(sizeof(*(cat->arr[x].words)));
        }
        else {
          free(temp);
        }
        index_line = k + 1;
        break;
      }
    }
    //get word
    for (size_t m = index_line; m < len_line; m++) {
      if (larray[j][m] == '\0' || larray[j][m] == '\n') {
        //get word after : save as temp
        char * temp1 = strndup(larray[j] + index_line, m - index_line + 1);
        temp1[m - index_line] = '\0';
        //if no temp in word, realloc words in arr
        //printf("%d",x);
        //printf("%ld\n", cat->arr[x].n_words);

        cat->arr[x].words = realloc(
            cat->arr[x].words, (cat->arr[x].n_words + 1) * sizeof(*(cat->arr[x].words)));
        cat->arr[x].words[cat->arr[x].n_words] = temp1;
        cat->arr[x].n_words++;
        break;
      }
    }
  }
  freeArr(i, larray);
  return cat;
}

void freecat(catarray_t * cat, size_t n) {
  for (size_t i = 0; i < n; i++) {
    free(cat->arr[i].name);
    for (size_t j = 0; j < cat->arr[i].n_words; j++) {
      free(cat->arr[i].words[j]);
    }
    free(cat->arr[i].words);
  }
  free(cat->arr);
  free(cat);
}

/* catarray_t * categories = malloc(sizeof(*categories));  //words for categories
  size_t num_cat = 0;                                     //number of cataegories
  //  size_t num_word = 0;  //number of words for one caraegories
  for (size_t j = 0; j < i; j++) {
    char temp[100000000000000];
    size_t len_line = strlen(larray[j]);  //get length of larray, that is size of lin
    if (strchr(larray[j], ':') == NULL) {
      fprintf(stderr, "No : in the line %ld \n", j);
      return NULL;
    }
    // categories->arr = realloc(categories->arr, (num_cat + 1) * sizeof(*categories->arr));
    // categories->arr[num_cat].n_words = 0;
    size_t index = 0;
    int x = 0;  //index for name
    for (size_t k = 0; k < len_line; k++) {
      if (larray[j][k] == ':') {
        temp[k] = '\0';
        x = contains(temp, categories->arr, num_cat);
        if (x == 0) {  //no cate in this arr, create categories
                       //categories->arr[num_cat].name[k] = '\0';
          categories->arr =
              realloc(categories->arr, (num_cat + 1) * sizeof(*categories->arr));
          categories->arr[num_cat].n_words = 0;
          categories->arr[num_cat].name = strndup(temp, k + 1);
          x = num_cat;  //index of categories
          num_cat++;
          categories->n = num_cat;  //number of categories
        }
        index = k;
        //categories->arr[x].n_words++;
        break;
      }
      temp[k] = larray[j][k];
      //categories->arr[num_cat].name[k] = larray[j][k];
    }
    //temp=NULL;
    //get words after :
    for (size_t m = index + 1; m < len_line; m++) {
      if (larray[j][m] == '\0' || larray[j][m] == '\n') {
        temp[m - index - 1] = '\0';
        categories->arr[x].words[categories->arr[x].n_words] = strndup(temp, m - index);
        categories->arr[x].n_words++;
      }
      temp[m - index - 1] = larray[j][m];
      //categories->arr[num_cat].words[][m-index-1] = larray[j][m];
    }
  }
  freeArr(i, larray);
  return categories;
  }*/
