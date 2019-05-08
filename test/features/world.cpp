
#include <rtc/algorithm.hpp>
#include <rtc/transformations.hpp>
#include <rtc/world.hpp>

#include <catch2/catch.hpp>

using namespace Catch::literals;

SCENARIO("Creating a world", "[world]")
{
    GIVEN("w = world()")
    {
        auto w = rtc::world_t{};

        THEN("w contains no objects") { REQUIRE(w.objects.size() == 0); }
        AND_THEN("w has no light source") { REQUIRE_FALSE(w.light_source); }
    }
}

SCENARIO("The default world", "[world]")
{
    GIVEN("light = point_light(point(-10, 10, -10), color(1, 1, 1))")
    {
        auto light = rtc::point_light_t{rtc::point(-10, 10, -10),
                                        rtc::color(1, 1, 1)};

        AND_GIVEN(
            "s1 = sphere() with:\n"
            "| material.color       | (0.8, 1.0, 0.6)   |\n"
            "| material.diffuse     | 0.7               |\n"
            "| material.specular    | 0.2               |")
        {
            auto s1              = rtc::sphere();
            s1.material.color    = rtc::color(0.8f, 1.f, 0.6f);
            s1.material.diffuse  = 0.7f;
            s1.material.specular = 0.2f;

            AND_GIVEN(
                "s2 = sphere() with:\n"
                "| transform | scaling(0.5, 0.5, 0.5) |")
            {
                auto s2      = rtc::sphere();
                s2.transform = rtc::scaling(0.5f, 0.5f, 0.5f);

                WHEN("w = default_world()")
                {
                    auto w = rtc::default_world();

                    THEN("w.light == light")
                    {
                        REQUIRE(*w.light_source == light);
                        AND_THEN("w contains s1")
                        {
                            REQUIRE(rtc::contains(w.objects, s1));
                        }
                        AND_THEN("w contains s2")
                        {
                            REQUIRE(rtc::contains(w.objects, s2));
                        }
                    }
                }
            }
        }
    }
}

SCENARIO("Intersect a world with a ray", "[world]")
{
    GIVEN("w = default_world()")
    {
        auto w = rtc::default_world();

        AND_GIVEN("r = ray(point(0, 0, -5), vector(0, 0, 1))")
        {
            auto r = rtc::ray_t{rtc::point(0, 0, -5), rtc::vector(0, 0, 1)};

            WHEN("xs = intersect_world(w, r)")
            {
                auto xs = rtc::intersect(w, r);

                THEN("xs.count == 4")
                {
                    REQUIRE(xs.size() == 4);

                    AND_THEN("xs[0].t == 4") { REQUIRE(xs[0].t == 4_a); }
                    AND_THEN("xs[1].t == 4.5") { REQUIRE(xs[1].t == 4.5_a); }
                    AND_THEN("xs[2].t == 5.5") { REQUIRE(xs[2].t == 5.5_a); }
                    AND_THEN("xs[3].t == 6") { REQUIRE(xs[3].t == 6_a); }
                }
            }
        }
    }
}

SCENARIO("Shading an intersection", "[world]")
{
    GIVEN("w = default_world()")
    {
        auto w = rtc::default_world();

        AND_GIVEN("r = ray(point(0, 0, -5), vector(0, 0, 1))")
        {
            auto r = rtc::ray_t{rtc::point(0, 0, -5), rtc::vector(0, 0, 1)};

            AND_GIVEN("shape = the first object in w")
            {
                const auto& shape = w.objects[0];

                AND_GIVEN("i = intersection(4, shape)")
                {
                    auto i = rtc::intersection_t{4, shape};

                    WHEN("comps = prepare_computations(i, r)")
                    {
                        auto comps = rtc::prepare_computations(i, r);

                        AND_WHEN("c = shade_hit(w, comps)")
                        {
                            auto c = rtc::shade_hit(w, comps);

                            THEN("c == color(0.38066, 0.47583, 0.2855)")
                            {
                                REQUIRE(c
                                        == rtc::color(0.38066f, 0.47583f, 0.2855f));
                            }
                        }
                    }
                }
            }
        }
    }
}

