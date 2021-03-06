
#include <rtc/tuple.hpp>

#include <catch2/catch.hpp>

using namespace Catch::literals;

SCENARIO("A tuple with w=1.0 is a point", "[tuples]")
{
    GIVEN("a = tuple(4.3, -4.2, 3.1, 1.0)")
    {
        auto a = rtc::tuple4_t{4.3f, -4.2f, 3.1f, 1.0f};

        THEN("a.x == 4.3") { REQUIRE(a.x == 4.3_a); }
        AND_THEN("a.y == -4.2") { REQUIRE(a.y == -4.2_a); }
        AND_THEN("a.z == 3.1") { REQUIRE(a.z == 3.1_a); }
        AND_THEN("a.w == 1.0") { REQUIRE(a.w == 1.0_a); }
        AND_THEN("a is a point") { REQUIRE(rtc::is_point(a)); }
        AND_THEN("a is not a vector") { REQUIRE_FALSE(rtc::is_vector(a)); }
    }
}

SCENARIO("A tuple with w=0 is a vector", "[tuples]")
{
    GIVEN("a = tuple(4.3, -4.2, 3.1, 0.0)")
    {
        auto a = rtc::tuple4_t{4.3f, -4.2f, 3.1f, 0.f};

        THEN("a.x == 4.3") { REQUIRE(a.x == 4.3_a); }
        AND_THEN("a.y == -4.2") { REQUIRE(a.y == -4.2_a); }
        AND_THEN("a.z == 3.1") { REQUIRE(a.z == 3.1_a); }
        AND_THEN("a.w == 0.0") { REQUIRE(a.w == 0.0_a); }
        AND_THEN("a is not a point") { REQUIRE_FALSE(rtc::is_point(a)); }
        AND_THEN("a is a vector") { REQUIRE(rtc::is_vector(a)); }
    }
}

SCENARIO("point() creates tuples with w=1", "[tuples]")
{
    GIVEN("p = point(4, -4, 3)")
    {
        auto p = rtc::point(4, -4, 3);

        THEN("p == tuple(4, -4, 3, 1)")
        {
            REQUIRE(p == rtc::tuple4_t{4, -4, 3, 1});
        }
    }
}

SCENARIO("vector() creates tuples with w=0", "[tuples]")
{
    GIVEN("v = vector(4, -4, 3)")
    {
        auto v = rtc::vector(4, -4, 3);

        THEN("v == tuple(4, -4, 3, 0)")
        {
            REQUIRE(v == rtc::tuple4_t{4, -4, 3, 0});
        }
    }
}

SCENARIO("Adding two tuples", "[tuples]")
{
    GIVEN("a1 = tuple(3, -2, 5, 1)")
    {
        auto a1 = rtc::tuple4_t{3, -2, 5, 1};

        AND_GIVEN("a2 = tuple(-2, 3, 1, 0)")
        {
            auto a2 = rtc::tuple4_t{-2, 3, 1, 0};

            THEN("a1 + a2 == tuple(1, 1, 6, 1)")
            {
                REQUIRE(a1 + a2 == rtc::tuple4_t{1, 1, 6, 1});
            }
        }
    }
}

SCENARIO("Subtracting two points", "[tuples]")
{
    GIVEN("p1 = point(3, 2, 1)")
    {
        auto p1 = rtc::point(3, 2, 1);

        AND_GIVEN("p2 = point(5, 6, 7)")
        {
            auto p2 = rtc::point(5, 6, 7);

            THEN("p1 - p2 == vector(-2, -4, -6)")
            {
                REQUIRE(p1 - p2 == rtc::vector(-2, -4, -6));
            }
        }
    }
}

SCENARIO("Subtracting a vector from a point", "[tuples]")
{
    GIVEN("p = point(3, 2, 1)")
    {
        auto p = rtc::point(3, 2, 1);

        AND_GIVEN("v = vector(5, 6, 7)")
        {
            auto v = rtc::vector(5, 6, 7);

            THEN("p - v == point(-2, -4, -6)")
            {
                REQUIRE(p - v == rtc::point(-2, -4, -6));
            }
        }
    }
}

SCENARIO("Subtracting two vectors", "[tuples]")
{
    GIVEN("v1 = vector(3, 2, 1)")
    {
        auto v1 = rtc::vector(3, 2, 1);

        AND_GIVEN("v2 = vector(5, 6, 7)")
        {
            auto v2 = rtc::vector(5, 6, 7);

            THEN("v1 - v2 == vector(-2, -4, -6)")
            {
                REQUIRE(v1 - v2 == rtc::vector(-2, -4, -6));
            }
        }
    }
}

SCENARIO("Subtracting a vector from the zero vector", "[tuples]")
{
    GIVEN("zero = vector(0, 0, 0)")
    {
        auto zero = rtc::vector(0, 0, 0);

        AND_GIVEN("v = vector(1, -2, 3)")
        {
            auto v = rtc::vector(1, -2, 3);

            THEN("zero - v == vector(-1, 2, -3)")
            {
                REQUIRE(zero - v == rtc::vector(-1, 2, -3));
            }
        }
    }
}

