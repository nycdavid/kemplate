#include <iostream>
#include "depot.hpp"

// Public
void Depot::Store(string key, string value) {
  cleanseKey(key);
  m_strings[key] = value;
}

void Depot::Store(string key, vector<string> value) {
  cleanseKey(key);
  m_lists[key] = value;
}

boost::any Depot::Fetch(string key) {
  if (existsInStrings(key)) {
    return m_strings[key];
  } else if (existsInLists(key)) {
    return m_lists[key];
  }
  return std::string{""};
}

// Private
bool Depot::existsInStrings(string key) {
  return m_strings.find(key) != m_strings.end();
}

bool Depot::existsInLists(string key) {
  return m_lists.find(key) != m_lists.end();
}

void Depot::cleanseKey(string key) {
  m_strings.erase(key);
  m_lists.erase(key);
}
