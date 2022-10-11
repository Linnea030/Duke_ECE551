#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  size_t size = strlen(inputName);
  //char * add = ".count\0";
  char * output;  // = malloc((size + strlen(add)) * sizeof(*output));
  output = strndup(inputName, size);
  output = realloc(output, (size + 8) * sizeof(*output));
  strcpy(output + size, ".count\0");
  return output;
}
