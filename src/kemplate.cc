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
  m_tmpl = tmpl;
  m_regex = regex("\\{\\{[a-zA-Z_]*\\}\\}");
}

string Kemplate::Html(map<string, string> data) {
  string result;
  string m_tmplCopy = m_tmpl;
  sregex_iterator begin = regexDataPoints();
  for (sregex_iterator i = begin; i != sregex_iterator(); ++i) {
    std::smatch match = *i;
    string key = handlebarsToKey(match.str());
    result = interpolate(key, data[key], m_tmplCopy);
  }
  return result;
}

string Kemplate::GetTemplate() {
  return m_tmpl;
}

string Kemplate::interpolate(string key, string value, string &pTmpl) {
  string barsKey = "{{" + key + "}}";
  std::size_t foundPos = pTmpl.find(barsKey);
  pTmpl.replace(foundPos, barsKey.size(), value);
  return pTmpl;
}

string Kemplate::handlebarsToKey(string point) {
  regex k("\\{\\{([a-zA-Z_]*)\\}\\}");
  std::smatch m;
  std::regex_search(point, m, k);
  return m[1];
}

sregex_iterator Kemplate::regexDataPoints() {
  return sregex_iterator(m_tmpl.begin(), m_tmpl.end(), m_regex);
}
