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
void getStory_cat(FILE * f);

#endif
