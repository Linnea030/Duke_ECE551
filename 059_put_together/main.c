#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "No such file");
    exit(EXIT_FAILURE);
  }
  counts_t * word = createCounts();
  char * line = NULL;
  size_t sz;
  while (getline(&line, &sz, f) > 0) {
    char * name = lookupValue(kvPairs, line);
    addCount(word, name);
    free(line);
    line = NULL;
  }
  free(line);
  int n = fclose(f);
  if (n != 0) {
    fprintf(stderr, "Failed to close");
    exit(EXIT_FAILURE);
  }
  return word;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc <= 2) {
    fprintf(stderr, "no argc");
    exit(EXIT_FAILURE);
  }
  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    counts_t * c = countFile(argv[i], kv);
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)

    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    if (f == NULL) {
      fprintf(stderr, "No such file");
      exit(EXIT_FAILURE);
    }
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    int n = fclose(f);
    if (n != 0) {
      fprintf(stderr, "Failed to close");
      exit(EXIT_FAILURE);
    }
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
