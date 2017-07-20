#include "../src/kemplate.hpp"
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

TEST_CASE("Kemplate#Html", "calling k.Html(map<string, string> data)") {
  SECTION("interpolates a single occurrence") {
    Depot dpt;
    dpt.Store("name", "David");
    string tmpl = "<html>{{name}}</html>";
    Kemplate k(tmpl);

    REQUIRE(k.Html(dpt) == "<html>David</html>");
  }

  SECTION("interpolates multiple occurrences") {
    Depot dpt;
    dpt.Store("name", "David");
    string tmpl = "<html>{{name}}.{{name}}</html>";
    Kemplate k(tmpl);

    REQUIRE(k.Html(dpt) == "<html>David.David</html>");
  }

  SECTION("interpolates different keys") {
    Depot dpt;
    dpt.Store("name", "David Ko");
    dpt.Store("job", "Software Engineer");
    string tmpl = "<html>{{name}}: {{job}}</html>";
    Kemplate k(tmpl);

    REQUIRE(k.Html(dpt) == "<html>David Ko: Software Engineer</html>");
  }

  SECTION("allows for keys in the data object that are not used") {
    Depot dpt;
    dpt.Store("name", "David Ko");
    dpt.Store("job", "Software Engineer");
    dpt.Store("foo", "bar");
    string tmpl = "<html>{{name}}: {{job}}</html>";
    Kemplate k(tmpl);

    REQUIRE(k.Html(dpt) == "<html>David Ko: Software Engineer</html>");
  }

  SECTION("interpolates empty space for a key that does not exist in the data object") {
    Depot dpt;
    dpt.Store("name", "David Ko");
    dpt.Store("job", "Software Engineer");
    string tmpl = "<html>{{name}}: {{job}}<p>{{foo}}</p></html>";
    Kemplate k(tmpl);

    REQUIRE(k.Html(dpt) == "<html>David Ko: Software Engineer<p></p></html>");
  }

  SECTION("interpolates a Handlebars datapoint with whitespace between the key and the brace") {
    Depot dpt;
    dpt.Store("name", "David Ko");
    dpt.Store("job", "Software Engineer");
    string tmpl = "<html>{{ name}}: {{job }}<p>{{foo  }}</p></html>";
    Kemplate k(tmpl);

    REQUIRE(k.Html(dpt) == "<html>David Ko: Software Engineer<p></p></html>");
  }

  SECTION("interpolates and iterates through a Handlebars array") {
    Depot dpt;
    vector<string> hobbies = {"music", "programming", "reading"};
    dpt.Store("hobbies", hobbies);
    string tmpl = "<html><ul>{{#each hobbies}}<li>{{hobby}}</li>{{/each}}</ul></html>";
    Kemplate k(tmpl);

    REQUIRE(k.HtmlForLists(dpt) == "<html><ul><li>music</li><li>programming</li><li>reading</li></ul></html>");
  }

  SECTION("handles multiple array keys") {
    Depot dpt;
    vector<string> hobbies = {"music", "reading"};
    vector<string> fruits = {"apple", "pineapple"};
    dpt.Store("hobbies", hobbies);
    dpt.Store("fruits", fruits);
    string tmpl = "<html><ul>{{#each hobbies}}<li>{{hobby}}</li>{{/each}}</ul><ul>{{#each fruits}}<li>{{fruit}}</li>{{/each}}</ul></html>";
    Kemplate k(tmpl);

    REQUIRE(k.HtmlForLists(dpt) == "<html><ul><li>music</li><li>reading</li></ul><ul><li>apple</li><li>pineapple</li></ul></html>");
  }
}

TEST_CASE("Kemplate#GetTemplate", "calling k.GetTemplate()") {
  SECTION("returns a template string in it's pre-interpolated state") {
    string tmpl = "<html>{{name}}: {{job}}</html>";
    Kemplate k(tmpl);

    REQUIRE(k.GetTemplate() == "<html>{{name}}: {{job}}</html>");
  }
}