SCENARIO("Shading an intersection from the inside", "[world]")
{
    GIVEN("w = default_world()")
    {
        auto w = rtc::default_world();

        AND_GIVEN("w.light = point_light(point(0, 0.25, 0), color(1, 1, 1))")
        {
            w.light_source = rtc::point_light_t{rtc::point(0, 0.25f, 0),
                                                rtc::color(1, 1, 1)};

            AND_GIVEN("r = ray(point(0, 0, 0), vector(0, 0, 1))")
            {
                auto r = rtc::ray_t{rtc::point(0, 0, 0), rtc::vector(0, 0, 1)};

                AND_GIVEN("shape = the second object in w")
                {
                    const auto& shape = w.objects[1];

                    AND_GIVEN("i = intersection(0.5, shape)")
                    {
                        auto i = rtc::intersection_t{0.5f, shape};

                        WHEN("comps = prepare_computations(i, r)")
                        {
                            auto comps = rtc::prepare_computations(i, r);

                            AND_WHEN("c = shade_hit(w, comps)")
                            {
                                auto c = rtc::shade_hit(w, comps);

                                THEN("c == color(0.90498, 0.90498, 0.90498)")
                                {
                                    REQUIRE(c
                                            == rtc::color(
                                                   0.90498f, 0.90498f, 0.90498f));
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

SCENARIO("The color when a ray misses", "[world]")
{
    GIVEN("w = default_world()")
    {
        auto w = rtc::default_world();

        AND_GIVEN("r = ray(point(0, 0, -5), vector(0, 1, 0))")
        {
            auto r = rtc::ray_t{rtc::point(0, 0, -5), rtc::vector(0, 1, 0)};

            WHEN("c = color_at(w, r)")
            {
                auto c = rtc::color_at(w, r);

                THEN("c == color(0, 0, 0)") { REQUIRE(c == rtc::color(0, 0, 0)); }
            }
        }
    }
}

SCENARIO("The color when a ray hits", "[world]")
{
    GIVEN("w = default_world()")
    {
        auto w = rtc::default_world();

        AND_GIVEN("r = ray(point(0, 0, -5), vector(0, 0, 1))")
        {
            auto r = rtc::ray_t{rtc::point(0, 0, -5), rtc::vector(0, 0, 1)};

            WHEN("c = color_at(w, r)")
            {
                auto c = rtc::color_at(w, r);

                THEN("c == color(0.38066, 0.47583, 0.2855)")
                {
                    REQUIRE(c == rtc::color(0.38066f, 0.47583f, 0.2855f));
                }
            }
        }
    }
}

SCENARIO("The color with an intersection behind the ray", "[world]")
{
    GIVEN("w = default_world()")
    {
        auto w = rtc::default_world();

        AND_GIVEN("outer = the first object in w")
        {
            auto& outer = w.objects[0];

            AND_GIVEN("outer.material.ambient = 1")
            {
                outer.material.ambient = 1;

                AND_GIVEN("inner = the second object in w")
                {
                    auto& inner = w.objects[1];

                    AND_GIVEN("inner.material.ambient = 1")
                    {
                        inner.material.ambient = 1;

                        AND_GIVEN("r = ray(point(0, 0, 0.75), vector(0, 0, -1))")
                        {
                            auto r = rtc::ray_t{rtc::point(0, 0, 0.75f),
                                                rtc::vector(0, 0, -1)};

                            WHEN("c = color_at(w, r)")
                            {
                                auto c = rtc::color_at(w, r);

                                THEN("c == inner.material.color")
                                {
                                    REQUIRE(c == inner.material.color);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

SCENARIO("There is no shadow when nothing is collinear with point and light",
         "[world]")
{
    GIVEN("w = default_world()")
    {
        auto w = rtc::default_world();

        AND_GIVEN("p = point(0, 10, 0)")
        {
            auto p = rtc::point(0, 10, 0);

            THEN("is_shadowed(w, p) is false")
            {
                REQUIRE_FALSE(rtc::is_shadowed(w, p));
            }
        }
    }
}

SCENARIO("The shadow when an object is between the point and the light", "[world]")
{
    GIVEN("w = default_world()")
    {
        auto w = rtc::default_world();

        AND_GIVEN("p = point(10, -10, 10)")
        {
            auto p = rtc::point(10, -10, 10);

            THEN("is_shadowed(w, p) is true") { REQUIRE(rtc::is_shadowed(w, p)); }
        }
    }
}

SCENARIO("There is no shadow when an object is behind the light", "[world]")
{
    GIVEN("w = default_world()")
    {
        auto w = rtc::default_world();

        AND_GIVEN("p = point(-20, 20, -20)")
        {
            auto p = rtc::point(-20, 20, -20);

            THEN("is_shadowed(w, p) is false")
            {
                REQUIRE_FALSE(rtc::is_shadowed(w, p));
            }
        }
    }
}

SCENARIO("There is no shadow when an object is behind the point", "[world]")
{
    GIVEN("w = default_world()")
    {
        auto w = rtc::default_world();

        AND_GIVEN("p = point(-2, 2, -2)")
        {
            auto p = rtc::point(-2, 2, -2);

            THEN("is_shadowed(w, p) is false")
            {
                REQUIRE_FALSE(rtc::is_shadowed(w, p));
            }
        }
    }
}

SCENARIO("shade_hit() is given an intersection in shadow", "[world]")
{
    GIVEN("w = world()")
    {
        auto w = rtc::world_t{};

        AND_GIVEN("w.light = point_light(point(0, 0, -10), color(1, 1, 1))")
        {
            w.light_source = rtc::point_light_t{rtc::point(0, 0, -10),
                                                rtc::color(1, 1, 1)};

            AND_GIVEN("s1 = sphere()")
            {
                auto s1 = rtc::sphere();

                AND_GIVEN("s1 is added to w")
                {
                    w.objects.push_back(s1);

                    AND_GIVEN(
                        "s2 = sphere() with:\n"
                        "| transform | translation(0, 0, 10) |")
                    {
                        auto s2      = rtc::sphere();
                        s2.transform = rtc::translation(0, 0, 10);

                        AND_GIVEN("s2 is added to w")
                        {
                            w.objects.push_back(s2);

                            AND_GIVEN("r = ray(point(0, 0, 5), vector(0, 0, 1))")
                            {
                                auto r = rtc::ray_t{rtc::point(0, 0, 5),
                                                    rtc::vector(0, 0, 1)};

                                AND_GIVEN("i = intersection(4, s2)")
                                {
                                    auto i = rtc::intersection_t{4, s2};

                                    WHEN("comps = prepare_computations(i, r)")
                                    {
                                        auto comps = rtc::prepare_computations(i,
                                                                               r);

                                        AND_WHEN("c = shade_hit(w, comps)")
                                        {
                                            auto c = rtc::shade_hit(w, comps);

                                            THEN("c == color(0.1, 0.1, 0.1)")
                                            {
                                                REQUIRE(c
                                                        == rtc::color(
                                                               0.1f, 0.1f, 0.1f));
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
