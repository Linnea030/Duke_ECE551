#include "readStory.hpp"

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

//open file
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
}

//process file in step1
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

//process file in step2
void ReadStory::processFile2(char ** argv) {
  //convert argv to char
  std::string s;
  std::stringstream ss;
  ss << argv[1];
  ss >> s;
  //read and print story.txt file
  Pstory ps;
  ps.proStory_1(ifs);
  //check if story is valid
  ps.checkValid(s);
  //start game
  ps.beginGame(s);
}

//process file in step3
void ReadStory::processFile3(char ** argv) {
  //convert argv to char
  std::string s;
  std::stringstream ss;
  ss << argv[1];
  ss >> s;
  //read and print story.txt file
  Pstory ps;
  ps.proStory_1(ifs);
  //check if story is valid
  ps.checkValid(s);
  //print all the ways to win
  ps.findWay();
}

//process file in step4
void ReadStory::processFile4(char ** argv) {
  //convert argv to char
  std::string s;
  std::stringstream ss;
  ss << argv[1];
  ss >> s;
  //read and print story.txt file
  Pstory ps;
  ps.proStory_2(ifs);
  //check if story is valid
  ps.checkValid(s);
  //start game
  ps.beginGame_plus(s);
}

// close file of ifs
void ReadStory::closeFile() {
  //close fail
  ifs.close();
}
