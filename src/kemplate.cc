#include <iostream>
#include <map>
#include <regex>
#include "kemplate.hpp"
#include "parser.hpp"

using std::cout;
using std::endl;
using std::map;
using std::regex;
using std::sregex_iterator;
using std::string;

// Constructor
Kemplate::Kemplate(string tmpl) {
  m_tmpl = tmpl;
}

string Kemplate::Html(Depot data) {
  string result;
  Parser prsr;
  vector<string> cells = prsr.ParseCells(m_tmpl);
  vector<map<string, string>> lists = prsr.ParseLists(m_tmpl);
  for(int i = 0; i < cells.size(); ++i) {
    result = interpolate(cells[i], data, m_tmpl);
  }
  for(int i = 0; i < lists.size(); ++i) {
    result = interpolateList(lists[i], data, result);
  }
  return result;
}

string Kemplate::GetTemplate() {
  return m_tmpl;
}

string Kemplate::interpolate(string barsKey, Depot data, string &pTmpl) {
  string strippedKey = handlebarsToKey(barsKey);
  string value = boost::any_cast<string>(data.Fetch(strippedKey));
  std::size_t foundPos = pTmpl.find(barsKey);
  pTmpl.replace(foundPos, barsKey.size(), value);
  return pTmpl;
}

string Kemplate::interpolateList(map<string, string> listObj, Depot data, string &pTmpl) {
  // cout << listObj["depotKey"] << endl;
  vector<string> listItems = boost::any_cast<vector<string>>(data.Fetch(listObj["depotKey"]));
  return "foo";
}

string Kemplate::handlebarsToKey(string point) {
  regex k("\\{\\{\\s*([a-zA-Z_]*)\\s*\\}\\}");
  std::smatch m;
  std::regex_search(point, m, k);
  return m[1];
}
