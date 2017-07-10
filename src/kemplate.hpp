#include <map>
#include <iostream>
using std::string;
using std::map;

#ifndef KEMPLATE_H
#define KEMPLATE_H
class Kemplate {
  public:
    Kemplate(string htmlTemplate = "");
    string Html(map<string, string> data);
    string GetTemplate();
  private:
    string m_tmpl;
    string interpolate(string key, string value, int length, string &pTmpl);
};
#endif
