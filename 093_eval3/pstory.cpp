#include "pstory.hpp"

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void Pstory::print(std::string path) {
  for (int i = 0; i <= p_num; i++) {
    story[i].print_p(path);
  }
}
void Pstory::checkPage(long num, long p_num) {
  if (num > p_num) {
    std::cerr << "No such pagenum!\n";
    exit(EXIT_FAILURE);
  }
}

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

long Pstory::convert(std::string s) {
  //test!!!
  // std::cout << s << std::endl;

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

void Pstory::proStory(std::ifstream & ifs) {
  std::string line;
  p_num = -1;
  while (getline(ifs, line)) {
    //if line is empty
    if (isSpacel(line)) {
      continue;
    }
    //test!!!
    // std::cout << line << "\n";

    //if line is page line
    if (isPage(line)) {
      size_t pos_at = line.find("@");
      std::string s1 = line.substr(0, pos_at);
      //get pagenumber
      long pagenum = convert(s1);

      //test!!!
      //        std::cout << pagenum << std::endl;

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

      //check if valid
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

      //test!!!
      //        std::cout << cpagenum << std::endl;

      //check if pagenum is exist
      checkPage(cpagenum, p_num);

      //get destpage number of choice
      size_t cpos_colon2 = line.find(":", cpos_colon1 + 1);
      std::string cs2 = line.substr(cpos_colon1 + 1, cpos_colon2 - cpos_colon1 - 1);
      long destpage = convert(cs2);
      //check if pagenum is exist
      //checkPage(destpage, p_num);

      //get text of choice
      std::string cs3 = line.substr(cpos_colon2 + 1);

      //creat and put choice into page
      int cnum = story[cpagenum].choice.size() + 1;
      Choice C(cpagenum, destpage, cs3, cnum);
      story[cpagenum].choice.push_back(C);

      //test!!!
      //std::cout << "put choice in vector\n";
    }
    else {
      //test!!!
      // std::cout << "pagenumber" << p_num << std::endl;

      std::cerr << "Invalid line format!\n";
      exit(EXIT_FAILURE);
    }
  }
  //test!!!
  //std::cout << "end page\n";
}
