
#include <rtc/tuple.hpp>
#include <rtc/ray.hpp>

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
