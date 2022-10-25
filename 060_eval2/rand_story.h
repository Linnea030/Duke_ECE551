#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

//any functions you want your main to use

//using this to free array
void freeArr(size_t i, char ** larray);

//using this to get the story when input is NULL
void getStory_cat(FILE * f, catarray_t * cats);

//compare the temp with exist name in arr
int contains(char * temp, category_t * arr, size_t num_cat);

//get cataarray_t from input word.txt
catarray_t * getWord_cat(FILE * f);

//free catarray_t cat in step2
void freecat(catarray_t * cat, size_t n);

//free catarray_t cat used to tracking words in step3
void freepro(category_t * cat, size_t len_pro);

//add word into tracking list cats_pro
void addpro(const char * cword, category_t * cats_pro);

//check if word is valid integer, if it is valid, return -1, else return value of cate
int valid(char * cate, size_t len_cate);

//choose provious word that used
char * choosepro(size_t index, category_t * cats_pro);
#endif
