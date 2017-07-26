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
  string result;
  string m_tmplCopy = m_tmpl;
  Parser prsr;
  vector<string> cells = prsr.ParseCells(m_tmplCopy);
  for(int i = 0; i < cells.size(); ++i) {
    result = interpolate(cells[i], m_tmplCopy);
  }
  return result;
}

string Kemplate::GetTemplate() {
  return m_tmpl;
}

Depot* Kemplate::GetDepot() {
  return &m_depot;
}

string Kemplate::interpolate(string barsKey, string &pTmpl) {
  string strippedKey = handlebarsToKey(barsKey);
  string value = boost::any_cast<string>(m_depot.Fetch(strippedKey));
  std::size_t foundPos = pTmpl.find(barsKey);
  pTmpl.replace(foundPos, barsKey.size(), value);
  return pTmpl;
}

string Kemplate::handlebarsToKey(string point) {
  regex k("\\{\\{\\s*([a-zA-Z_]*)\\s*\\}\\}");
  std::smatch m;
  std::regex_search(point, m, k);
  return m[1];
}
