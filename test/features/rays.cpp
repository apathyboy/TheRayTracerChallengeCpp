
#include <rtc/ray.hpp>
#include <rtc/transformations.hpp>
#include <rtc/tuple.hpp>

#include <catch2/catch.hpp>

SCENARIO("Creating and querying a ray", "[rays]")
{
    GIVEN("origin = point(1, 2, 3)")
    {
        auto origin = rtc::point(1, 2, 3);

        AND_GIVEN("direction = vector(4, 5, 6)")
        {
            auto direction = rtc::vector(4, 5, 6);

            WHEN("r = ray(origin, direction)")
            {
                auto r = rtc::ray_t{origin, direction};

                THEN("r.origin == origin") { REQUIRE(r.origin == origin); }

                AND_THEN("r.direction == direction")
                {
                    REQUIRE(r.direction == direction);
                }
            }
        }
    }
}

SCENARIO("Computing a point from a distance", "[rays]")
{
    GIVEN("r = ray(point(2, 3, 4), vector(1, 0, 0))")
    {
        auto r = rtc::ray_t{rtc::point(2, 3, 4), rtc::vector(1, 0, 0)};

        THEN("position(r, 0) == point(2, 3, 4)")
        {
            REQUIRE(rtc::position(r, 0) == rtc::point(2, 3, 4));
        }
        AND_THEN("position(r, 1) == point(3, 3, 4)")
        {
            REQUIRE(rtc::position(r, 1) == rtc::point(3, 3, 4));
        }
        AND_THEN("position(r, -1) == point(1, 3, 4)")
        {
            REQUIRE(rtc::position(r, -1) == rtc::point(1, 3, 4));
        }
        AND_THEN("position(r, 2.5) == point(4.5, 3, 4)")
        {
            REQUIRE(rtc::position(r, 2.5f) == rtc::point(4.5f, 3, 4));
        }
    }
}

SCENARIO("Translating a ray", "[rays]")
{
    GIVEN("r = ray(point(1, 2, 3), vector(0, 1, 0))")
    {
        auto r = rtc::ray_t{rtc::point(1, 2, 3), rtc::vector(0, 1, 0)};

        AND_GIVEN("m = translation(3, 4, 5)")
        {
            auto m = rtc::translation(3, 4, 5);

            WHEN("r2 = transform(r, m)")
            {
                auto r2 = rtc::transform(r, m);

                THEN("r2.origin == point(4, 6, 8)")
                {
                    REQUIRE(r2.origin == rtc::point(4, 6, 8));
                }
                AND_THEN("r2.direction == vector(0, 1, 0)")
                {
                    REQUIRE(r2.direction == rtc::vector(0, 1, 0));
                }
            }
        }
    }
}

SCENARIO("Scaling a ray", "[rays]")
{
    GIVEN("r = ray(point(1, 2, 3), vector(0, 1, 0))")
    {
        auto r = rtc::ray_t{rtc::point(1, 2, 3), rtc::vector(0, 1, 0)};

        AND_GIVEN("m = scaling(2, 3, 4)")
        {
            auto m = rtc::scaling(2, 3, 4);

            WHEN("r2 = transform(r, m)")
            {
                auto r2 = rtc::transform(r, m);
                THEN("r2.origin == point(2, 6, 12)")
                {
                    REQUIRE(r2.origin == rtc::point(2, 6, 12));
                }
                AND_THEN("r2.direction == vector(0, 3, 0)")
                {
                    REQUIRE(r2.direction == rtc::vector(0, 3, 0));
                }
            }
        }
    }
}
