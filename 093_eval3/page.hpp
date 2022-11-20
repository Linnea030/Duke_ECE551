#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

#include "choice.hpp"
//#include "cline.hpp"
//#include "pline.hpp"
class Page {
 public:
  long pageNum;
  std::string pageType;
  std::string fileName;
  std::vector<Choice> choice;

  Page(long pn, std::string pt, std::string fn) :
      pageNum(pn), pageType(pt), fileName(fn) {}

  void print_p(std::string path) {
    //print pagenumber
    std::cout << "Page " << pageNum << "\n";
    std::cout << "==========\n";
    //print text
    std::ifstream ifsp;
    std::string path1;
    path1 = path + "/" + fileName;

    //test!!!
    // std::cout << path << std::endl;

    char * spath = new char[path1.length() + 1];
    std::strcpy(spath, path1.c_str());

    //test!!!
    // std::cout << spath << std::endl;

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
    //error check???

    //check the page type
    if (pageType == "N") {
      std::cout << "\n";
      std::cout << "What would you like to do?\n";
      std::cout << "\n";
      int n = choice.size();
      for (int i = 0; i < n; ++i) {
        choice[i].print_c();
      }
    }
    else if (pageType == "W") {
      std::cout << "\n";
      std::cout << "Congratulations! You have won. Hooray!\n";
    }
    else if (pageType == "L") {
      std::cout << "\n";
      std::cout << "Sorry, you have lost. Better luck next time!\n";
    }
  }
};
