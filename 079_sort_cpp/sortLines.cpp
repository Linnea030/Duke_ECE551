#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char ** argv) {
  if (argc < 1) {
    exit(EXIT_FAILURE);
  }

  string line;
  vector<string> ans;
  if (argc > 1) {
    //read from command line
    for (int i = 1; i < argc; i++) {
      ifstream read(argv[i]);
      int x = read.fail();
      if (x) {
        cerr << "Open file failed " << argv[i] << endl;
        exit(EXIT_FAILURE);
      }
      while (!read.eof()) {
        getline(read, line);
        ans.push_back(line);
      }
      sort(ans.begin(), ans.end());
      for (size_t i = 0; i < ans.size(); i++) {
        cout << ans[i] << endl;
      }
      ans.clear();
    }
  }

  else {
    while (!cin.eof()) {
      getline(cin, line);
      ans.push_back(line);
    }
    sort(ans.begin(), ans.end());
    for (size_t i = 0; i < ans.size(); i++) {
      cout << ans[i] << endl;
    }
    ans.clear();
  }
  return EXIT_SUCCESS;
}
