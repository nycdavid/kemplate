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
  m_regex = regex("\\{\\{[a-zA-Z_\\s]*\\}\\}");
}

string Kemplate::Html(Depot data) {
  string result;
  string m_tmplCopy = m_tmpl;
  Parser prsr;
  vector<string> cells = prsr.ParseCells(m_tmplCopy);
  for(int i = 0; i < cells.size(); ++i) {
    result = interpolate(cells[i], data, m_tmplCopy);
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

string Kemplate::handlebarsToKey(string point) {
  regex k("\\{\\{\\s*([a-zA-Z_]*)\\s*\\}\\}");
  std::smatch m;
  std::regex_search(point, m, k);
  return m[1];
}
