#include "choice.hpp"
class Page {
 public:
  size_t pageNum;
  std::vector<std::pair<long int, std::string> > var;
  std::string pageType;
  std::string fileName;
  std::vector<Choice> choice;

  Page(size_t pn, std::string pt, std::string fn) :
      pageNum(pn), pageType(pt), fileName(fn) {}
  //print this page in step1 2 3
  void print_p(std::string path, int step);
  //print this page's text, subfunction of print_p and print_p1
  void textPrint(std::string path);
  //print this page with variable in step4
  void print_p1(std::string path,
                std::vector<std::pair<long int, std::string> > storyVar);
  bool operator==(const Page & rhs);
  bool operator!=(const Page & rhs);
};
