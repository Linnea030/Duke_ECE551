#include "choice.hpp"
class Page {
 public:
  size_t pageNum;              //page number of this page
  std::string pageType;        //page type of this page: N W L
  std::string fileName;        //file name of this page text
  std::vector<Choice> choice;  //the choice objects of this page
  //variable used in step 4
  std::vector<std::pair<long int, std::string> > var;  //variables set in this page

  //constructor
  Page(size_t pn, std::string pt, std::string fn) :
      pageNum(pn), pageType(pt), fileName(fn) {}

  //copy constructor
  Page(const Page & rhs) :
      pageNum(rhs.pageNum),
      pageType(rhs.pageType),
      fileName(rhs.fileName),
      choice(rhs.choice),
      var(rhs.var) {}

  //copy assignment operator
  Page & operator=(const Page & rhs);

  //input string path of the pagefile.txt and which step it is in now
  //return is void
  //print this page in step1 2
  void print_p(std::string path, int step) const;

  //input string path of the pagefile.txt
  //return is void
  //print this page's text, subfunction of print_p and print_p1
  void textPrint(std::string path) const;

  //input string path of the pagefile.txt and vector storyVar which save the variables
  //return void, variable is checked by storyVar (save all variables for now) and choice
  //print this page with variable in step4
  void print_p1(std::string path,
                std::vector<std::pair<long int, std::string> > storyVar);
  //input: vector storyVar which save the variables, return void
  //print and check variables in choice for step 4
  void print_step4(std::vector<std::pair<long int, std::string> > storyVar);

  //destructor
  ~Page() {}
};
