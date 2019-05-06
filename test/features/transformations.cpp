
#include <rtc/transformations.hpp>

#include <catch2/catch.hpp>

SCENARIO("Multiplying by a translation matrix", "[transformations]")
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

SCENARIO("Multiplying by the inverse of a translation matrix", "[transformations]")
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

SCENARIO("Translation does not affect vectors", "[transformations]")
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

SCENARIO("A scaling matrix applied to a point", "[transformations]")
{
    GIVEN("transform = scaling(2, 3, 4)")
    {
        auto transform = rtc::scaling(2, 3, 4);

        AND_GIVEN("p = point(-4, 6, 8)")
        {
            auto p = rtc::point(-4, 6, 8);

            THEN("transform * p == point(-8, 18, 32)")
            {
                REQUIRE(transform * p == rtc::point(-8, 18, 32));
            }
        }
    }
}

SCENARIO("A scaling matrix applied to a vector", "[transformations]")
{
    GIVEN("transform = scaling(2, 3, 4)")
    {
        auto transform = rtc::scaling(2, 3, 4);

        AND_GIVEN("v = vector(-4, 6, 8)")
        {
            auto v = rtc::vector(-4, 6, 8);

            THEN("transform * v == vector(-8, 18, 32)")
            {
                REQUIRE(transform * v == rtc::vector(-8, 18, 32));
            }
        }
    }
}

SCENARIO("Multiplying by the inverse of a scaling matrix", "[transformations]")
{
    GIVEN("transform = scaling(2, 3, 4)")
    {
        auto transform = rtc::scaling(2, 3, 4);

        AND_GIVEN("inv = inverse(transform)")
        {
            auto inv = rtc::inverse(transform);

            AND_GIVEN("v = vector(-4, 6, 8)")
            {
                auto v = rtc::vector(-4, 6, 8);

                THEN("inv * v == vector(-2, 2, 2)")
                {
                    REQUIRE(inv * v == rtc::vector(-2, 2, 2));
                }
            }
        }
    }
}

SCENARIO("Reflection is scaling by a negative value", "[transformations]")
{
    GIVEN("transform = scaling(-1, 1, 1)")
    {
        auto transform = rtc::scaling(-1, 1, 1);

        AND_GIVEN("p = point(2, 3, 4)")
        {
            auto p = rtc::point(2, 3, 4);

            THEN("transform * p = point(-2, 3, 4)")
            {
                REQUIRE(transform * p == rtc::point(-2, 3, 4));
            }
        }
    }
}
