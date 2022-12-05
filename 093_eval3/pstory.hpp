#include "choice.hpp"
#include "page.hpp"
class Pstory {
 public:
  long p_num;
  long win_num;
  long lose_num;
  std::vector<Page> story;

  Pstory() : p_num(-1), win_num(0), lose_num(0) {}
  void proStory(std::ifstream & ifs);
  void proStory_1(std::ifstream & ifs);
  void proPage(std::string line);
  void proChoice(std::string line);
  void print(std::string path);
  void print_single(std::string path, int i);
  void checkPage(long num, long p_num);
  bool isPage(std::string line);
  bool isChoice(std::string line);
  long convert(std::string s);
  bool isSpacel(std::string line);
  void check_wl(std::string s2);
  void checkValid();
  void beginGame(std::string path);
  void beginGame_plus(std::string path);
  bool isValidChoice(std::string n, long num_choice);
  void findWay();
  std::string toString(std::vector<std::pair<Page, long> > currPath);
  void printWay(std::vector<std::string> way);
};
