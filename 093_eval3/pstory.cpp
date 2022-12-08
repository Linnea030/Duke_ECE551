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
    return false;
  }
  //check if valid number before @
  std::string s1 = line.substr(0, pos_at);
  if (isNumber(s1) == false) {
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
    return false;
  }
  //check if valid number before $
  std::string s1 = line.substr(0, pos_cash);
  if (isNumber(s1) == false) {
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
    return false;
  }
  //check if valid number before :
  std::string s1 = line.substr(0, pos_colon);
  if (isNumber(s1) == false) {
    return false;
  }
  //find second : after first :
  size_t pos_colon1 = line.find(":", pos_colon + 1);
  if (pos_colon1 == std::string::npos) {
    return false;
  }
  return true;
}

//check if the line type is choice or not
bool Pstory::isChoicevar(std::string line) {
  //find first [ left brackets
  size_t pos_braleft = line.find("[");
  if (pos_braleft == std::string::npos) {
    return false;
  }
  //check if valid number before [
  std::string s1 = line.substr(0, pos_braleft);
  if (isNumber(s1) == false) {
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
//check if string s is a number
bool Pstory::isNumber(std::string s) {
  //if string is empty
  if (s.empty()) {
    return false;
  }
  //if string is not empty
  char * c = new char[s.length() + 1];
  std::strcpy(c, s.c_str());
  char * end;
  long num = std::strtol(c, &end, 10);
  //check valid of integer
  //if pointer end is not point to null
  int len_end = strlen(end);
  if (*end != 0 || len_end != 0) {
    delete[] c;
    return false;
  }
  //if it is a negative number
  if (num < 0) {
    delete[] c;
    return false;
  }
  delete[] c;
  return true;
}

//convert string to integer and check if it is valid
long Pstory::convert(std::string s) {
  //if string is empty
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
  //if pointer end is pointer to null
  int len_end = strlen(end);
  if (*end != 0 || len_end != 0) {
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

//convert string to integer and check if it is valid, but it can be negative
long Pstory::convert1(std::string s) {
  //if string is empty
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
  //if pointer end is pointer to null
  int len_end = strlen(end);
  if (*end != 0 || len_end != 0) {
    std::cerr << "Invalid integer!\n";
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
  //traverse each char, to find something that is not space or newline
  for (unsigned long i = 0; i < num; ++i) {
    std::string s = line.substr(i, 1);
    //if not a space or newline
    if ((s.compare(space)) != 0 && s.compare(newline) != 0) {
      return false;
    }
  }
  return true;
}
//process Page without variable
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
  size_t pos_colon = line.find(":", pos_at + 1);
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

  //create new page
  Page P((size_t)pagenum, s2, s3);
  story.push_back(P);
}
//process Page with variable
void Pstory::proPagevar(std::string line) {
  //get pagenumber
  //find first $
  size_t pos_cash = line.find("$");
  std::string s1 = line.substr(0, pos_cash);
  long pagenum = convert(s1);
  //error check for page declaration must appear before anything else
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
  long varValue = convert1(s3);

  //check repeated pagenum and variable name???
  std::pair<long int, std::string> varPair = std::make_pair(varValue, s2);
  story[pagenum].var.push_back(varPair);
}
//process Choice without variable
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

  //get text of choice
  std::string cs3 = line.substr(cpos_colon2 + 1);

  //creat and put choice into page
  int cnum = story[cpagenum].choice.size() + 1;
  Choice C((size_t)cpagenum, (size_t)destpage, cs3, cnum);
  story[cpagenum].choice.push_back(C);
}
//process Choice with variable
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
  long int value = convert1(cs3);

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
  C.choiceVar = std::make_pair(value, cs2);
  C.needVar = true;
  story[cpagenum].choice.push_back(C);
}

//process story in step1 2 3
void Pstory::proStory_1(std::ifstream & ifs) {
  std::string line;
  p_num = -1;
  while (getline(ifs, line)) {
    //if line is empty
    if (isSpacel(line)) {
      std::cout << "blank line" << std::endl;
      continue;
    }
    //if line is page line
    if (isPage(line)) {
      std::cout << "page line" << std::endl;
      proPage(line);
    }
    //if line is choice line
    else if (isChoice(line)) {
      std::cout << "choice line" << std::endl;
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
    //if line is empty
    if (isSpacel(line)) {
      continue;
    }
    //if line is page line
    if (isPage(line)) {
      proPage(line);
    }
    //if line is page variable line
    else if (isPagevar(line)) {
      proPagevar(line);
    }
    //if line is choice variable line
    else if (isChoicevar(line)) {
      proChoicevar(line);
    }
    //if line is choice line
    else if (isChoice(line)) {
      proChoice(line);
    }
    else {
      std::cerr << "Invalid line format!\n";
      exit(EXIT_FAILURE);
    }
  }
}
//check if there exist at least 1 win and 1 lose page
void Pstory::check_wl(std::string s2) {
  if (s2 == "W") {  //winpage number +1
    win_num++;
  }
  else if (s2 == "L") {  //losepage number +1
    lose_num++;
  }
}
//check valid conditions for step2 3 4
void Pstory::checkValid() {
  //3a. check destpage is valid or not
  std::map<int, int> hashmap;
  //traverse all choice to find destpage and save them in a map
  for (long i = 0; i <= p_num; ++i) {
    for (unsigned long j = 0; j < story[i].choice.size(); ++j) {
      size_t dest = story[i].choice[j].destnum;  //get destpage
      if ((long)dest > p_num) {                  //if destpage is not existed
        std::cerr << "No such destpage file!\n";
        exit(EXIT_FAILURE);
      }
      //page is referenced by others
      if (dest != story[i].choice[j].pagenum) {
        hashmap[dest] = 1;
      }
    }
  }
  //3b. check if every page is referenced
  for (long k = 1; k < p_num + 1; ++k) {
    if (hashmap[k] == 0) {  //not referenced
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
//begingame for step1 2 3,start the game for user
void Pstory::beginGame(std::string path) {
  long currnum = 0;
  //if type is N
  while (story[currnum].pageType != "W" && story[currnum].pageType != "L") {
    std::string n;
    //print page(num).txt and choice
    print_single(path, currnum);
    long num_choice = story[currnum].choice.size();  //get number of choice
    //read from cmd
    std::cin >> n;

    //if input is invalid, input again until valid
    while (!isValidChoice(n, num_choice)) {
      std::cout << "That is not a valid choice, please try again\n";
      std::cin >> n;
    }
    //get choice number
    long num = convert(n);

    //update currnum to destpage number
    long nextnum = story[currnum].choice[num - 1].destnum;
    currnum = nextnum;
  }
  //if type is win or lose
  print_single(path, currnum);
}
//begingame for step4,start the game for user
void Pstory::beginGame_plus(std::string path) {
  long currnum = 0;
  std::vector<std::pair<long int, std::string> > storyVar;
  //if type is N
  while (story[currnum].pageType != "W" && story[currnum].pageType != "L") {
    std::string n;
    //save current variable value in storyVar
    for (unsigned long k = 0; k < story[currnum].var.size(); ++k) {
      storyVar.push_back(story[currnum].var[k]);
    }

    //print page(num).txt and choice
    print_single1(path, currnum, storyVar);
    long num_choice = story[currnum].choice.size();  //get number of choice

    //read from cmd
    std::cin >> n;
    // std::getline(std::cin, n);

    //if input is invalid, input again until valid
    while (!isValidChoice(n, num_choice)) {
      std::cout << "That is not a valid choice, please try again\n";
      //std::getline(std::cin, n);
      std::cin >> n;
    }

    long temp = convert(n);
    //check if <UNAVAILABLE>
    while (!story[currnum].choice[temp - 1].available) {
      std::cout << "That choice is not available at this time, please try again\n";
      // std::getline(std::cin, n);
      std::cin >> n;
      //if input is invalid, input again until valid
      while (!isValidChoice(n, num_choice)) {
        std::cout << "That is not a valid choice, please try again\n";
        //std::getline(std::cin, n);
        std::cin >> n;
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
//check if this choice is valid for this page
bool Pstory::isValidChoice(std::string n, long num_choice) {
  //if string is empty
  if (n.empty()) {
    return false;
  }
  //if string is not empty
  char * c = new char[n.length() + 1];
  std::strcpy(c, n.c_str());
  char * end;
  long num = std::strtol(c, &end, 10);

  //check valid of integer
  int len_end = strlen(end);
  if (*end != 0 || len_end != 0) {
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
//find all paths to win and print them
void Pstory::findWay() {
  long curr_c = 0;                           //current choice number under this page
  std::map<long, int> visit;                 //visited node number
  std::vector<std::pair<Page, long> > Path;  //current path
  std::stack<std::vector<std::pair<Page, long> > > todoPath;  //todo list of path
  std::vector<std::string> resPath;                           //result path
  std::pair<Page, long> currPage =
      std::make_pair(story[0], curr_c);  //current page we are in
  Path.push_back(currPage);
  todoPath.push(Path);
  //doing todo list until it is empty
  while (!todoPath.empty()) {
    Path = todoPath.top();
    todoPath.pop();
    currPage = Path[Path.size() - 1];
    //if find win page
    if (currPage.first.pageType == "W") {
      //convert(currPath to string)
      std::string way = toString(Path);
      resPath.push_back(way);
      //update visited vector if todopath is not empty
      visit.clear();
      if (!todoPath.empty()) {
        for (unsigned long j = 0; j < todoPath.top().size() - 1; ++j) {
          long index = todoPath.top()[j].first.pageNum;
          visit[index]++;
        }
      }
      continue;
    }
    //if it has not been visited
    if (!visit.count(currPage.first.pageNum)) {
      visit[currPage.first.pageNum]++;  //update visited
      //save its neighbers into todoPath
      for (unsigned long i = 0; i < currPage.first.choice.size(); ++i) {
        curr_c = i + 1;
        long next_p = currPage.first.choice[i].destnum;
        if (!visit.count(next_p)) {  //if its neighber is not visited
          std::pair<Page, long> tempPage = std::make_pair(story[next_p], curr_c);
          Path.push_back(tempPage);  //push neighber
          todoPath.push(Path);
          Path.pop_back();  //Backtracking
        }
      }
    }
  }
  //if resPath has not saved path, this story is unwinnable
  if (resPath.empty()) {
    std::cout << "This story is unwinnable!\n";
    return;
  }
  //else print all the paths
  printWay(resPath);
}
//convert path node to a whole path string that can be printed
std::string Pstory::toString(std::vector<std::pair<Page, long> > currPath) {
  std::string path;
  std::stringstream s1;  //using stringstream to convert string
  for (unsigned long k = 0; k < currPath.size() - 1; ++k) {
    s1 << currPath[k].first.pageNum << "(" << currPath[k + 1].second << "),";
  }
  s1 << currPath[currPath.size() - 1].first.pageNum << "(win)";
  s1 >> path;
  return path;
}
//print each string way
void Pstory::printWay(std::vector<std::string> way) {
  for (unsigned long int i = 0; i < way.size(); ++i) {
    std::cout << way[i] << std::endl;
  }
}
//copy assignment operator
Pstory & Pstory::operator=(const Pstory & rhs) {
  if (this != &rhs) {
    p_num = rhs.p_num;
    win_num = rhs.win_num;
    lose_num = rhs.lose_num;
    story = rhs.story;
  }
  return *this;
}
