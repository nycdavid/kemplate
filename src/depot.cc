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
  } else {
    return m_lists[key];
  }
}

// Private
bool Depot::existsInStrings(string key) {
  return m_strings.find(key) != m_strings.end();
}

void Depot::cleanseKey(string key) {
  m_strings.erase(key);
  m_lists.erase(key);
}
