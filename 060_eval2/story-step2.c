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
  FILE * f = fopen(argv[1], "r");
  //open file is fail
  if (f == NULL) {
    fprintf(stderr, "Input file is NULL\n");
    exit(EXIT_FAILURE);
  }
  //using function to parsing the story

  //close file, if fail assert
  assert(fclose(f) == 0);
  return EXIT_SUCCESS;
}
