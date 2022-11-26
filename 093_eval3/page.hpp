#include "choice.hpp"
class Page {
 public:
  long pageNum;
  std::string pageType;
  std::string fileName;
  std::vector<Choice> choice;

  Page(long pn, std::string pt, std::string fn) :
      pageNum(pn), pageType(pt), fileName(fn) {}

  void print_p(std::string path, int step);
};
