#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>
void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  uint64_t * res = new uint64_t[257]();
  std::ifstream ifs;
  ifs.open(fname);

  int c = 0;
  while ((c = ifs.get()) != EOF) {
    //c = ifs.get();
    res[c]++;
  }
  res[256] = 1;
  ifs.close();
  return res;
}
