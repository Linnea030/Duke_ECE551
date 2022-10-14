#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assert.h"
#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "No such file");
    return NULL;
  }
  counts_t * answer = createCounts();
  //for every key in file
  char * key = NULL;
  size_t sz;
  while (getline(&key, &sz, f) >= 0) {
    char * p = strchr(key, '\n');
    if (p != NULL) {
      *p = '\0';
    }
    char * value = lookupValue(kvPairs, key);
    addCount(answer, value);
    free(key);
    key = NULL;
  }
  free(key);
  assert(fclose(f) == 0);
  return answer;
}

int main(int argc, char ** argv) {
  if (argc <= 2) {
    fprintf(stderr, "no argc");
    return EXIT_FAILURE;
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    counts_t * c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    if (f == NULL) {
      fprintf(stderr, "Open error");
      exit(EXIT_FAILURE);
    }
    printCounts(c, f);  //print the counts from c into the FILE f
    assert(fclose(f) == 0);
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
  freeKVs(kv);  //free the memory for kv
  return EXIT_SUCCESS;
}
