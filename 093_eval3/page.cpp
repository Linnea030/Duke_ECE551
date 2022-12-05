#include "page.hpp"

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

void Page::print_p(std::string path, int step) {
  if (step == 1) {
    //print pagenumber
    std::cout << "Page " << pageNum << "\n";
    std::cout << "==========\n";
  }
  else if (step == 2) {
    //print newline
    std::cout << "\n";
    std::cout << "\n";
  }

  //print text
  textPrint(path);

  //check the page type
  if (pageType == "N") {
    //if N type print
    std::cout << "\n";
    std::cout << "What would you like to do?\n";
    std::cout << "\n";

    //print choice
    //if in step1 and step2
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

void Page::textPrint(std::string path) {
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
}

void Page::print_p1(std::string path,
                    int step,
                    std::vector<std::pair<long int, std::string> > storyVar) {
  if (step == 4) {
    //print newline
    std::cout << "\n";
    std::cout << "\n";
  }

  //print text
  textPrint(path);

  //check the page type
  if (pageType == "N") {
    //if N type print
    std::cout << "\n";
    std::cout << "What would you like to do?\n";
    std::cout << "\n";

    //print choice
    //if in step4
    int n = choice.size();
    for (int i = 0; i < n; ++i) {
      choice[i].available = true;
      //if this choice is not related to variable, print as usual
      if (choice[i].needVar == false) {
        //test!!!
        //        std::cout << "not related to variable\n";

        choice[i].print_c();
        continue;
      }

      //else, check the validness of variable in this page
      long pos_var = -1;  //the position of variable in var
                          //check if the variable name is existed in this page
      for (unsigned long j = 0; j < storyVar.size(); ++j) {
        //if var exist in this page

        if (storyVar[j].second.compare(choice[i].choiceVar.second) == 0) {
          pos_var = j;  //get the index of variable in var
          break;
        }
      }

      //check if variable existed
      bool existed = (pos_var != -1);
      //check if variable value are the same
      bool valueEqual = (storyVar[pos_var].first == choice[i].choiceVar.first);
      //check if value is 0
      bool valueEqual0 = (choice[i].choiceVar.first == 0);

      if (existed && valueEqual) {
        //if there is such var in this page,the value is equal
        //test!!!
        //        std::cout << "existed and equal\n";
        choice[i].print_c();
      }
      else if (!existed && valueEqual0) {
        //if there is no such var in this page,the default value is 0, and equal
        //test!!!
        // std::cout << "not existed but euqal 0\n";
        choice[i].print_c();
      }
      else {
        //test!!!
        // std::cout << "unavailable\n";
        choice[i].available = false;
        choice[i].print_var();
      }
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

/////////////////////////////////////////////////
bool Page::operator==(const Page & rhs) {
  if (pageNum != rhs.pageNum || pageType != rhs.pageType || fileName != rhs.fileName) {
    return false;
  }
  //if(choice)
  return true;
}

///////////////////////////////////////////////
bool Page::operator!=(const Page & rhs) {
  if (*this != rhs) {
    return false;
  }
  return true;
}
