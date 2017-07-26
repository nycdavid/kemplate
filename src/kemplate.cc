#include <iostream>
#include <map>
#include <regex>
#include "kemplate.hpp"

using std::cout;
using std::endl;
using std::map;
using std::regex;
using std::sregex_iterator;
using std::string;

// Constructor
Kemplate::Kemplate(string tmpl) {
  Depot m_depot;
  m_tmpl = tmpl;
  m_regex = regex("\\{\\{[a-zA-Z_\\s]*\\}\\}");
}

string Kemplate::Html() {
  string result = m_tmpl;
  Parser prsr;
  vector<string> cells = prsr.ParseCells(m_tmpl);
  vector<map<string, string>> lists = prsr.ParseLists(m_tmpl);
  for(int i = 0; i < cells.size(); ++i) {
    string strippedKey = handlebarsToKey(cells[i]);
    string value = boost::any_cast<string>(m_depot.Fetch(strippedKey));
    result = interpolate(cells[i], value, result);
  }
  for(int i = 0; i < lists.size(); ++i) {
    result = interpolateList(lists[i], result);
  }
  return result;
}

string Kemplate::GetTemplate() {
  return m_tmpl;
}

Depot* Kemplate::GetDepot() {
  return &m_depot;
}

string Kemplate::interpolate(string handlebarsKey, string value, string &pTmpl) {
  std::size_t foundPos = pTmpl.find(handlebarsKey);
  pTmpl.replace(foundPos, handlebarsKey.size(), value);
  return pTmpl;
}

string Kemplate::interpolateList(map<string, string> listObj, string &pTmpl) {
  string replacementStr;
  string listBlock = listObj["listBlock"];
  vector<string> items = boost::any_cast<vector<string>>(m_depot.Fetch(listObj["depotKey"]));
  for (int i = 0; i < items.size(); ++i) {
    string blockBody = listObj["blockBody"];
    string appendStr = interpolate(listObj["doElement"], items[i], blockBody);
    replacementStr.append(appendStr);
  }
  std::size_t foundPos = pTmpl.find(listBlock);
  pTmpl.replace(foundPos, listBlock.size(), replacementStr);
  return pTmpl;
}

string Kemplate::handlebarsToKey(string point) {
  regex k("\\{\\{\\s*([a-zA-Z_]*)\\s*\\}\\}");
  std::smatch m;
  std::regex_search(point, m, k);
  return m[1];
}
