#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

TEST_CASE("1 equals 1", "foo") {
  REQUIRE(1 == 1);
}

TEST_CASE("0 DNE 1", "bar") {
  REQUIRE(0 != 1);
}
