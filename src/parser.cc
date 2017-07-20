#include "parser.hpp"

// Public
Parser::Parser() {
  m_listRegex = regex("\\{\\{#each\\s+[a-zA-Z_]*\\}\\}[a-zA-Z\\/<>]+\\{\\{do [a-zA-Z_]+\\}\\}[a-zA-Z\\/<>]+\\{\\{\\/each\\}\\}");
  m_cellRegex = regex("\\{\\{\\s*[a-zA-Z_]*\\s*\\}\\}");
}

vector<string> Parser::ParseLists(string tmpl) {
  return parseAndStore(tmpl, m_listRegex);
}

vector<string> Parser::ParseCells(string tmpl) {
  return parseAndStore(tmpl, m_cellRegex);
}

// Private
vector<string> Parser::parseAndStore(string tmpl, regex rgx) {
  vector<string> items;
  sregex_iterator begin = sregex_iterator(tmpl.begin(), tmpl.end(), rgx);
  for (sregex_iterator i = begin; i != sregex_iterator(); ++i) {
    std::smatch match = *i;
    items.push_back(match.str());
  }
  return items;
}
