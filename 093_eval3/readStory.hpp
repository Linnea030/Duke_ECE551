#ifndef __READ_STORY_H___
#define __READ_STORY_H___
#include <fstream>

#include "pstory.hpp"
//use this class to read the story
class ReadStory {
 public:
  std::ifstream ifs;  //ifstream to use

  //constructor
  ReadStory() {}

  //input: char**argv,the path from input of command line,return void
  //find and open ifstream ifs
  void openFile(char ** argv);

  //input: char**argv,the path from input of command line,return void
  //process file in step1
  void processFile1(char ** argv);

  //input: char**argv,the path from input of command line,return void
  //process file in step2
  void processFile2(char ** argv);

  //input: char**argv,the path from input of command line,return void
  //process file in step3
  void processFile3(char ** argv);

  //input: char**argv,the path from input of command line,return void
  //process file in step4
  void processFile4(char ** argv);

  //input: nothing,return void
  //close file of ifs
  void closeFile();
};
#endif
