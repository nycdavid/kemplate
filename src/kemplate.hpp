#include <map>
#include <regex>
#include <iostream>

#include "depot.hpp"

using std::map;
using std::regex;
using std::sregex_iterator;
using std::string;
using std::vector;

#ifndef KEMPLATE_H
#define KEMPLATE_H
class Kemplate {
  public:
    Kemplate(string htmlTemplate = "");
    string Html(Depot data);
    string GetTemplate();
  private:
    string m_tmpl;
    regex m_regex;
    string interpolate(string barsKey, Depot data, string &pTmpl);
    string handlebarsToKey(string point);
    sregex_iterator regexDataPoints();
};
#endif
