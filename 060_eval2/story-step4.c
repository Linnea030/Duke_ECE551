#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  //If there are not two command line arguments
  if (argc < 3 || argc > 4) {
    fprintf(stderr, "argc invalid\n");
    exit(EXIT_FAILURE);
  }
  int op = 0;
  //If there are 3 arguments in command line
  if (argc == 3) {  //using functions in step3
    //If there is no input file1 for words
    if (argv[1] == NULL) {
      fprintf(stderr, "No input file\n");
      exit(EXIT_FAILURE);
    }
    FILE * f1 = fopen(argv[1], "r");
    //open file1 is fail
    if (f1 == NULL) {
      fprintf(stderr, "Input file is NULL\n");
      exit(EXIT_FAILURE);
    }
    //If there is no input file2 for story
    if (argv[2] == NULL) {
      fprintf(stderr, "No input file\n");
      exit(EXIT_FAILURE);
    }
    FILE * f2 = fopen(argv[2], "r");
    //open file2 is fail
    if (f2 == NULL) {
      fprintf(stderr, "Input file is NULL\n");
      exit(EXIT_FAILURE);
    }
    //cats used to save words
    catarray_t * cats = getWord_cat(f1);
    //using function to replace the words and generate a story
    getStory_cat(f2, cats, op);
    //free
    freecat(cats, cats->n);
    //close file, if fail assert
    assert(fclose(f2) == 0);
    assert(fclose(f1) == 0);
  }

  //if there are 4 arguments
  else if (argc == 4) {
    //if first argument is not -n,exit and report
    if (strcmp(argv[1], "-n") != 0) {
      fprintf(stderr, "argv[1] is not -n\n");
      exit(EXIT_FAILURE);
    }
    //if argv is NULL
    if (argv[2] == NULL) {
      fprintf(stderr, "No input file\n");
      exit(EXIT_FAILURE);
    }
    FILE * f1 = fopen(argv[2], "r");
    //open file1 is fail
    if (f1 == NULL) {
      fprintf(stderr, "Input file is NULL\n");
      exit(EXIT_FAILURE);
    }
    //If there is no input file2 for story
    if (argv[3] == NULL) {
      fprintf(stderr, "No input file\n");
      exit(EXIT_FAILURE);
    }
    FILE * f2 = fopen(argv[3], "r");
    //open file2 is fail
    if (f2 == NULL) {
      fprintf(stderr, "Input file is NULL\n");
      exit(EXIT_FAILURE);
    }
    op = -1;  //operation code for op =-1 means no repeated words

    //cats used to save words
    catarray_t * cats = getWord_cat(f1);
    //using function to replace the words and generate a story
    getStory_cat(f2, cats, op);
    //free
    freecat(cats, cats->n);
    //close file, if fail assert
    assert(fclose(f2) == 0);
    assert(fclose(f1) == 0);
  }
  return EXIT_SUCCESS;
}
