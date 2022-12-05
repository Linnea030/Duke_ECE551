#include "readStory.hpp"

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

void ReadStory::openFile(char ** argv) {
  //extent the path to real path
  std::string s;
  std::stringstream ss;
  ss << argv[1];
  ss >> s;
  std::string path1;
  //path1 is argv+/story.txt
  path1 = s + "/story.txt";
  //path is the same as path1 but with type of char
  char * path = new char[path1.length() + 1];
  std::strcpy(path, path1.c_str());

  //open the file ifs
  //std::ifstream ifs;
  ifs.open(path);
  delete[] path;  //free memory of path

  //error check for failed open(no such file, invalid path)
  if (!ifs.is_open()) {
    std::cerr << "Open file failed!\n";
    exit(EXIT_FAILURE);
  }
  //return ifs;
}

void ReadStory::processFile1(char ** argv) {
  //convert argv to char
  std::string s;
  std::stringstream ss;
  ss << argv[1];
  ss >> s;
  //read and print story.txt file
  Pstory ps;
  ps.proStory_1(ifs);
  ps.print(s);
}

void ReadStory::processFile2(char ** argv) {
  //convert argv to char
  std::string s;
  std::stringstream ss;
  ss << argv[1];
  ss >> s;
  //read and print story.txt file
  Pstory ps;
  ps.proStory_1(ifs);
  ps.checkValid();
  ps.beginGame(s);
}

void ReadStory::processFile3(char ** argv) {
  //convert argv to char
  std::string s;
  std::stringstream ss;
  ss << argv[1];
  ss >> s;
  //read and print story.txt file
  Pstory ps;
  ps.proStory_1(ifs);
  ps.checkValid();
  ps.findWay();
}

void ReadStory::processFile4(char ** argv) {
  //convert argv to char
  std::string s;
  std::stringstream ss;
  ss << argv[1];
  ss >> s;
  //read and print story.txt file
  Pstory ps;
  ps.proStory(ifs);
  ps.checkValid();
  ps.beginGame_plus(s);
}

void ReadStory::closeFile() {
  //close fail
  ifs.close();
  //error check failed close
}
