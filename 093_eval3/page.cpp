#include "page.hpp"

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

void Page::print_p(std::string path) {
  //print pagenumber
  std::cout << "Page " << pageNum << "\n";
  std::cout << "==========\n";

  //print text
  //convert file name
  std::ifstream ifsp;
  std::string path1;
  path1 = path + "/" + fileName;
  char * spath = new char[path1.length() + 1];
  std::strcpy(spath, path1.c_str());
  //open file
  ifsp.open(spath);
  delete[] spath;  //delete
  if (!ifsp.is_open()) {
    std::cerr << "Open file failed!\n";
    exit(EXIT_FAILURE);
  }
  std::string line;
  while (getline(ifsp, line)) {
    std::cout << line << "\n";
  }
  ifsp.close();
  //error check

  //check the page type
  if (pageType == "N") {
    //if N type print
    std::cout << "\n";
    std::cout << "What would you like to do?\n";
    std::cout << "\n";
    //print choice
    int n = choice.size();
    for (int i = 0; i < n; ++i) {
      choice[i].print_c();
    }
  }
  else if (pageType == "W") {
    //if W type
    std::cout << "\n";
    std::cout << "Congratulations! You have won. Hooray!\n";
  }
  else if (pageType == "L") {
    //if L type
    std::cout << "\n";
    std::cout << "Sorry, you have lost. Better luck next time!\n";
  }
}
