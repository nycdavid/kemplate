#include <iostream>
#include <map>
#include <vector>

#include "../vendor/boost/any.hpp"

using std::string;
using std::map;
using std::vector;

#ifndef DEPOT_H
#define DEPOT_H
class Depot {
  public:
    void Store(string key, string value);
    void Store(string key, vector<string> value);
    boost::any Fetch(string key);
  private:
    map<string, string> m_strings;
    map<string, vector<string>> m_lists;
    bool existsInStrings(string key);
    void cleanseKey(string key);
};
#endif
