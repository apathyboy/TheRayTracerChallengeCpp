
#include <rtc/ray.hpp>
#include <rtc/sphere.hpp>

#include <catch2/catch.hpp>

using namespace Catch::literals;

SCENARIO("A ray intersects a sphere at two points", "[spheres]")
{
    GIVEN("r = ray(point(0, 0, -5), vector(0, 0, 1))")
    {
        auto r = rtc::ray_t{rtc::point(0, 0, -5), rtc::vector(0, 0, 1)};

        AND_GIVEN("s = sphere()")
        {
            auto s = rtc::sphere();

            WHEN("xs = intersect(s, r)")
            {
                auto xs = rtc::intersect(s, r);

                THEN("xs.count == 2")
                {
                    REQUIRE(xs.size() == 2);

                    AND_THEN("xs[0] == 4.0") { REQUIRE(xs[0] == 4_a); }
                    AND_THEN("xs[1] == 6.0") { REQUIRE(xs[1] == 6_a); }
                }
            }
        }
    }
}

SCENARIO("A ray intersects a sphere at a tangent", "[spheres]")
{
    GIVEN("r = ray(point(0, 1, -5), vector(0, 0, 1))")
    {
        auto r = rtc::ray_t{rtc::point(0, 1, -5), rtc::vector(0, 0, 1)};

        AND_GIVEN("s = sphere()")
        {
            auto s = rtc::sphere();

            WHEN("xs = intersect(s, r)")
            {
                auto xs = rtc::intersect(s, r);

                THEN("xs.count == 2")
                {
                    REQUIRE(xs.size() == 2);

                    AND_THEN("xs[0] == 5.0") { REQUIRE(xs[0] == 5_a); }
                    AND_THEN("xs[1] == 5.0") { REQUIRE(xs[1] == 5_a); }
                }
            }
        }
    }
}

SCENARIO("A ray misses a sphere", "[spheres]")
{
    GIVEN("r = ray(point(0, 2, -5), vector(0, 0, 1))")
    {
        auto r = rtc::ray_t{rtc::point(0, 2, -5), rtc::vector(0, 0, 1)};

        AND_GIVEN("s = sphere()")
        {
            auto s = rtc::sphere();

            WHEN("xs = intersect(s, r)")
            {
                auto xs = rtc::intersect(s, r);

                THEN("xs.count == 0") { REQUIRE(xs.size() == 0); }
            }
        }
    }
}

SCENARIO("A ray originates inside a sphere", "[spheres]")
{
    GIVEN("r = ray(point(0, 0, 0), vector(0, 0, 1))")
    {
        auto r = rtc::ray_t{rtc::point(0, 0, 0), rtc::vector(0, 0, 1)};

        AND_GIVEN("s = sphere()")
        {
            auto s = rtc::sphere();

            WHEN("xs = intersect(s, r)")
            {
                auto xs = rtc::intersect(s, r);

                THEN("xs.count == 2")
                {
                    REQUIRE(xs.size() == 2);

                    AND_THEN("xs[0] == -1.0") { REQUIRE(xs[0] == -1_a); }
                    AND_THEN("xs[1] == 1.0") { REQUIRE(xs[1] == 1_a); }
                }
            }
        }
    }
}

SCENARIO("A sphere is behind a ray", "[spheres]")
{
    GIVEN("r = ray(point(0, 0, 5), vector(0, 0, 1))")
    {
        auto r = rtc::ray_t{rtc::point(0, 0, 5), rtc::vector(0, 0, 1)};

        AND_GIVEN("s = sphere()")
        {
            auto s = rtc::sphere();

            WHEN("xs = intersect(s, r)")
            {
                auto xs = rtc::intersect(s, r);

                THEN("xs.count == 2")
                {
                    REQUIRE(xs.size() == 2);

                    AND_THEN("xs[0] == -6.0") { REQUIRE(xs[0] == -6_a); }
                    AND_THEN("xs[1] == -4.0") { REQUIRE(xs[1] == -4_a); }
                }
            }
        }
    }
}
