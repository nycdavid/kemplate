#include "../catch.hpp"
#include "../src/kemplate.hpp"

TEST_CASE("Kemplate", "#constructor") {
  Kemplate k;
  string tmpl = k.HtmlTemplate();
  REQUIRE(tmpl == "<html></html>");
}
