#include <iostream>
#include "parser.hpp"

// Public
Parser::Parser() {
  m_listRegex = regex("\\{\\{#each\\s+[a-zA-Z_]*\\}\\}[a-zA-Z\\/<>]+\\{\\{do [a-zA-Z_]+\\}\\}[a-zA-Z\\/<>]+\\{\\{\\/each\\}\\}");
  m_listPartsRegex = regex("\\{\\{#each\\s+([a-zA-Z_]+)\\}\\}(.*(\\{\\{do [a-zA-Z_]+\\}\\}).*)\\{\\{\\/each\\}\\}");
  m_cellRegex = regex("\\{\\{\\s*[a-zA-Z_]*\\s*\\}\\}");
}

vector<map<string, string>> Parser::ParseLists(string tmpl) {
  vector<map<string, string>> lists;
  vector<string> listBlocks = parseAndStore(tmpl, m_listRegex);
  for (int i = 0; i < listBlocks.size(); ++i) {
    lists.push_back(parseListForInfo(listBlocks[i]));
  }
  return lists;
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

map<string, string> Parser::parseListForInfo(string listBlock) {
  std::smatch matches;
  std::regex_search(listBlock, matches, m_listPartsRegex);
  map<string, string> info = {
    {"listBlock", listBlock},
    {"depotKey", matches[1]},
    {"blockBody", matches[2]},
    {"doElement", matches[3]}
  };
  return info;
}
