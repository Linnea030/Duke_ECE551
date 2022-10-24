#include "rand_story.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//free larray[][]
void freeArr(size_t i, char ** larray) {
  for (size_t j = 0; j < i; j++) {
    free(larray[j]);
  }
  free(larray);
}

//get story by input category and catarray_t
void getStory_cat(FILE * f, catarray_t * cats) {
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
    char * res = NULL;  // result of story
    size_t len = strlen(larray[j]);
    size_t len_res = 0;  //length of each line
    const char * cword;

    for (size_t k = 0; k < len; k++) {
      char * cate = NULL;  //categories of word
      if (larray[j][k] != '_') {
        res = realloc(res, (len_res + 1) * sizeof(*res));
        res[len_res] = larray[j][k];
        len_res++;
      }
      else {
        size_t len_cate = 0;  //length of cate
        k++;
        while (larray[j][k] != '_') {  //if it is not underscore, save it in cate
          cate = realloc(cate, (len_cate + 1) * sizeof(*cate));
          cate[len_cate] = larray[j][k];
          len_cate++;
          if (k >= len) {  //If there is no underscore in the line
            // free everything and quit with error
            free(res);
            freeArr(i, larray);
            free(cate);
            fprintf(stderr, "No matching underscore");
            exit(EXIT_FAILURE);
          }
          k++;
        }
        cword = chooseWord(cate, cats);  //choose word from cats by cate
        size_t len_c = strlen(cword);
        free(cate);  //free categories of word
                     //repalce cate with word in line
        for (size_t m = 0; m < len_c; m++) {
          res = realloc(res, (len_res + 1) * sizeof(*res));
          res[len_res] = cword[m];
          len_res++;
        }
      }
    }
    res = realloc(res, (len_res + 1) * sizeof(*res));
    res[len_res] = '\0';  //make result of story as a string
    printf("%s", res);
    free(res);  //free res
  }
  freeArr(i, larray);  //free larray
}

//sub function used in getWord_cat(), use it to check if name in word.txt is unique
//if unique, return -1
//else, return the index of exist arr which contains name
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

//process with word.txt, store the word in catarray_t type value and return it
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

/*free catarray_t type value with size of n, return void*/
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
