#include "../src/kemplate.hpp"
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

TEST_CASE("Kemplate", "#constructor") {
  Kemplate k;
  string tmpl = k.HtmlTemplate();
  REQUIRE(tmpl == "<html></html>");
}
