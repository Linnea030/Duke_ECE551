#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * word = malloc(sizeof(*word));
  word->size = 0;
  word->unknown = 0;
  word->array = malloc(word->size * sizeof(*word->array));
  return word;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->unknown++;
    return;
  }
  for (size_t i = 0; i < c->size; i++) {
    if (strcmp(c->array[i].string, name) == 0) {
      c->array[i].count++;
      return;
    }
  }
  one_count_t add;
  add.count = 1;
  add.string = strdup(name);
  c->size++;
  c->array = realloc(c->array, c->size * sizeof(*c->array));
  c->array[c->size - 1] = add;
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (size_t i = 0; i < c->size; i++) {
    fprintf(outFile, "%s: %d\n", c->array[i].string, c->array[i].count);
  }
  if (c->unknown != 0) {
    fprintf(outFile, "<unknow> : %d\n", c->unknown);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (size_t i = 0; i < c->size; i++) {
    free(c->array[i].string);
  }
  free(c->array);
  free(c);
}
