#include <iostream>
using std::string;

#ifndef KEMPLATE_H
#define KEMPLATE_H
class Kemplate {
  public:
    Kemplate(string htmlTemplate = "<html></html>");
    string HtmlTemplate();
  private:
    string htmlTemplate;
};
#endif
