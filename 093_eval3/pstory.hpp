#include "choice.hpp"
#include "page.hpp"
class Pstory {
 public:
  long p_num;               //the number of pages -1 in this story
  long win_num;             //the number of win pages in this story
  long lose_num;            //the number of lose pages in this story
  std::vector<Page> story;  //vector of each Page object
  //constructor
  Pstory() : p_num(-1), win_num(0), lose_num(0) {}
  //copy constructor
  Pstory(const Pstory & rhs) :
      p_num(rhs.p_num), win_num(rhs.win_num), lose_num(rhs.lose_num), story(rhs.story) {}
  //copy assignment operator
  Pstory & operator=(const Pstory & rhs);
  //process story in step 1 2 3
  void proStory_1(std::ifstream & ifs);
  //process story in step 4
  void proStory_2(std::ifstream & ifs);
  //process Page type
  void proPage(std::string line);
  //process choice type
  void proChoice(std::string line);
  //process Page with variable
  void proPagevar(std::string line);
  //process choice with variable
  void proChoicevar(std::string line);
  //print whole pages in step1
  void print(std::string path);
  //print single page in step2 3
  void print_single(std::string path, int i);
  //print single page with variable in step4
  void print_single1(std::string path,
                     int i,
                     std::vector<std::pair<long int, std::string> > storyVar);
  void checkPage(long num, long p_num);
  bool isPage(std::string line);
  bool isChoice(std::string line);
  bool isPagevar(std::string line);
  bool isChoicevar(std::string line);
  long convert(std::string s);
  bool isSpacel(std::string line);
  void check_wl(std::string s2);
  void checkValid();
  void beginGame(std::string path);
  void beginGame_plus(std::string path);
  bool isValidChoice(std::string n, long num_choice);
  bool isNumber(std::string s);
  void findWay();
  std::string toString(std::vector<std::pair<Page, long> > currPath);
  void printWay(std::vector<std::string> way);
  //destructor
  ~Pstory() {}
};
