
#include <rtc/intersections.hpp>
#include <rtc/materials.hpp>
#include <rtc/ray.hpp>
#include <rtc/sphere.hpp>
#include <rtc/transformations.hpp>

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

                    AND_THEN("xs[0] == 4.0") { REQUIRE(xs[0].t == 4_a); }
                    AND_THEN("xs[1] == 6.0") { REQUIRE(xs[1].t == 6_a); }
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

                    AND_THEN("xs[0] == 5.0") { REQUIRE(xs[0].t == 5_a); }
                    AND_THEN("xs[1] == 5.0") { REQUIRE(xs[1].t == 5_a); }
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

                    AND_THEN("xs[0] == -1.0") { REQUIRE(xs[0].t == -1_a); }
                    AND_THEN("xs[1] == 1.0") { REQUIRE(xs[1].t == 1_a); }
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

                    AND_THEN("xs[0] == -6.0") { REQUIRE(xs[0].t == -6_a); }
                    AND_THEN("xs[1] == -4.0") { REQUIRE(xs[1].t == -4_a); }
                }
            }
        }
    }
}

SCENARIO("A sphere's default transformation", "[spheres]")
{
    GIVEN("s = sphere()")
    {
        auto s = rtc::sphere();

        THEN("s.transform == identity_matrix")
        {
            REQUIRE(s.transform == rtc::matrix4x4_t::identity());
        }
    }
}

SCENARIO("Changing a sphere's transformation", "[spheres]")
{
    GIVEN("s = sphere()")
    {
        auto s = rtc::sphere();

        AND_GIVEN("t = translation(2, 3, 4)")
        {
            auto t = rtc::translation(2, 3, 4);

            WHEN("set_transform(s, t)")
            {
                s.transform = t;

                THEN("s.transform == t") { REQUIRE(s.transform == t); }
            }
        }
    }
}

SCENARIO("Intersecting a scaled sphere with a ray", "[spheres]")
{
    GIVEN("r = ray(point(0, 0, -5), vector(0, 0, 1))")
    {
        auto r = rtc::ray_t{rtc::point(0, 0, -5), rtc::vector(0, 0, 1)};

        AND_GIVEN("s = sphere()")
        {
            auto s = rtc::sphere();

            WHEN("set_transform(s, scaling(2, 2, 2))")
            {
                s.transform = rtc::scaling(2, 2, 2);

                AND_WHEN("xs = intersect(s, r)")
                {
                    auto xs = rtc::intersect(s, r);

                    THEN("xs.count == 2")
                    {
                        REQUIRE(xs.size() == 2);

                        AND_THEN("xs[0].t == 3") { REQUIRE(xs[0].t == 3_a); }
                        AND_THEN("xs[1].t == 7") { REQUIRE(xs[1].t == 7_a); }
                    }
                }
            }
        }
    }
}

SCENARIO("Intersecting a translated sphere with a ray", "[spheres]")
{
    GIVEN("r = ray(point(0, 0, -5), vector(0, 0, 1))")
    {
        auto r = rtc::ray_t{rtc::point(0, 0, -5), rtc::vector(0, 0, 1)};

        AND_GIVEN("s = sphere()")
        {
            auto s = rtc::sphere();

            WHEN("set_transform(s, translation(5, 0, 0))")
            {
                s.transform = rtc::translation(5, 0, 0);

                AND_WHEN("xs = intersect(s, r)")
                {
                    auto xs = rtc::intersect(s, r);

                    THEN("xs.count == 0") { REQUIRE(xs.size() == 0); }
                }
            }
        }
    }
}

SCENARIO("The normal on a sphere at a point on the x axis", "[spheres]")
{
    GIVEN("s = sphere()")
    {
        auto s = rtc::sphere();

        WHEN("n = normal_at(s, point(1, 0, 0))")
        {
            auto n = rtc::normal_at(s, rtc::point(1, 0, 0));

            THEN("n == vector(1, 0, 0)") { REQUIRE(n == rtc::vector(1, 0, 0)); }
        }
    }
}

SCENARIO("The normal on a sphere at a point on the y axis", "[spheres]")
{
    GIVEN("s = sphere()")
    {
        auto s = rtc::sphere();

        WHEN("n = normal_at(s, point(0, 1, 0))")
        {
            auto n = rtc::normal_at(s, rtc::point(0, 1, 0));

            THEN("n == vector(0, 1, 0)") { REQUIRE(n == rtc::vector(0, 1, 0)); }
        }
    }
}

