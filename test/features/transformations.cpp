
#include <rtc/transformations.hpp>

#include <catch2/catch.hpp>

SCENARIO("Multiplying by a translation matrix", "[matrices]")
{
    GIVEN("transform = translation(5, -3, 2)")
    {
        auto transform = rtc::translation(5, -3, 2);

        AND_GIVEN("p = point(-3, 4, 5)")
        {
            auto p = rtc::point(-3, 4, 5);

            THEN("transform * p == point(2, 1, 7)")
            {
                REQUIRE(transform * p == rtc::point(2, 1, 7));
            }
        }
    }
}

SCENARIO("Multiplying by the inverse of a translation matrix", "[matrices]")
{
    GIVEN("transform = translation(5, -3, 2)")
    {
        auto transform = rtc::translation(5, -3, 2);

        AND_GIVEN("inv = inverse(transform)")
        {
            auto inv = rtc::inverse(transform);

            AND_GIVEN("p = point(-3, 4, 5)")
            {
                auto p = rtc::point(-3, 4, 5);

                THEN("inv * p == point(-8, 7, 3)")
                {
                    REQUIRE(inv * p == rtc::point(-8, 7, 3));
                }
            }
        }
    }
}

SCENARIO("Translation does not affect vectors", "[matrices]")
{
    GIVEN("transform = translation(5, -3, 2)")
    {
        auto transform = rtc::translation(5, -3, 2);

        AND_GIVEN("v = vector(-3, 4, 5)")
        {
            auto v = rtc::vector(-3, 4, 5);

            THEN("transform * v == v") { REQUIRE(transform * v == v); }
        }
    }
}
