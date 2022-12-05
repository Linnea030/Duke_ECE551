#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "readStory.hpp"
int main(int argc, char ** argv) {
  //check input command line
  if (argc != 2) {
    std::cerr << "The command line input has errors!\n";
    exit(EXIT_FAILURE);
  }
  //open the file
  ReadStory rs;
  rs.openFile(argv);

  //process the whole story
  rs.processFile4(argv);

  //close story.txt file
  rs.closeFile();

  return EXIT_SUCCESS;
}