SCENARIO("The normal on a sphere at a point on the z axis", "[spheres]")
{
    GIVEN("s = sphere()")
    {
        auto s = rtc::sphere();

        WHEN("n = normal_at(s, point(0, 0, 1))")
        {
            auto n = rtc::normal_at(s, rtc::point(0, 0, 1));

            THEN("n == vector(0, 0, 1)") { REQUIRE(n == rtc::vector(0, 0, 1)); }
        }
    }
}

SCENARIO("The normal on a sphere at a nonaxial point", "[spheres]")
{
    GIVEN("s = sphere()")
    {
        auto s = rtc::sphere();

        WHEN("n = normal_at(s, point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3))")
        {
            auto n = rtc::normal_at(s,
                                    rtc::point(std::sqrtf(3) / 3,
                                               std::sqrtf(3) / 3,
                                               std::sqrtf(3) / 3));

            THEN("n == vector(0, 0, 1)")
            {
                REQUIRE(n
                        == rtc::vector(std::sqrtf(3) / 3,
                                       std::sqrtf(3) / 3,
                                       std::sqrtf(3) / 3));
            }
        }
    }
}

SCENARIO("The normal is a normalization vector", "[spheres]")
{
    GIVEN("s = sphere()")
    {
        auto s = rtc::sphere();

        WHEN("n = normal_at(s, point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3))")
        {
            auto n = rtc::normal_at(s,
                                    rtc::point(std::sqrtf(3) / 3,
                                               std::sqrtf(3) / 3,
                                               std::sqrtf(3) / 3));

            THEN("n == normalize(n)") { REQUIRE(n == rtc::normalize(n)); }
        }
    }
}

SCENARIO("Computing the normal on a translated sphere", "[spheres]")
{
    GIVEN("s = sphere()")
    {
        auto s = rtc::sphere();

        AND_GIVEN("set_transform(s, translation(0, 1, 0))")
        {
            s.transform = rtc::translation(0, 1, 0);

            WHEN("n = normal_at(s, point(0, 1.70711, -0.70711))")
            {
                auto n = rtc::normal_at(s, rtc::point(0, 1.70711f, -0.70711f));

                THEN("n == vector(0, 0.70711, -0.70711")
                {
                    REQUIRE(n == rtc::vector(0, 0.70711f, -0.70711f));
                }
            }
        }
    }
}

SCENARIO("Computing the normal on a transformed sphere", "[spheres]")
{
    GIVEN("s = sphere()")
    {
        auto s = rtc::sphere();

        AND_GIVEN("m = scaling(1, 0.5, 1) * rotation_z(PI/5)")
        {
            auto m = rtc::scaling(1, 0.5f, 1) * rtc::rotation_z(rtc::PI / 5);

            AND_GIVEN("set_transform(s, m")
            {
                s.transform = m;

                WHEN("n = normal_at(s, point(0, sqrt(2)/2, sqrt(2)/2))")
                {
                    auto n = rtc::normal_at(
                        s, rtc::point(0, std::sqrtf(2) / 2, -std::sqrtf(2) / 2));

                    THEN("n == vector(0, 0.97014, -0.24254")
                    {
                        REQUIRE(n == rtc::vector(0, 0.97014f, -0.24254f));
                    }
                }
            }
        }
    }
}

SCENARIO("A sphere has a default material", "[spheres]")
{
    GIVEN("s = sphere()")
    {
        auto s = rtc::sphere();

        WHEN("m = s.material")
        {
            auto m = s.material;

            THEN("m == material()") { REQUIRE(m == rtc::material()); }
        }
    }
}

SCENARIO("A sphere may be assigned a material", "[spheres]")
{
    GIVEN("s = sphere()")
    {
        auto s = rtc::sphere();

        AND_GIVEN("m = material()")
        {
            auto m = rtc::material();

            AND_GIVEN("m.ambient = 1")
            {
                m.ambient = 1;

                WHEN("s.material = m")
                {
                    s.material = m;

                    THEN("s.material == m") { REQUIRE(s.material == m); }
                }
            }
        }
    }
}
