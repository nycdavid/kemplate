#include "../src/kemplate.hpp"
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

TEST_CASE("Kemplate#Html", "calling k.Html()") {
  SECTION("interpolates a single occurrence") {
    map<string, string> data;
    data["name"] = "David";
    string tmpl = "<html>{{name}}</html>";
    Kemplate k(tmpl);

    REQUIRE(k.Html(data) == "<html>David</html>");
  }

  SECTION("interpolates multiple occurrences") {
    map<string, string> data;
    data["name"] = "David";
    string tmpl = "<html>{{name}}.{{name}}</html>";
    Kemplate k(tmpl);

    REQUIRE(k.Html(data) == "<html>David.David</html>");
  }

  SECTION("interpolates different keys") {
    map<string, string> data;
    data["name"] = "David Ko";
    data["job"] = "Software Engineer";
    string tmpl = "<html>{{name}}: {{job}}</html>";
    Kemplate k(tmpl);

    REQUIRE(k.Html(data) == "<html>David Ko: Software Engineer</html>");
  }
}

TEST_CASE("Kemplate#GetTemplate", "calling k.GetTemplate()") {
  SECTION("returns a template string in it's pre-interpolated state") {
    map<string, string> data;
    data["name"] = "David Ko";
    data["job"] = "Software Engineer";
    string tmpl = "<html>{{name}}: {{job}}</html>";
    Kemplate k(tmpl);

    REQUIRE(k.GetTemplate() == "<html>{{name}}: {{job}}</html>");
  }
}
