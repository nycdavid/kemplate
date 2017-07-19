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
    string HtmlForLists(Depot data);
    string GetTemplate();
  private:
    string m_tmpl;
    regex m_regex;
    regex m_listRegex;
    string interpolate(string barsKey, Depot data, string &pTmpl);
    string interpolateList(string capturedMarkup, Depot data, string &pTmpl);
    string handlebarsToKey(string point);
    sregex_iterator parseForKeys();
    sregex_iterator parseForKeysThatAreLists();
};
#endif
