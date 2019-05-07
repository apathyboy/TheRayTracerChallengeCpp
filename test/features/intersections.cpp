
#include <rtc/sphere.hpp>
#include <rtc/intersections.hpp>

#include <catch2/catch.hpp>

using namespace Catch::literals;

SCENARIO("An intersection encapsulates t and object", "[intersections]")
{
    GIVEN("s = sphere()")
    {
        auto s = rtc::sphere();

        WHEN("i = intersection(3.5, s)")
        {
            auto i = rtc::intersection_t{3.5f, s};

            THEN("i.t == 3.5")
            {
                REQUIRE(i.t == 3.5_a);

                AND_THEN("i.object == s") { REQUIRE(i.object == s); }
            }
        }
    }
}

SCENARIO("Aggregating intersections", "[intersections]")
{
    GIVEN("s = sphere()")
    {
        auto s = rtc::sphere();

        AND_GIVEN("i1 = intersection(1, s)")
        {
            auto i1 = rtc::intersection_t{1, s};

            AND_GIVEN("i2 = intersection(2, s)")
            {
                auto i2 = rtc::intersection_t{2, s};

                WHEN("xs = intersections(i1, i2)")
                {
                    auto xs = rtc::intersections_t{i1, i2};

                    THEN("xs.count == 2")
                    {
                        REQUIRE(xs.size() == 2);

                        AND_THEN("xs[0].t == 1") { REQUIRE(xs[0].t == 1_a); }
                        AND_THEN("xs[1].t == 2") { REQUIRE(xs[1].t == 2_a); }
                    }
                }
            }
        }
    }
}

SCENARIO("Intersect sets the object on the intersection", "[intersections]")
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

                    AND_THEN("xs[0].object == s") { REQUIRE(xs[0].object == s); }
                    AND_THEN("xs[1].object == s") { REQUIRE(xs[1].object == s); }
                }
            }
        }
    }
}

SCENARIO("The hit, when all intersections have positive t", "[intersections]")
{
    GIVEN("s = sphere()")
    {
        auto s = rtc::sphere();

        AND_GIVEN("i1 = intersection(1, s)")
        {
            auto i1 = rtc::intersection_t{1, s};

            AND_GIVEN("i2 = intersection(2, s)")
            {
                auto i2 = rtc::intersection_t{2, s};

                AND_GIVEN("xs = intersections(i2, i1)")
                {
                    auto xs = rtc::intersections_t{i2, i1};

                    WHEN("i = hit(xs)")
                    {
                        auto i = rtc::hit(xs);

                        THEN("i == i1") { REQUIRE(*i == i1); }
                    }
                }
            }
        }
    }
}

SCENARIO("The hit, when some intersections have negative t", "[intersections]")
{
    GIVEN("s = sphere()")
    {
        auto s = rtc::sphere();

        AND_GIVEN("i1 = intersection(-1, s)")
        {
            auto i1 = rtc::intersection_t{-1, s};

            AND_GIVEN("i2 = intersection(1, s)")
            {
                auto i2 = rtc::intersection_t{1, s};

                AND_GIVEN("xs = intersections(i2, i1)")
                {
                    auto xs = rtc::intersections_t{i2, i1};

                    WHEN("i = hit(xs)")
                    {
                        auto i = rtc::hit(xs);

                        THEN("i == i2") { REQUIRE(*i == i2); }
                    }
                }
            }
        }
    }
}

SCENARIO("The hit, when all intersections have negative t", "[intersections]")
{
    GIVEN("s = sphere()")
    {
        auto s = rtc::sphere();

        AND_GIVEN("i1 = intersection(-2, s)")
        {
            auto i1 = rtc::intersection_t{-2, s};

            AND_GIVEN("i2 = intersection(-1, s)")
            {
                auto i2 = rtc::intersection_t{-1, s};

                AND_GIVEN("xs = intersections(i2, i1)")
                {
                    auto xs = rtc::intersections_t{i2, i1};

                    WHEN("i = hit(xs)")
                    {
                        auto i = rtc::hit(xs);

                        THEN("i is nothing") { REQUIRE_FALSE(i); }
                    }
                }
            }
        }
    }
}

SCENARIO("The hit is always the lowest non-negative intersection",
         "[intersections]")
{
    GIVEN("s = sphere()")
    {
        auto s = rtc::sphere();

        AND_GIVEN("i1 = intersection(5, s)")
        {
            auto i1 = rtc::intersection_t{5, s};

            AND_GIVEN("i2 = intersection(7, s)")
            {
                auto i2 = rtc::intersection_t{7, s};

                AND_GIVEN("i3 = intersection(-3, s)")
                {
                    auto i3 = rtc::intersection_t{-3, s};

                    AND_GIVEN("i4 = intersection(2, s)")
                    {
                        auto i4 = rtc::intersection_t{2, s};

                        AND_GIVEN("xs = intersections(i2, i1)")
                        {
                            auto xs = rtc::intersections_t{i1, i2, i3, i4};

                            WHEN("i = hit(xs)")
                            {
                                auto i = rtc::hit(xs);

                                THEN("i == i4") { REQUIRE(*i == i4); }
                            }
                        }
                    }
                }
            }
        }
    }
}