SCENARIO("Negating a tuple", "[tuples]")
{
    GIVEN("a = tuple(1, -2, 3, -4)")
    {
        auto a = rtc::tuple4_t{1, -2, 3, -4};

        THEN("-a == tuple(-1, 2, -3, 4)")
        {
            REQUIRE(-a == rtc::tuple4_t{-1, 2, -3, 4});
        }
    }
}

SCENARIO("Multiplying a tuple by a scalar", "[tuples]")
{
    GIVEN("a = tuple(1, -2, 3, -4)")
    {
        auto a = rtc::tuple4_t{1, -2, 3, -4};

        THEN("a * 3.5 = tuple(3.5, -7, 10.5, -14)")
        {
            REQUIRE(a * 3.5f == rtc::tuple4_t{3.5f, -7, 10.5f, -14});
        }
    }
}

SCENARIO("Multiplying a tuple by a fraction", "[tuples]")
{
    GIVEN("a = tuple(1, -2, 3, -4)")
    {
        auto a = rtc::tuple4_t{1, -2, 3, -4};

        THEN("a * 0.5 == tuple(0.5, -1, 1.5, -2)")
        {
            REQUIRE(a * 0.5f == rtc::tuple4_t{0.5f, -1, 1.5f, -2});
        }
    }
}

SCENARIO("Dividing a tuple by a scalar", "[tuples]")
{
    GIVEN("a = tuple(1, -2, 3, -4)")
    {
        auto a = rtc::tuple4_t{1, -2, 3, -4};

        THEN("a / 2 == tuple(0.5, -1, 1.5, -2)")
        {
            REQUIRE(a / 2 == rtc::tuple4_t{0.5, -1, 1.5, -2});
        }
    }
}

SCENARIO("Computing the magnitude of vector(1, 0, 0)", "[tuples]")
{
    GIVEN("v = vector(1, 0, 0)")
    {
        auto v = rtc::vector(1, 0, 0);

        THEN("magnitude(v) == 1") { REQUIRE(rtc::magnitude(v) == 1.0_a); }
    }
}

SCENARIO("Computing the magnitude of vector(0, 1, 0)", "[tuples]")
{
    GIVEN("v = vector(0, 1, 0)")
    {
        auto v = rtc::vector(0, 1, 0);

        THEN("magnitude(v) == 1") { REQUIRE(rtc::magnitude(v) == 1.0_a); }
    }
}

SCENARIO("Computing the magnitude of vector(0, 0, 1)", "[tuples]")
{
    GIVEN("v = vector(0, 0, 1)")
    {
        auto v = rtc::vector(0, 0, 1);

        THEN("magnitude(v) == 1") { REQUIRE(rtc::magnitude(v) == 1.0_a); }
    }
}

SCENARIO("Computing the magnitude of vector(1, 2, 3)", "[tuples]")
{
    GIVEN("v = vector(1, 2, 3)")
    {
        auto v = rtc::vector(1, 2, 3);

        THEN("magnitude(v) == sqrt(14)")
        {
            REQUIRE(rtc::magnitude(v) == Approx(std::sqrtf(14)));
        }
    }
}

SCENARIO("Computing the magnitude of vector(-1, -2, -3)", "[tuples]")
{
    GIVEN("v = vector(-1, -2, -3)")
    {
        auto v = rtc::vector(-1, -2, -3);

        THEN("magnitude(v) == sqrt(14)")
        {
            REQUIRE(rtc::magnitude(v) == Approx(std::sqrtf(14)));
        }
    }
}

SCENARIO("Normalizing vector(4, 0, 0) gives (1, 0, 0)", "[tuples]")
{
    GIVEN("v = vector(4, 0, 0)")
    {
        auto v = rtc::vector(4, 0, 0);

        THEN("normalize(v) == vector(1, 0, 0)")
        {
            REQUIRE(rtc::normalize(v) == rtc::vector(1, 0, 0));
        }
    }
}

SCENARIO("Normalizing vector(1, 2, 3)", "[tuples]")
{
    GIVEN("v = vector(1, 2, 3)")
    {
        auto v = rtc::vector(1, 2, 3);

        THEN("normalize(v) == approximately vector(0.26726, 0.53452,0.80178)")
        {
            REQUIRE(rtc::normalize(v)
                    == rtc::tuple4_t{0.26726f, 0.53452f, 0.80178f});
        }
    }
}

SCENARIO("The magnitude of a normalized vector", "[tuples]")
{
    GIVEN("v = vector(1, 2, 3)")
    {
        auto v = rtc::vector(1, 2, 3);

        WHEN("norm = normalize(v)")
        {
            auto norm = rtc::normalize(v);

            THEN("magnitude(norm) == 1") { REQUIRE(rtc::magnitude(norm) == 1.0_a); }
        }
    }
}

