#include <regex>
#include <vector>

using std::string;
using std::vector;
using std::regex;
using std::sregex_iterator;

#ifndef PARSER_H
#define PARSER_H
class Parser {
  public:
    Parser();
    vector<string> ParseLists(string tmpl);
    vector<string> ParseCells(string tmpl);
  private:
    vector<string> parseAndStore(string tmpl, regex rgx);
    regex m_listRegex;
    regex m_cellRegex;
};
#endif
