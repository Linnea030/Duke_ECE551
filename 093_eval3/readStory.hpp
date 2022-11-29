#ifndef __READ_STORY_H___
#define __READ_STORY_H___
#include <fstream>

#include "pstory.hpp"

class ReadStory {
 public:
  std::ifstream ifs;
  ReadStory() {}
  void openFile(char ** argv);
  void processFile1(char ** argv);
  void processFile2(char ** argv);
  void processFile3(char ** argv);
  void closeFile();
};
#endif
