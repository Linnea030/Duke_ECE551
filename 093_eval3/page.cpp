#include "page.hpp"

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

//input string path of the pagefile.txt and which step it is in now
//return is void
//print this page in step1 2
void Page::print_p(std::string path, int step) {
  if (step == 1) {
    //print pagenumber
    std::cout << "Page " << pageNum << "\n";
    std::cout << "==========\n";
  }
  //print text
  textPrint(path);  //1.

  //check the page type
  if (pageType == "N") {
    //if N type print
    std::cout << "\n";                            //2.
    std::cout << "What would you like to do?\n";  //3.
    std::cout << "\n";                            //4.

    //print choice
    int n = choice.size();
    for (int i = 0; i < n; ++i) {  //5.
      choice[i].print_c();
    }
  }
  else if (pageType == "W") {
    //if W type
    std::cout << "\n";                                        //2.
    std::cout << "Congratulations! You have won. Hooray!\n";  //3.
  }
  else if (pageType == "L") {
    //if L type
    std::cout << "\n";                                              //2.
    std::cout << "Sorry, you have lost. Better luck next time!\n";  //3.
  }
}

//input string path of the pagefile.txt
//return is void
//print this page's text, subfunction of print_p and print_p1
void Page::textPrint(std::string path) {
  //print text
  //add path and fileName and convert whole path to char
  std::ifstream ifsp;
  std::string path1;
  path1 = path + "/" + fileName;
  char * spath = new char[path1.length() + 1];
  std::strcpy(spath, path1.c_str());
  //open file
  ifsp.open(spath);
  delete[] spath;  //delete space we new
  //check if it is opened
  if (!ifsp.is_open()) {
    std::cerr << "Open file failed!\n";
    exit(EXIT_FAILURE);
  }
  //if opened, print each line
  std::string line;
  while (getline(ifsp, line)) {
    std::cout << line << "\n";  //1.
  }
  ifsp.close();
  //error check???
}

//input string path of the pagefile.txt and vector storyVar which save the variables
//return void, variable is checked by storyVar (save all variables for now) and choice
//print this page with variable in step4
void Page::print_p1(std::string path,
                    std::vector<std::pair<long int, std::string> > storyVar) {
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
        choice[i].print_c();
        continue;
      }

      //else, check the validness of variable in this page
      long pos_var = -1;  //the position of variable in var
                          //check if the variable name is existed in this page
      for (unsigned long j = 0; j < storyVar.size(); ++j) {
        //if variable is found, get index of this variable in storyVar
        if (storyVar[j].second.compare(choice[i].choiceVar.second) == 0) {
          pos_var = j;  //get the index of variable in var
          break;
        }
      }

      //check if variable existed
      bool existed = (pos_var != -1);
      //check if variable value are the same
      //bool valueEqual = (storyVar[pos_var].first == choice[i].choiceVar.first);
      //check if value is 0
      bool valueEqual0 = (choice[i].choiceVar.first == 0);

      //if existed and value equal
      if (existed) {
        //if there is such var in this page,the value is equal
        if (storyVar[pos_var].first == choice[i].choiceVar.first) {
          choice[i].print_c();
        }
        //if no such variable's value
        else {
          choice[i].available = false;
          choice[i].print_var();
        }
      }
      //if it is not existed
      else if (!existed) {
        //if there is no such var in this page,the default value is 0, and equal
        if (valueEqual0) {
          choice[i].print_c();
        }
        //if no such variable's value
        else {
          choice[i].available = false;
          choice[i].print_var();
        }
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

Page & Page::operator=(const Page & rhs) {
  if (this != &rhs) {
    pageNum = rhs.pageNum;
    pageType = rhs.pageType;
    fileName = rhs.fileName;
    choice = rhs.choice;
    var = rhs.var;
  }
  return *this;
}
