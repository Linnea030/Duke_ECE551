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

  //input: ifstream of file, return void
  //process story in step 1 2 3
  void proStory_1(std::ifstream & ifs);

  //input: ifstream of file, return void
  //process story in step 4
  void proStory_2(std::ifstream & ifs);

  //input: line in story.txt, return void
  //process Page type
  void proPage(std::string line);

  //input: line in story.txt, return void
  //process choice type
  void proChoice(std::string line);

  //input: line in story.txt, return void
  //process Page with variable
  void proPagevar(std::string line);

  //input: line in story.txt, return void
  //process choice with variable
  void proChoicevar(std::string line);

  //input: path of the file, return void
  //print whole pages in step1
  void print(std::string path) const;

  //input: path of the file and page number i, return void
  //print single page in step2 3
  void print_single(std::string path, int i) const;

  //input: path of the file and page number i and storyVar of variable, return void
  //print single page with variable in step4
  void print_single1(std::string path,
                     int i,
                     std::vector<std::pair<long int, std::string> > storyVar);

  //input: num(pagenumber) and p_num(total number of the story),return void
  //check if this destpage is existed
  void checkPage(long num, long p_num) const;

  //input: line in story.txt, return true for is page, false for not
  //check if line is page line
  bool isPage(std::string line) const;

  //input: line in story.txt
  //check if line is choice line, return true for is choice, false for not
  bool isChoice(std::string line) const;

  //input: line in story.txt
  //check if line is page variable line, return true for is pagevar, false for not
  bool isPagevar(std::string line) const;

  //input: line in story.txt, return true for is choicevar, false for not
  //check if line is choice variable line
  bool isChoicevar(std::string line) const;

  //input: string s, return number of type long
  //convert string to integer and check if it is valid
  long convert(std::string s);

  //input: string s, return number of type long
  //convert string to integer and check if it is valid, but it can be negative in step4
  long convert1(std::string s);

  //input: line in story.txt, return true for is blank line, false for not
  //check if the line only contains blackspace and new line
  bool isSpacel(std::string line) const;

  //input: string s, return void
  //save number of win pages and number of lose pages
  //used it to check if there exist at least 1 win and 1 lose page
  void check_wl(std::string s2);

  //input: string path of the files, return void
  //check valid conditions for step2 3 4
  void checkValid(std::string path) const;

  //input: nothing, return void
  //check if cin is end
  void isEndCin();

  //input: string path of the files, return void
  //begingame for step1 2 3,start the game for user
  void beginGame(std::string path);

  //input: string path of the files, return void
  //begingame for step4,start the game for user
  void beginGame_plus(std::string path);

  //input: variable name string s, vector storyVar used to save set variable
  //return index of variable in vector
  //help to check if variable has been set in this game
  int isInVector(std::string s, std::vector<std::pair<long int, std::string> > storyVar);
  //input: string n for input and num_choice for the number of choices in this page
  //return true for valid, false for not
  //check if this choice is valid for this page
  bool isValidChoice(std::string n, long num_choice) const;

  //input:string s, return bool
  //check if string s is a number,true for is, false for is not
  bool isNumber(std::string s) const;

  //input:nothing, return void
  //find all paths to win and print them
  void findWay();

  //input: vector of pair named currPath,return a string of path in step3
  //convert path node to a whole path string that can be printed
  std::string toString(std::vector<std::pair<Page, long> > currPath);

  //input: vector of string named way which saved all paths to win, return void
  //print each string way
  void printWay(std::vector<std::string> way);

  //destructor
  ~Pstory() {}
};
