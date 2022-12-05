#include "choice.hpp"
void Choice::print_c() {
  std::cout << " " << cnum << ". " << text;
  std::cout << "\n";
}

void Choice::print_var() {
  std::cout << " " << cnum << ". <UNAVAILABLE>";
  std::cout << "\n";
}
