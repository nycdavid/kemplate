#include <iostream>
#include <map>
#include "kemplate.hpp"

using std::string;
using std::map;
using std::cout;
using std::endl;

// Constructor
Kemplate::Kemplate(string tmpl) {
  m_tmpl = tmpl;
}

string Kemplate::Html(map<string, string> data) {
  string result;
  string m_tmplCopy = m_tmpl;
  for (auto iter = data.begin(); iter != data.end(); iter++) {
    string key = "{{" + iter->first + "}}";
    string value = iter->second;
    int length = key.length();
    result = interpolate(key, value, length, m_tmplCopy);
  }
  return result;
}

string Kemplate::interpolate(string key, string value, int length, string &pTmpl) {
  std::size_t foundPos = pTmpl.find(key);
  if (foundPos != string::npos) {
    pTmpl.replace(foundPos, length, value);
    return interpolate(key, value, length, pTmpl);
  } else {
    return pTmpl;
  }
}

string Kemplate::GetTemplate() {
  return m_tmpl;
}
