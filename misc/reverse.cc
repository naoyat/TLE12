#include <iostream>
#include <vector>
using namespace std;

main() {
  char buf[2000];

  vector<string> lines;
  while(gets(buf)) {
    lines.push_back(buf);
  }
  for(int i=lines.size()-1; i>=0; --i) {
    cout << lines[i] << endl;
  }
}
