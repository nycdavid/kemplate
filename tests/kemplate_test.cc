#include "../src/kemplate.hpp"
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

TEST_CASE("Kemplate#Html", "calling k.Html(map<string, string> data)") {
  SECTION("interpolates a single occurrence") {
    string tmpl = "<html>{{name}}</html>";
    Kemplate k(tmpl);
    Depot* dpt = k.GetDepot();
    dpt->Store("name", "David");

    REQUIRE(k.Html() == "<html>David</html>");
  }

  SECTION("interpolates multiple occurrences") {
    string tmpl = "<html>{{name}}.{{name}}</html>";
    Kemplate k(tmpl);
    Depot* dpt = k.GetDepot();
    dpt->Store("name", "David");

    REQUIRE(k.Html() == "<html>David.David</html>");
  }

  SECTION("interpolates different keys") {
    string tmpl = "<html>{{name}}: {{job}}</html>";
    Kemplate k(tmpl);
    Depot* dpt = k.GetDepot();
    dpt->Store("name", "David Ko");
    dpt->Store("job", "Software Engineer");

    REQUIRE(k.Html() == "<html>David Ko: Software Engineer</html>");
  }

  SECTION("allows for keys in the data object that are not used") {
    string tmpl = "<html>{{name}}: {{job}}</html>";
    Kemplate k(tmpl);
    Depot* dpt = k.GetDepot();
    dpt->Store("name", "David Ko");
    dpt->Store("job", "Software Engineer");
    dpt->Store("foo", "bar");

    REQUIRE(k.Html() == "<html>David Ko: Software Engineer</html>");
  }

  SECTION("interpolates empty space for a key that does not exist in the data object") {
    string tmpl = "<html>{{name}}: {{job}}<p>{{foo}}</p></html>";
    Kemplate k(tmpl);
    Depot* dpt = k.GetDepot();
    dpt->Store("name", "David Ko");
    dpt->Store("job", "Software Engineer");

    REQUIRE(k.Html() == "<html>David Ko: Software Engineer<p></p></html>");
  }

  SECTION("interpolates a Handlebars datapoint with whitespace between the key and the brace") {
    string tmpl = "<html>{{ name}}: {{job }}<p>{{foo  }}</p></html>";
    Kemplate k(tmpl);
    Depot* dpt = k.GetDepot();
    dpt->Store("name", "David Ko");
    dpt->Store("job", "Software Engineer");

    REQUIRE(k.Html() == "<html>David Ko: Software Engineer<p></p></html>");
  }
}

TEST_CASE("Kemplate#GetTemplate", "calling k.GetTemplate()") {
  SECTION("returns a template string in it's pre-interpolated state") {
    string tmpl = "<html>{{name}}: {{job}}</html>";
    Kemplate k(tmpl);

    REQUIRE(k.GetTemplate() == "<html>{{name}}: {{job}}</html>");
  }
}
