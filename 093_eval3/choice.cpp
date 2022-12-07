#include "choice.hpp"
//input Choice object rhs, return Choice object *this
//copy constructor
Choice & Choice::operator=(const Choice & rhs) {
  if (this != &rhs) {
    pagenum = rhs.pagenum;
    destnum = rhs.destnum;
    text = rhs.text;
    cnum = rhs.cnum;
    needVar = rhs.needVar;
    available = rhs.available;
    choiceVar = rhs.choiceVar;
  }
  return *this;
}
//input nothing, return nothing
//print choice text in step 1 2 3
void Choice::print_c() {
  std::cout << " " << cnum << ". " << text;
  std::cout << "\n";
  return;
}
//input nothing, return nothing
//print choice text in step 4
void Choice::print_var() {
  std::cout << " " << cnum << ". <UNAVAILABLE>";
  std::cout << "\n";
  return;
}
