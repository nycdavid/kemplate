#include <map>
#include <regex>
#include <iostream>

using std::map;
using std::regex;
using std::sregex_iterator;
using std::string;

#ifndef KEMPLATE_H
#define KEMPLATE_H
class Kemplate {
  public:
    Kemplate(string htmlTemplate = "");
    string Html(map<string, string> data);
    string GetTemplate();
  private:
    string m_tmpl;
    regex m_regex;
    string interpolate(string barsKey, map<string, string> data, string &pTmpl);
    string handlebarsToKey(string point);
    sregex_iterator regexDataPoints();
};
#endif