SCENARIO("The dot product of two tuples", "[tuples]")
{
    GIVEN("a = vector(1, 2, 3)")
    {
        auto a = rtc::vector(1, 2, 3);

        AND_GIVEN("b = vector(2, 3, 4)")
        {
            auto b = rtc::vector(2, 3, 4);

            THEN("dot(a, b) == 20") { REQUIRE(rtc::dot(a, b) == 20.0_a); }
        }
    }
}

SCENARIO("The cross product of two vectors", "[tuples]")
{
    GIVEN("a = vector(1, 2, 3)")
    {
        auto a = rtc::vector(1, 2, 3);

        AND_GIVEN("b = vector(2, 3, 4)")
        {
            auto b = rtc::vector(2, 3, 4);

            THEN("cross(a, b) == vector(-1, 2, -1)")
            {
                REQUIRE(rtc::cross(a, b) == rtc::vector(-1, 2, -1));
            }

            AND_THEN("cross(b, a) == vector(1, -2, 1)")
            {
                REQUIRE(rtc::cross(b, a) == rtc::vector(1, -2, 1));
            }
        }
    }
}

SCENARIO("Colors are (red, green, blue) tuples", "[tuples]")
{
    GIVEN("c = color(-0.5, 0.4, 1.7)")
    {
        auto c = rtc::color(-0.5f, 0.4f, 1.7f);

        THEN("c.red == -0.5") { REQUIRE(c.red == -0.5_a); }
        AND_THEN("c.green == 0.4") { REQUIRE(c.green == 0.4_a); }
        AND_THEN("c.blue = 1.7") { REQUIRE(c.blue == 1.7_a); }
    }
}

SCENARIO("Adding colors", "[tuples]")
{
    GIVEN("c1 = color(0.9, 0.6, 0.75)")
    {
        auto c1 = rtc::color(0.9f, 0.6f, 0.75f);

        AND_GIVEN("c2 = color(0.7, 0.1, 0.25)")
        {
            auto c2 = rtc::color(0.7f, 0.1f, 0.25f);

            THEN("c1 + c2 == color(1.6, 0.7, 1.0)")
            {
                REQUIRE(c1 + c2 == rtc::color(1.6f, 0.7f, 1.0f));
            }
        }
    }
}

SCENARIO("Subtracting colors", "[tuples]")
{
    GIVEN("c1 = color(0.9, 0.6, 0.75)")
    {
        auto c1 = rtc::color(0.9f, 0.6f, 0.75f);

        AND_GIVEN("c2 = color(0.7, 0.1, 0.25)")
        {
            auto c2 = rtc::color(0.7f, 0.1f, 0.25f);

            THEN("c1 - c2 == color(0.2, 0.5, 0.5)")
            {
                REQUIRE(c1 - c2 == rtc::color(0.2f, 0.5f, 0.5f));
            }
        }
    }
}

SCENARIO("Multiplying a color by a scalar", "[tuples]")
{
    GIVEN("c = color(0.2, 0.3, 0.4)")
    {
        auto c = rtc::color(0.2f, 0.3f, 0.4f);

        THEN("c * 2 == color(0.4, 0.6, 0.8)")
        {
            REQUIRE(c * 2 == rtc::color(0.4f, 0.6f, 0.8f));
        }
    }
}

SCENARIO("Multiplying colors", "[tuples]")
{
    GIVEN("c1 = color(1, 0.2, 0.4)")
    {
        auto c1 = rtc::color(1, 0.2f, 0.4f);

        AND_GIVEN("c2 = color(0.9, 1, 0.1)")
        {
            auto c2 = rtc::color(0.9f, 1, 0.1f);

            THEN("c1 * c2 == color(0.9, 0.2, 0.04)")
            {
                REQUIRE(c1 * c2 == rtc::color(0.9f, 0.2f, 0.04f));
            }
        }
    }
}

SCENARIO("Reflecting a vector approaching at 45 degrees", "[tuples]")
{
    GIVEN("v = vector(1, -1, 0)")
    {
        auto v = rtc::vector(1, -1, 0);

        AND_GIVEN("n = vector(0, 1, 0)")
        {
            auto n = rtc::vector(0, 1, 0);

            WHEN("r = reflect(v, n)")
            {
                auto r = rtc::reflect(v, n);

                THEN("r == vector(1, 1, 0)") { REQUIRE(r == rtc::vector(1, 1, 0)); }
            }
        }
    }
}

SCENARIO("Reflecting a vector off a slanted surface", "[tuples]")
{
    GIVEN("v = vector(0, -1, 0)")
    {
        auto v = rtc::vector(0, -1, 0);

        AND_GIVEN("n = vector(sqrt(2)/2, sqrt(2)/2, 0)")
        {
            auto n = rtc::vector(std::sqrtf(2) / 2, std::sqrtf(2) / 2, 0);

            WHEN("r = reflect(v, n)")
            {
                auto r = rtc::reflect(v, n);

                THEN("r == vector(1, 0, 0)") { REQUIRE(r == rtc::vector(1, 0, 0)); }
            }
        }
    }
}
