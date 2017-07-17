#include "../src/depot.hpp"
#include "../catch.hpp"

TEST_CASE("Depot#Store - string, string", "calling Depot#Store(string key, string value)") {
  SECTION("stores a value in an internal <string, string> map") {
    Depot dpt;
    dpt.Store("name", "David");
    string fetched = boost::any_cast<string>(dpt.Fetch("name"));

    REQUIRE(fetched == "David");
  }
}

TEST_CASE("Depot#Store - string, vector<string>", "calling Depot#Store(string key, vector<string> value)") {
  SECTION("stores a value in an internal <string, vector<string>> map") {
    Depot dpt;
    vector<string> hobbies = { "Music Production", "Programming", "Reading" };
    dpt.Store("hobbies", hobbies);
    vector<string> fetched = boost::any_cast<vector<string>>(dpt.Fetch("hobbies"));

    REQUIRE(fetched.size() == 3);
  }
}

TEST_CASE("Depot#Store - edge cases", "overwrites the key if it exists") {
  SECTION("value stored is the same type as the original") {
    Depot dpt;
    dpt.Store("name", "David");
    dpt.Store("name", "Dave");
    string fetched = boost::any_cast<string>(dpt.Fetch("name"));

    REQUIRE(fetched == "Dave");
  }

  SECTION("key is stored as string then vector") {
    Depot dpt;
    dpt.Store("some_key", "David");
    vector<string> hobbies = { "Music Production", "Programming", "Reading" };
    dpt.Store("some_key", hobbies);
    vector<string> fetched = boost::any_cast<vector<string>>(dpt.Fetch("some_key"));

    REQUIRE(fetched.size() == 3);
  }

  SECTION("key is stored as vector then string") {
    Depot dpt;
    vector<string> hobbies = { "Music Production", "Programming", "Reading" };
    dpt.Store("some_key", hobbies);
    dpt.Store("some_key", "David");
    string fetched = boost::any_cast<string>(dpt.Fetch("some_key"));

    REQUIRE(fetched == "David");
  }
}
