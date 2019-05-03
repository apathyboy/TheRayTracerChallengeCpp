
#include <rtc/math.hpp>

#include <catch2/catch.hpp>

SCENARIO("Floats within EPSILON are approximately equal", "[math]")
{
    GIVEN("a = 0.0894")
    {
        float a = 0.0894f;

        AND_GIVEN("b = 0.089400000001")
        {
            auto b = 0.08940000001f;

            THEN("a is approximately b") { REQUIRE(rtc::approx(a, b)); }
        }
    }
}

SCENARIO("Floats not within EPSILON are not approximately equal", "[math]")
{
    GIVEN("a = 0.0894")
    {
        float a = 0.0894f;

        AND_GIVEN("b = 0.089499")
        {
            float b = 0.08949f;

            THEN("a is not approximately b") { REQUIRE_FALSE(rtc::approx(a, b)); }
        }
    }
}
