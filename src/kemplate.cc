#include <iostream>
#include "kemplate.hpp"

using std::string;

Kemplate::Kemplate(string htmlStr) {
  htmlTemplate = htmlStr;
}

string Kemplate::HtmlTemplate() {
  return htmlTemplate;
}
