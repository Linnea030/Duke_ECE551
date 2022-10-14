#include "kv.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvpair_t getPair(char * line) {
  kvpair_t pair;
  char * value = strchr(line, '=');  //get string after first = include =
  if (value == NULL)
    exit(EXIT_FAILURE);
  size_t n = strlen(line) - strlen(value);  //get length of key
  char * v = strchr(value++, '\n');         //get string after first \n
  if (v == NULL) {
    pair.value = value;  //if there is no \n
  }
  else {                                   //if there is \n
    size_t m = strlen(value) - strlen(v);  //get length of value
    pair.value = strndup(value, m);
  }
  pair.key = strndup(line, n);
  return pair;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    //fprintf(stderr,"No input file\n");
    return NULL;
  }
  //give space to answer
  kvarray_t * answer = malloc(sizeof(*answer));
  //give space to answer->pairs
  answer->pairs = malloc(sizeof(*answer->pairs));
  if (answer->pairs == NULL) {
    free(answer);
    return NULL;
  }
  answer->size = 0;

  char * line = NULL;
  size_t sz = 0;
  //getline to get one line in f
  while (getline(&line, &sz, f) >= 0) {
    answer->size++;  //one line means one member in array
    answer->pairs = realloc(answer->pairs, answer->size * sizeof(*answer->pairs));
    //realloc space for answer->pairs because line is increasing
    answer->pairs[answer->size - 1] = getPair(line);
    //getPair from other function
    free(line);
    line = NULL;
  }
  free(line);
  //  free(line);
  int result = fclose(f);
  assert(result == 0);
  return answer;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->size; i++) {
    free(pairs->pairs[i].key);
    free(pairs->pairs[i].value);
  }
  free(pairs->pairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->size; i++) {
    printf("key = '%s' value = '%s'\n", pairs->pairs[i].key, pairs->pairs[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t i = 0; i < pairs->size; i++) {
    if (strcmp(key, pairs->pairs[i].key) == 0) {
      return pairs->pairs[i].value;
    }
  }
  return NULL;
}
