#include <iostream>
#include <string>
#include <map>

using std::string;
using std::map;

string kemplatify(string tmpl, map<string, string> data) {
  std::cout << "The value at key \"name\" is: " << data["name"] << std::endl;
}

int main() {
  string tmpl = "<html><body><p>Hi, there! My name is {{name}}</p></body></html>";
  map<string, string> foo;
  foo.insert(std::pair<string, string>("name", "David"));
  string kemplate = kemplatify(tmpl, foo);

  std::cout << tmpl << std::endl;
  return 0;
}
