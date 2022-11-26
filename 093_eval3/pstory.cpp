#include "pstory.hpp"

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

//print all the story in step1
void Pstory::print(std::string path) {
  for (int i = 0; i <= p_num; i++) {
    story[i].print_p(path, 1);
  }
}
//print single story in step2
void Pstory::print_single(std::string path, int i) {
  story[i].print_p(path, 2);
}

//check if the pagenumber is valid in step1
void Pstory::checkPage(long num, long p_num) {
  if (num > p_num) {
    std::cerr << "No such pagenum!\n";
    exit(EXIT_FAILURE);
  }
}

//check if the line type is page or not
bool Pstory::isPage(std::string line) {
  //find first @
  size_t pos_at = line.find("@");
  if (pos_at == std::string::npos) {
    //std::cerr << "No @ in line!\n";
    return false;
  }
  //find first : after @
  size_t pos_colon = line.find(":", pos_at + 1);
  if (pos_colon == std::string::npos) {
    return false;
  }
  return true;
}
//check if the line type is choice or not
bool Pstory::isChoice(std::string line) {
  //find first :
  size_t pos_colon = line.find(":");
  if (pos_colon == std::string::npos) {
    //std::cerr << "No : in line!\n";
    return false;
  }
  //find second :
  size_t pos_colon1 = line.find(":", pos_colon + 1);
  if (pos_colon1 == std::string::npos) {
    return false;
  }
  return true;
}

//convert string to integer and check if it is valid
long Pstory::convert(std::string s) {
  char * c = new char[s.length() + 1];
  std::strcpy(c, s.c_str());
  char * end;
  long num = std::strtol(c, &end, 10);
  //check valid of integer
  if (*end != 0) {
    std::cerr << "Invalid integer!\n";
    delete[] c;
    exit(EXIT_FAILURE);
  }
  //chech if integer if negative
  if (num < 0) {
    std::cerr << "Negative integer!\n";
    delete[] c;
    exit(EXIT_FAILURE);
  }
  delete[] c;
  return num;
}

//check if the line only contains blackspace and new line
bool Pstory::isSpacel(std::string line) {
  unsigned long num = line.size();
  std::string space = " ";
  std::string newline = "\n";
  for (unsigned long i = 0; i < num; ++i) {
    std::string s = line.substr(i, 1);
    if ((s.compare(space)) != 0 && s.compare(newline) != 0) {
      return false;
    }
  }
  return true;
}
//process story in step1
void Pstory::proStory(std::ifstream & ifs) {
  std::string line;
  p_num = -1;
  while (getline(ifs, line)) {
    //if line is empty
    if (isSpacel(line)) {
      continue;
    }

    //if line is page line
    if (isPage(line)) {
      //get pagenumber
      size_t pos_at = line.find("@");
      std::string s1 = line.substr(0, pos_at);
      long pagenum = convert(s1);
      //if pagenumber if not continuous
      if (pagenum != p_num + 1) {
        std::cerr << "Invalid line format for pagenum!\n";
        exit(EXIT_FAILURE);
      }
      p_num++;

      //get pagetype
      //  char ptype;
      size_t pos_colon = line.find(":");
      std::string s2 = line.substr(pos_at + 1, pos_colon - pos_at - 1);
      //check if it is win or lose
      check_wl(s2);
      //check if pagetype is valid or not
      if (s2 != "N" && s2 != "W" && s2 != "L") {
        std::cerr << "Invalid line format for page type!\n";
        exit(EXIT_FAILURE);
      }

      //get file name
      std::string s3 = line.substr(pos_colon + 1);
      if (s3.find(".txt") == std::string::npos) {
        std::cerr << "Invalid file name!\n";
        exit(EXIT_FAILURE);
      }

      //create new page
      Page P(pagenum, s2, s3);
      story.push_back(P);
    }

    //if line is choice line
    else if (isChoice(line)) {
      //get pagenumber of choice
      size_t cpos_colon1 = line.find(":");
      std::string cs1 = line.substr(0, cpos_colon1);
      long cpagenum = convert(cs1);
      //check if pagenum is exist
      checkPage(cpagenum, p_num);
      //check if this page if win or lose
      if (story[cpagenum].pageType == "W" || story[cpagenum].pageType == "L") {
        std::cerr << "Win or Lose type can not have choice!\n";
        exit(EXIT_FAILURE);
      }

      //get destpage number of choice
      size_t cpos_colon2 = line.find(":", cpos_colon1 + 1);
      std::string cs2 = line.substr(cpos_colon1 + 1, cpos_colon2 - cpos_colon1 - 1);
      long destpage = convert(cs2);

      //test!!!
      //      std::cout << destpage << std::endl;

      //get text of choice
      std::string cs3 = line.substr(cpos_colon2 + 1);

      //creat and put choice into page
      int cnum = story[cpagenum].choice.size() + 1;
      Choice C(cpagenum, destpage, cs3, cnum);
      story[cpagenum].choice.push_back(C);
    }
    else {
      std::cerr << "Invalid line format!\n";
      exit(EXIT_FAILURE);
    }
  }
}

