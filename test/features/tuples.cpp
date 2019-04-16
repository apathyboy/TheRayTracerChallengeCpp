
#include <rtc/tuple.hpp>

#include <catch2/catch.hpp>

using namespace Catch::literals;

SCENARIO("A tuple with w=1.0 is a point", "[tuples]")
{
    GIVEN("a = tuple(4.3, -4.2, 3.1, 1.0)")
    {
        auto a = rtc::tuple_t{4.3f, -4.2f, 3.1f, 1.0f};

        THEN("a.x == 4.3") { REQUIRE(a.x == 4.3_a); }
        AND_THEN("a.y == -4.2") { REQUIRE(a.y == -4.2_a); }
        AND_THEN("a.z == 3.1") { REQUIRE(a.z == 3.1_a); }
        AND_THEN("a.w == 1.0") { REQUIRE(a.w == 1.0_a); }
        AND_THEN("a is a point") { REQUIRE(rtc::is_point(a)); }
        AND_THEN("a is not a vector") { REQUIRE_FALSE(rtc::is_vector(a)); }
    }
}
