#include <map>
#include <regex>
#include <iostream>

#include "depot.hpp"
#include "parser.hpp"

using std::map;
using std::regex;
using std::sregex_iterator;
using std::string;

#ifndef KEMPLATE_H
#define KEMPLATE_H
class Kemplate {
  public:
    Kemplate(string htmlTemplate = "");
    string Html();
    string GetTemplate();
    Depot* GetDepot();
  private:
    Depot m_depot;
    string m_tmpl;
    regex m_regex;
    string interpolate(string handlebarsKey, string value, string &pTmpl);
    string interpolateList(map<string, string> listObj, string &pTmpl);
    string handlebarsToKey(string point);
};
#endif
