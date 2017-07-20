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
  m_listRegex = regex("\\{\\{#each\\s+[a-zA-Z_]*\\}\\}.*?\\{\\{\\/each\\}\\}");
}

string Kemplate::Html(Depot data) {
  string result;
  string m_tmplCopy = m_tmpl;
<<<<<<< 744d5e59d985457601a8f0a39aeb7c4254b21638
  Parser prsr;
  vector<string> cells = prsr.ParseCells(m_tmplCopy);
  for(int i = 0; i < cells.size(); ++i) {
    result = interpolate(cells[i], data, m_tmplCopy);
=======
  sregex_iterator begin = parseForKeys();
  for (sregex_iterator i = begin; i != sregex_iterator(); ++i) {
    std::smatch match = *i;
    string barsKey = match.str();
    result = interpolate(barsKey, data, m_tmplCopy);
>>>>>>> Break out methods into different paths
  }
  return result;
}

string Kemplate::HtmlForLists(Depot data) { // TODO: Duplicate code
  string result;
  string m_tmplCopy = m_tmpl;
  sregex_iterator begin = parseForKeysThatAreLists();
  for (sregex_iterator i = begin; i != sregex_iterator(); ++i) {
    std::smatch match = *i;
    result = interpolateList(match.str(), data, m_tmplCopy);
  }
  return result;
}

string Kemplate::interpolateList(string capturedMarkup, Depot data, string &pTmpl) {
  regex iteratedTag("\\{\\{#each\\s+(.*)\\}\\}<([a-zA-Z\\d]*)>\\{\\{.*\\}\\}<\\/[a-zA-Z\\d]*>\\{\\{\\/each\\}\\}");
  string itemsTmpl;
  std::smatch m;
  std::regex_search(capturedMarkup, m, iteratedTag);
  string dataKey = m[1];
  std::size_t foundPos = pTmpl.find(capturedMarkup);
  vector<string> items = boost::any_cast<vector<string>>(data.Fetch(dataKey)); // TODO key is hard-coded
  for(int i = 0; i != items.size(); ++i) {
    string tag;
    tag.append("<");
    tag.append(m[2]);
    tag.append(">");
    tag.append(items[i]);
    tag.append("</");
    tag.append(m[2]);
    tag.append(">");
    itemsTmpl.append(tag);
  }

  pTmpl.replace(foundPos, capturedMarkup.size(), itemsTmpl);
  return pTmpl;
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
<<<<<<< 744d5e59d985457601a8f0a39aeb7c4254b21638
=======

sregex_iterator Kemplate::parseForKeys() {
  return sregex_iterator(m_tmpl.begin(), m_tmpl.end(), m_regex);
}

sregex_iterator Kemplate::parseForKeysThatAreLists() {
  return sregex_iterator(m_tmpl.begin(), m_tmpl.end(), m_listRegex);
}
>>>>>>> Break out methods into different paths
