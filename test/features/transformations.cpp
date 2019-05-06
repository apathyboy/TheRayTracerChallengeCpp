
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

            THEN("transform * p == point(-2, 3, 4)")
            {
                REQUIRE(transform * p == rtc::point(-2, 3, 4));
            }
        }
    }
}

SCENARIO("Rotating a point around the x axis", "[transformations]")
{
    GIVEN("p = point(0, 1, 0)")
    {
        auto p = rtc::point(0, 1, 0);

        AND_GIVEN("half_quarter = rotation_x(PI / 4)")
        {
            auto half_quarter = rtc::rotation_x(rtc::PI / 4);

            AND_GIVEN("full_quarter = rotation_x(PI / 2)")
            {
                auto full_quarter = rtc::rotation_x(rtc::PI / 2);

                THEN("half_quarter * p == point(0, sqrt(2)/2, sqrt(2)/2")
                {
                    REQUIRE(half_quarter * p
                            == rtc::point(0, std::sqrtf(2) / 2, std::sqrtf(2) / 2));

                    AND_THEN("full_quarter * p == point(0, 0, 1)")
                    {
                        REQUIRE(full_quarter * p == rtc::point(0, 0, 1));
                    }
                }
            }
        }
    }
}

SCENARIO("The inverse of x-rotation rotates in opposite direction",
         "[transformations]")
{
    GIVEN("p = point(0, 1, 0)")
    {
        auto p = rtc::point(0, 1, 0);

        AND_GIVEN("half_quarter = rotation_x(PI / 4)")
        {
            auto half_quarter = rtc::rotation_x(rtc::PI / 4);

            AND_GIVEN("inv = inverse(half_quarter)")
            {
                auto inv = rtc::inverse(half_quarter);

                THEN("inv * p == point(0, sqrt(2)/2, sqrt(2)/2)")
                {
                    REQUIRE(
                        inv * p
                        == rtc::point(0, std::sqrtf(2) / 2, -std::sqrtf(2) / 2));
                }
            }
        }
    }
}

SCENARIO("Rotating a point around the y axis", "[transformations]")
{
    GIVEN("p = point(0, 0, 1)")
    {
        auto p = rtc::point(0, 0, 1);

        AND_GIVEN("half_quarter = rotation_y(PI / 4)")
        {
            auto half_quarter = rtc::rotation_y(rtc::PI / 4);

            AND_GIVEN("full_quarter = rotation_y(PI / 2)")
            {
                auto full_quarter = rtc::rotation_y(rtc::PI / 2);

                THEN("half_quarter * p == point(sqrt(2)/2, 0, sqrt(2)/2)")
                {
                    REQUIRE(half_quarter * p
                            == rtc::point(std::sqrtf(2) / 2, 0, std::sqrtf(2) / 2));

                    AND_THEN("full_quarter * p == point(1, 0, 0)")
                    {
                        REQUIRE(full_quarter * p == rtc::point(1, 0, 0));
                    }
                }
            }
        }
    }
}

SCENARIO("Rotating a point around the z axis", "[transformations]")
{
    GIVEN("p = point(0, 1, 0)")
    {
        auto p = rtc::point(0, 1, 0);

        AND_GIVEN("half_quarter = rotation_z(PI / 4)")
        {
            auto half_quarter = rtc::rotation_z(rtc::PI / 4);

            AND_GIVEN("full_quarter = rotation_z(PI / 2)")
            {
                auto full_quarter = rtc::rotation_z(rtc::PI / 2);

                THEN("half_quarter * p == point(-sqrt(2)/2, sqrt(2)/2, 0)")
                {
                    REQUIRE(
                        half_quarter * p
                        == rtc::point(-std::sqrtf(2) / 2, std::sqrtf(2) / 2, 0));

                    AND_THEN("full_quarter * p == point(-1, 0, 0)")
                    {
                        REQUIRE(full_quarter * p == rtc::point(-1, 0, 0));
                    }
                }
            }
        }
    }
}
