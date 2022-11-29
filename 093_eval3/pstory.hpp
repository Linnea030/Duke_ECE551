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
  bool isValidChoice(std::string n, long num_choice);
  void findWay();
  bool isContained(const std::vector<long> & visited, const long & pageNum);
  std::string toString(std::vector<std::pair<Page, long> > currPath);
  void printWay(std::vector<std::string> way);
  //  bool isContained(std::vector<Page> const & visited, Page const & currPage);
  //  bool operator==(const Page & rhs);
  //  bool operator!=(const Page & rhs);
  // ~Pstory() {}
};
