#include "../src/parser.hpp"
#include "../catch.hpp"

TEST_CASE("Parser#FindLists") {
  SECTION("it accepts a template string and parses it for lists") {
    string tmpl = "<ul>{{#each fruits}}<li>{{do fruit}}</li>{{/each}}</ul>";
    Parser prsr;
    vector<map<string, string>> lists = prsr.ParseLists(tmpl);

    REQUIRE(lists.size() == 1);
  }

  SECTION("parses for lists and stores it's keys") {
    string tmpl = "<ul>{{#each fruits}}<li>{{do fruit}}</li>{{/each}}</ul>";
    Parser prsr;
    vector<map<string, string>> lists = prsr.ParseLists(tmpl);

    REQUIRE(lists[0]["depotKey"] == "fruits");
    REQUIRE(lists[0]["cellKey"] == "fruit");
  }

  SECTION("parses a list and returns the original list block") {
    string tmpl = "<ul>{{#each fruits}}<li>{{do fruit}}</li>{{/each}}</ul>";
    Parser prsr;
    vector<map<string, string>> lists = prsr.ParseLists(tmpl);

    REQUIRE(lists[0]["listBlock"] == "{{#each fruits}}<li>{{do fruit}}</li>{{/each}}");
  }

  SECTION("it parses multiple lists in a template string") {
    string tmpl = "<div><ul>{{#each fruits}}<li>{{do fruit}}</li>{{/each}}</ul></div><div><ul>{{#each fruits}}<li>{{do fruit}}</li>{{/each}}</ul></div>";
    Parser prsr;
    vector<map<string, string>> lists = prsr.ParseLists(tmpl);

    REQUIRE(lists.size() == 2);
  }

  SECTION("it parses multiple lists when there are data strings also present") {
    string tmpl = "<div><h1>{{pet_name}}</h1><ul>{{#each fruits}}<li>{{do fruit}}</li>{{/each}}</ul></div><div><ul>{{#each fruits}}<li>{{do fruit}}</li>{{/each}}</ul></div>";
    Parser prsr;
    vector<map<string, string>> lists = prsr.ParseLists(tmpl);

    REQUIRE(lists.size() == 2);
  }

  SECTION("it ignores a list that's missing the do keyword") {
    string tmpl = "<div><h1>{{pet_name}}</h1><ul>{{#each fruits}}<li>{{fruit}}</li>{{/each}}</ul></div><div><ul>{{#each fruits}}<li>{{do fruit}}</li>{{/each}}</ul></div>";
    Parser prsr;
    vector<map<string, string>> lists = prsr.ParseLists(tmpl);

    REQUIRE(lists.size() == 1);
  }
}

TEST_CASE("Parser#FindCells") {
  SECTION("it accepts a template string and parses it for a list") {
    string tmpl = "<h1>{{pet_name}}</h1>";
    Parser prsr;
    vector<string> cells = prsr.ParseCells(tmpl);

    REQUIRE(cells.size() == 1);
  }

  SECTION("it parses multiple cells in a template string") {
    string tmpl = "<h1>{{pet_name}}</h1><div>{{some_other_name}}</div>";
    Parser prsr;
    vector<string> cells = prsr.ParseCells(tmpl);

    REQUIRE(cells.size() == 2);
  }

  SECTION("it parses multiple cells from a mixed template string") {
    string tmpl = "<h1>{{pet_name}}</h1><div>{{some_other_name}}</div><div><ul>{{#each fruits}}<li>{{do fruit}}</li>{{/each}}</ul></div>";
    Parser prsr;
    vector<string> cells = prsr.ParseCells(tmpl);

    REQUIRE(cells.size() == 2);
  }

  SECTION("it parses cell keys with whitespace between the brace and string") {
    string tmpl = "<h1>{{   pet_name }}</h1><div>{{some_other_name}}</div>";
    Parser prsr;
    vector<string> cells = prsr.ParseCells(tmpl);

    REQUIRE(cells.size() == 2);
  }

  SECTION("it ignores cell keys that have whitespace in them") {
    string tmpl = "<h1>{{pet name}}</h1><div>{{some_other_name}}</div>";
    Parser prsr;
    vector<string> cells = prsr.ParseCells(tmpl);

    REQUIRE(cells.size() == 1);
    REQUIRE(cells[0] == "{{some_other_name}}");
  }
}
