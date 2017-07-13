#include "../src/kemplate.hpp"
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

TEST_CASE("Kemplate#Html", "calling k.Html(map<string, string> data)") {
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

  SECTION("allows for keys in the data object that are not used") {
    map<string, string> data;
    data["name"] = "David Ko";
    data["job"] = "Software Engineer";
    data["foo"] = "bar";
    string tmpl = "<html>{{name}}: {{job}}</html>";
    Kemplate k(tmpl);

    REQUIRE(k.Html(data) == "<html>David Ko: Software Engineer</html>");
  }

  SECTION("interpolates empty space for a key that does not exist in the data object") {
    map<string, string> data;
    data["name"] = "David Ko";
    data["job"] = "Software Engineer";
    string tmpl = "<html>{{name}}: {{job}}<p>{{foo}}</p></html>";
    Kemplate k(tmpl);

    REQUIRE(k.Html(data) == "<html>David Ko: Software Engineer<p></p></html>");
  }

  SECTION("interpolates a Handlebars datapoint with whitespace between the key and the brace") {
    map<string, string> data;
    data["name"] = "David Ko";
    data["job"] = "Software Engineer";
    string tmpl = "<html>{{ name}}: {{job }}<p>{{foo  }}</p></html>";
    Kemplate k(tmpl);

    REQUIRE(k.Html(data) == "<html>David Ko: Software Engineer<p></p></html>");
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
