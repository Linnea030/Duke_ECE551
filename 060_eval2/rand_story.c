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

//check if word is valid integer, if it is valid, return -1, else return value of cate
int valid(char * cate, size_t len_cate) {
  int value = atoi(cate);  //cited as AOP chapter10
  int temp = value;
  size_t len_value = 0;
  //printf("%s\n", cate);
  if (value <= 0) {  // if cate is string or not positive value
    return -1;
  }
  while (temp != 0) {  //check the length of value
    temp = temp / 10;
    len_value++;
  }
  if (len_value != len_cate - 1) {  //if length of value is not equal to length of cate,
    //there is other character in cate
    return -1;
  }
  else {
    return value;  // value is the index of word
  }
}

//add word into tracking list cats_pro
void addpro(const char * cword, category_t * cats_pro) {
  cats_pro->words =
      realloc(cats_pro->words, (cats_pro->n_words + 1) * sizeof(*(cats_pro->words)));
  cats_pro->words[cats_pro->n_words] = strndup(cword, strlen(cword));
  cats_pro->n_words++;
}

//choose provious word that used
char * choosepro(size_t index, category_t * cats_pro) {
  char * cword = NULL;
  cword = cats_pro->words[cats_pro->n_words - index];
  return cword;
}

//free cats_pro which is used to track the provious words
void freepro(category_t * cat, size_t len_pro) {
  for (size_t i = 0; i < len_pro; i++) {
    free(cat->words[i]);
  }
  free(cat->words);
  free(cat);
}

//delete repeated words
void delete_word(char * cate, const char * cword, catarray_t * cats) {
  for (size_t a = 0; a < cats->n; a++) {
    int x = strcmp(cate, cats->arr[a].name);
    if (x == 0) {
      for (size_t b = 0; b < cats->arr[a].n_words; b++) {
        int y = strcmp(cword, cats->arr[a].words[b]);
        if (y == 0) {
          char * temp = cats->arr[a].words[b];
          cats->arr[a].words[b] = cats->arr[a].words[cats->arr[a].n_words - 1];
          cats->arr[a].words[cats->arr[a].n_words - 1] = temp;
          free(temp);
          cats->arr[a].n_words--;
          break;
        }
      }
      break;
    }
  }
}

//get story by input category and catarray_t
void getStory_cat(FILE * f, catarray_t * cats, int op) {
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

  //using cats_pro to track the provious words
  category_t * cats_pro =
      malloc(sizeof(*cats_pro));  //using it to track the provious words
  cats_pro->name = NULL;
  cats_pro->words = malloc(sizeof(*(cats_pro->words)));
  cats_pro->n_words = 0;  // initialize the variables in it

  int del = 0;

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
        //make cate as string
        cate = realloc(cate, (len_cate + 1) * sizeof(*cate));
        cate[len_cate] = '\0';
        len_cate++;

        //check if cate is valid integer, using provious words
        int index = valid(cate, len_cate);
        //printf("%d\n", index);

        if (index != -1) {
          //using provious words
          cword = choosepro(index, cats_pro);
        }
        //else, use it to choose word
        else {
          cword = chooseWord(cate, cats);  //choose word from cats by cate
          //cword += '\0';                   //make cword as string
          if (op == -1) {
            //delete cword from cats but not now
            del = 2;
          }
        }

        // add cword into cats_pro
        addpro(cword, cats_pro);

        //put cword into story
        size_t len_c = strlen(cword);
        //free(cate);  //free categories of word
        //repalce cate with word in line
        for (size_t m = 0; m < len_c; m++) {
          res = realloc(res, (len_res + 1) * sizeof(*res));
          res[len_res] = cword[m];
          len_res++;
        }

        //delete cword from cats
        if (del == 2) {
          delete_word(cate, cword, cats);
          del = 0;
          //printWords(cats);
        }
        free(cate);  //free categories of word
      }
    }
    res = realloc(res, (len_res + 1) * sizeof(*res));
    res[len_res] = '\0';  //make result of story as a string
    printf("%s", res);
    free(res);  //free res
  }
  freepro(cats_pro, cats_pro->n_words);
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
  char * line = NULL;                    //line used to save each line of file
  char ** larray = NULL;                 //larray is an array to save all the lines
  size_t sz = 0;                         //size of line
  size_t i = 0;                          //size of larray
  while (getline(&line, &sz, f) >= 0) {  //using getline to save each line
    larray = realloc(larray, (i + 1) * sizeof(*larray));
    larray[i] = line;
    line = NULL;  //let line be another buffer
    i++;
  }
  free(line);  //free line

  //declare cat as return result
  catarray_t * cat = malloc(sizeof(*cat));
  cat->arr = malloc(sizeof(*cat->arr));
  cat->n = 0;  //initialize cat

  //traverse each line to get cat
  for (size_t j = 0; j < i; j++) {
    //if there is no : in the line
    if (strchr(larray[j], ':') == NULL) {
      fprintf(stderr, "No : in the line %ld \n", j);
      exit(EXIT_FAILURE);
    }
    //if there is no \0 in the line
    if (strchr(larray[j], '\0') == NULL) {
      fprintf(stderr, "This line is not string with new line %ld \n", j);
      exit(EXIT_FAILURE);
    }

    //get new name from word before : in one line
    size_t len_line = strlen(larray[j]);  // get length of this line
    size_t index_line = 0;                //declare index in line
    int x = -1;                           //declare x to save the index of existed arr
    for (size_t k = 0; k < len_line;
         k++) {                   //traverse each character and save words in temp
      if (larray[j][k] == ':') {  //save name in arr  in temp
        size_t len_name = k;      //length of name in arr
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
        //temp is in arr
        else {
          free(temp);  //free temp
        }
        index_line = k + 1;  //get the index of character after :
        break;
      }
    }

    //get word from word after :
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
    printWords(cat);
  }
  freeArr(i, larray);  //free larray
  return cat;          //return result of category array
}

/*free catarray_t type value with size of n, return void*/
void freecat(catarray_t * cat, size_t n) {
  for (size_t i = 0; i < n; i++) {
    free(cat->arr[i].name);                             //free name in arr
    for (size_t j = 0; j < cat->arr[i].n_words; j++) {  //free each words in arr
      free(cat->arr[i].words[j]);
    }
    free(cat->arr[i].words);  //free words
  }
  free(cat->arr);  //free arr
  free(cat);       //free cat which contains arr
}
