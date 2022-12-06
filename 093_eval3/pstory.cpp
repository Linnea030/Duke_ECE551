#include "pstory.hpp"

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
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

//print single story in step4
void Pstory::print_single1(std::string path,
                           int i,
                           std::vector<std::pair<long int, std::string> > storyVar) {
  story[i].print_p1(path, storyVar);
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

//check if the line type is page or not
bool Pstory::isPagevar(std::string line) {
  //find first $
  size_t pos_cash = line.find("$");
  if (pos_cash == std::string::npos) {
    //std::cerr << "No $ in line!\n";
    return false;
  }
  //find first = after $
  size_t pos_equal = line.find("=", pos_cash + 1);
  if (pos_equal == std::string::npos) {
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

//check if the line type is choice or not
bool Pstory::isChoicevar(std::string line) {
  //find first [
  size_t pos_braleft = line.find("[");
  if (pos_braleft == std::string::npos) {
    return false;
  }
  //find first = after first [
  size_t pos_equal = line.find("=", pos_braleft + 1);
  if (pos_equal == std::string::npos) {
    return false;
  }
  //find first ] after first =
  //]:??? blank space
  size_t pos_braright = line.find("]", pos_equal + 1);
  if (pos_braright == std::string::npos) {
    return false;
  }
  //find first : after first ]
  size_t pos_colon1 = line.find(":", pos_braright + 1);
  if (pos_colon1 == std::string::npos) {
    return false;
  }
  //find second : after first :
  size_t pos_colon2 = line.find(":", pos_colon1 + 1);
  if (pos_colon2 == std::string::npos) {
    return false;
  }
  return true;
}

//convert string to integer and check if it is valid
long Pstory::convert(std::string s) {
  //if string is empty???
  if (s.empty()) {
    std::cerr << "string is empty\n";
    exit(EXIT_FAILURE);
  }

  //if string is not empty
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

void Pstory::proPage(std::string line) {
  //if line is page line
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
  Page P((size_t)pagenum, s2, s3);
  story.push_back(P);
}

void Pstory::proPagevar(std::string line) {
  //get pagenumber
  //find first $
  size_t pos_cash = line.find("$");
  std::string s1 = line.substr(0, pos_cash);
  long pagenum = convert(s1);
  //error check
  if (pagenum > p_num) {
    std::cerr << "Invalid line format for pagenum variable!\n";
    exit(EXIT_FAILURE);
  }

  //get variable name
  //find first = after $
  size_t pos_equal = line.find("=", pos_cash + 1);
  std::string s2 = line.substr(pos_cash + 1, pos_equal - pos_cash - 1);

  //get variable value
  std::string s3 = line.substr(pos_equal + 1);
  long varValue = convert(s3);

  //check repeated pagenum and variable name???
  std::pair<long int, std::string> varPair = std::make_pair(varValue, s2);
  story[pagenum].var.push_back(varPair);
  //test!!!
  //std::cout << "page" << pagenum << "var size" << story[pagenum].var.size() << std::endl;
}

void Pstory::proChoice(std::string line) {
  //if line is choice line
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
  Choice C((size_t)cpagenum, (size_t)destpage, cs3, cnum);
  story[cpagenum].choice.push_back(C);
}

void Pstory::proChoicevar(std::string line) {
  //get pagenumber of choice
  size_t cpos_bra1 = line.find("[");  //left brackets
  std::string cs1 = line.substr(0, cpos_bra1);
  long cpagenum = convert(cs1);
  //check if pagenum is exist
  checkPage(cpagenum, p_num);
  //check if this page if win or lose
  if (story[cpagenum].pageType == "W" || story[cpagenum].pageType == "L") {
    std::cerr << "Win or Lose type can not have choice!\n";
    exit(EXIT_FAILURE);
  }

  //get variable name
  size_t cpos_equal = line.find("=", cpos_bra1 + 1);
  std::string cs2 = line.substr(cpos_bra1 + 1, cpos_equal - cpos_bra1 - 1);

  //check if cs2 is contained in page???

  //get variable value
  size_t cpos_bra2 = line.find("]", cpos_equal + 1);
  std::string cs3 = line.substr(cpos_equal + 1, cpos_bra2 - cpos_equal - 1);
  long int value = convert(cs3);

  //get destnum
  size_t cpos_colon1 = line.find(":", cpos_bra2 + 1);
  size_t cpos_colon2 = line.find(":", cpos_colon1 + 1);
  std::string cs4 = line.substr(cpos_colon1 + 1, cpos_colon2 - cpos_colon1 - 1);
  long destpage = convert(cs4);

  //get text of choice
  std::string cs5 = line.substr(cpos_colon2 + 1);

  //creat and put choice into page
  long cnum = story[cpagenum].choice.size() + 1;
  Choice C(cpagenum, destpage, cs5, cnum);
  //test!!!
  //  std::cout << "here is pstory.cpp"
  //          << " value=" << value << " key=" << cs2 << std::endl;
  C.choiceVar = std::make_pair(value, cs2);
  C.needVar = true;
  story[cpagenum].choice.push_back(C);
}

//process story in step1
void Pstory::proStory_1(std::ifstream & ifs) {
  std::string line;
  p_num = -1;
  while (getline(ifs, line)) {
    //if line is empty
    if (isSpacel(line)) {
      continue;
    }
    //if line is page line
    if (isPage(line)) {
      proPage(line);
    }
    else if (isChoice(line)) {
      proChoice(line);
    }
    else {
      std::cerr << "Invalid line format!\n";
      exit(EXIT_FAILURE);
    }
  }
}

//process story in step4
void Pstory::proStory_2(std::ifstream & ifs) {
  std::string line;
  p_num = -1;
  while (getline(ifs, line)) {
    //test!!!
    // std::cout << line << std::endl;

    //if line is empty
    if (isSpacel(line)) {
      continue;
    }
    //if line is page line
    if (isPage(line)) {
      //test!!!
      // std::cout << "Page\n";
      proPage(line);
    }
    else if (isPagevar(line)) {
      // std::cout << "Pagevar\n";
      proPagevar(line);
    }
    else if (isChoicevar(line)) {
      //std::cout << "Choicevar\n";
      proChoicevar(line);
    }
    else if (isChoice(line)) {
      //std::cout << "Choice\n";
      proChoice(line);
    }
    else {
      std::cerr << "Invalid line format!\n";
      exit(EXIT_FAILURE);
    }
  }
}

//process story in step
/*
void Pstory::proStory_3(std::ifstream & ifs) {
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
*/

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
    std::getline(std::cin, n);

    //test!!!
    // std::cout << n << std::endl;

    //if input is invalid, input again until valid
    while (!isValidChoice(n, num_choice)) {
      std::cout << "That is not a valid choice, please try again\n";
      std::getline(std::cin, n);
    }

    //get choice number
    long num = convert(n);

    //test!!!
    // std::cout << num << std::endl;

    //update currnum to destpage number

    long nextnum = story[currnum].choice[num - 1].destnum;
    currnum = nextnum;
  }
  //if type is win or lose
  print_single(path, currnum);
}

void Pstory::beginGame_plus(std::string path) {
  long currnum = 0;
  std::string n;
  std::vector<std::pair<long int, std::string> > storyVar;
  //if type is N
  while (story[currnum].pageType != "W" && story[currnum].pageType != "L") {
    //save current variable value in storyVar
    for (unsigned long k = 0; k < story[currnum].var.size(); ++k) {
      storyVar.push_back(story[currnum].var[k]);
    }

    //print page(num).txt and choice
    print_single1(path, currnum, storyVar);
    long num_choice = story[currnum].choice.size();  //get number of choice

    //read from cmd
    std::getline(std::cin, n);

    //if input is invalid, input again until valid
    while (!isValidChoice(n, num_choice)) {
      std::cout << "That is not a valid choice, please try again\n";
      std::getline(std::cin, n);
    }

    long temp = convert(n);
    //check if <UNAVAILABLE>
    while (!story[currnum].choice[temp - 1].available) {
      std::cout << "That choice is not available at this time, please try again\n";
      std::getline(std::cin, n);
      //if input is invalid, input again until valid
      while (!isValidChoice(n, num_choice)) {
        std::cout << "That is not a valid choice, please try again\n";
        std::getline(std::cin, n);
      }
      temp = convert(n);
    }

    //get choice number
    long num = convert(n);

    //update currnum to destpage number
    long nextnum = story[currnum].choice[num - 1].destnum;
    currnum = nextnum;
  }
  //if type is win or lose
  print_single1(path, currnum, storyVar);
}

bool Pstory::isValidChoice(std::string n, long num_choice) {
  //if string is empty???
  if (n.empty()) {
    return false;
  }
  //if string is not empty
  char * c = new char[n.length() + 1];
  std::strcpy(c, n.c_str());
  char * end;
  long num = std::strtol(c, &end, 10);

  //check valid of integer
  if (*end != 0) {
    delete[] c;
    return false;
  }
  //chech if integer if negative
  if (num <= 0) {
    delete[] c;
    return false;
  }
  //check if choice is in this page
  if (num > num_choice) {
    delete[] c;
    return false;
  }
  delete[] c;
  return true;
}

void Pstory::findWay() {
  //long curr_p = 0;  //current page number
  long curr_c = 0;  //current choice number under this page
  //std::vector<long> visited;
  std::map<long, int> visit;
  std::vector<std::pair<Page, long> > Path;
  std::stack<std::vector<std::pair<Page, long> > > todoPath;
  std::vector<std::string> resPath;
  std::pair<Page, long> currPage = std::make_pair(story[0], curr_c);
  Path.push_back(currPage);
  todoPath.push(Path);
  while (!todoPath.empty()) {
    Path = todoPath.top();
    todoPath.pop();
    currPage = Path[Path.size() - 1];
    //curr_p = currPage.first.pageNum;
    if (currPage.first.pageType == "W") {
      //convert(currPath to string)
      std::string way = toString(Path);

      resPath.push_back(way);
      //get visited back
      visit.clear();
      for (unsigned long j = 0; j < todoPath.top().size() - 1; ++j) {
        long index = todoPath.top()[j].first.pageNum;
        visit[index]++;
      }
      continue;
    }
    if (!visit.count(currPage.first.pageNum)) {
      visit[currPage.first.pageNum]++;
      for (unsigned long i = 0; i < currPage.first.choice.size(); ++i) {
        curr_c = i + 1;
        long next_p = currPage.first.choice[i].destnum;
        if (!visit.count(next_p)) {
          std::pair<Page, long> tempPage = std::make_pair(story[next_p], curr_c);
          Path.push_back(tempPage);
          todoPath.push(Path);
          Path.pop_back();
        }
      }
    }
  }
  if (resPath.empty()) {
    std::cout << "This story is unwinnable!\n";
    return;
  }
  printWay(resPath);
}

std::string Pstory::toString(std::vector<std::pair<Page, long> > currPath) {
  std::string path;
  std::stringstream s1;
  for (unsigned long k = 0; k < currPath.size() - 1; ++k) {
    s1 << currPath[k].first.pageNum << "(" << currPath[k + 1].second << "),";
  }
  s1 << currPath[currPath.size() - 1].first.pageNum << "(win)";
  s1 >> path;
  return path;
}

void Pstory::printWay(std::vector<std::string> way) {
  for (unsigned long int i = 0; i < way.size(); ++i) {
    std::cout << way[i] << std::endl;
  }
}

///////////////////////////////////////////////////////////
