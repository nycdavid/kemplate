#include <iostream>
#include <vector>
#include <string>
#include <map>

using std::string;
using std::map;
using std::vector;

vector<string> getKeys(map<string, string> data);
string kemplatify(string tmpl, map<string, string> data);

int main() {
  string tmpl = "<html><body><p>Hi, there! My name is {{name}}</p><p>My favorite hobby is {{favorite_hobby}}</p><p>{{favorite_hobby}} is something I enjoy because.</p></body></html>";
  map<string, string> foo;
  foo.insert(std::pair<string, string>("name", "David"));
  foo.insert(std::pair<string, string>("favorite_hobby", "music production"));
  kemplatify(tmpl, foo);
  std::cout << tmpl << std::endl;
  return 0;
}

vector<string> getKeys(map<string, string> data) {
  vector<string> keys;
  map<string, string>::const_iterator iter;
  for(iter = data.begin(); iter != data.end(); iter++) {
    keys.push_back(iter->first);
  }
  return keys;
}

string kemplatify(string tmpl, map<string, string> data) {
  vector<string> keys = getKeys(data);
  for(int i = 0; i < keys.size(); i++) {
    string token = "{{" + keys[i] + "}}";
    int idx = tmpl.find(token);
    tmpl.replace(idx, keys[i].length()+4, data[keys[i]]);
  }
  std::cout << "Template is now: " << tmpl << std::endl;
}