void Pstory::check_wl(std::string s2) {
  if (s2 == "W") {
    win_num++;
  }
  else if (s2 == "L") {
    lose_num++;
  }
}

void Pstory::checkValid() {
  //3a. check destpage is valid or not
  std::map<int, int> hashmap;
  for (long i = 0; i < p_num; ++i) {
    for (unsigned long j = 0; j < story[i].choice.size(); ++j) {
      long dest = story[i].choice[j].destnum;
      if (dest > p_num) {
        std::cerr << "No such destpage file!\n";
        exit(EXIT_FAILURE);
      }
      hashmap[dest]++;
    }
  }

  //3b. check if every page is referenced
  for (unsigned long k = 1; k < hashmap.size(); ++k) {
    if (hashmap[k] < 1) {
      std::cerr << "This page " << k << " is not referenced!\n";
      exit(EXIT_FAILURE);
    }
  }

  //3c. check win and lose page
  if (win_num < 1) {
    std::cerr << "No page for win\n";
    exit(EXIT_FAILURE);
  }
  if (lose_num < 1) {
    std::cerr << "No page for lose\n";
    exit(EXIT_FAILURE);
  }
}

void Pstory::beginGame(std::string path) {
  long currnum = 0;
  std::string n;
  //if type is N
  while (story[currnum].pageType != "W" && story[currnum].pageType != "L") {
    //print page(num).txt and choice
    print_single(path, currnum);
    long num_choice = story[currnum].choice.size();  //get number of choice
    //read from cmd
    std::cin >> n;

    //test!!!
    // std::cout << n << std::endl;

    //if input is invalid, input again until valid
    while (!isValidChoice(n, num_choice)) {
      std::cout << "That is not a valid choice, please try again\n";
      std::cin >> n;
    }

    //get choice number
    long num = convert(n);

    //test!!!
    // std::cout << num << std::endl;

    //update currnum to destpage number

    //test!!!
    /*    for (unsigned long x = 0; x < story.size(); ++x) {
      for (unsigned long y = 0; y < story[x].choice.size(); ++y) {
        long p = story[x].choice[y].destnum;
        std::cout << p << std::endl;
      }
    }
    std::cout << "curr=" << currnum << ",num=" << num << std::endl;
    */

    long nextnum = story[currnum].choice[num - 1].destnum;
    currnum = nextnum;
  }
  //if type is win or lose
  print_single(path, currnum);
}

bool Pstory::isValidChoice(std::string n, long num_choice) {
  char * c = new char[n.length() + 1];
  std::strcpy(c, n.c_str());
  char * end;
  long num = std::strtol(c, &end, 10);

  //check valid of integer
  if (*end != 0) {
    //test!!!
    //  std::cout << "not integer\n";

    delete[] c;
    return false;
  }
  //chech if integer if negative
  if (num < 0) {
    //test!!!
    //std::cout << "<0\n";

    delete[] c;
    return false;
  }
  //check if choice is in this page
  if (num > num_choice) {
    //test!!!
    //std::cout << "no such choice\n";

    delete[] c;
    return false;
  }
  delete[] c;
  return true;
}
