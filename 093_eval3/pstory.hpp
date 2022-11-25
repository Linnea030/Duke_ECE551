#include "choice.hpp"
#include "page.hpp"
class Pstory {
 public:
  long p_num;
  std::vector<Page> story;

  Pstory() : p_num(-1) {}
  void proStory(std::ifstream & ifs);
  void print(std::string path);
  void checkPage(long num, long p_num);
  bool isPage(std::string line);
  bool isChoice(std::string line);
  long convert(std::string s);
  bool isSpacel(std::string line);
};
