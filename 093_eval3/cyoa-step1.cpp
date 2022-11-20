#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "pstory.hpp"
int main(int argc, char ** argv) {
  //check input command line
  if (argc != 2) {
    std::cerr << "The command line input has errors!\n";
    exit(EXIT_FAILURE);
  }

  //open the file
  std::string s;
  std::stringstream ss;
  ss << argv[1];
  ss >> s;
  std::string path1;
  path1 = s + "/story.txt";

  //test!!!
  //  std::cout << path1 << std::endl;
  char * path = new char[path1.length() + 1];
  std::strcpy(path, path1.c_str());
  // std::cout << path << std::endl;
  std::ifstream ifs;
  ifs.open(path);

  //open???

  delete[] path;

  std::string buf;
  //while (getline(ifs, buf)) {
  // std::cout << buf << std::endl;
  //}

  if (!ifs.is_open()) {
    std::cerr << "Open file failed!\n";
    exit(EXIT_FAILURE);
  }

  //no such file???
  //invalid path???

  //read and print story.txt file
  Pstory ps;
  ps.proStory(ifs);
  ps.print(s);

  //close story.txt file
  ifs.close();

  //errors check
  //if (ifs.fail()) {
  //std::cerr << "Close file failed in main!\n";
  //}
  return EXIT_SUCCESS;
}
