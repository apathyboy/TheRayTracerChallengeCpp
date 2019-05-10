
#include <rtc/materials.hpp>
#include <rtc/matrices.hpp>
#include <rtc/shape.hpp>
#include <rtc/transformations.hpp>

#include <catch2/catch.hpp>

SCENARIO("The default transformation for shape", "[shapes]")
{
    GIVEN("s = test_shape()")
    {
        auto s = rtc::test_shape();

        THEN("s.transform == identity_matrix")
        {
            REQUIRE(s.transform == rtc::matrix4x4_t::identity());
        }
    }
}

SCENARIO("Assigning a transformation to shape", "[shapes]")
{
    GIVEN("s = test_shape()")
    {
        auto s = rtc::test_shape();

        WHEN("set_transform(s, translation(2, 3, 4))")
        {
            s.transform = rtc::translation(2, 3, 4);

            THEN("s.transform == translation(2, 3, 4)")
            {
                REQUIRE(s.transform == rtc::translation(2, 3, 4));
            }
        }
    }
}

SCENARIO("The default material for shape", "[shapes]")
{
    GIVEN("s = test_shape()")
    {
        auto s = rtc::test_shape();

        WHEN("m = s.material")
        {
            auto m = s.material;

            THEN("m == material()") { REQUIRE(m == rtc::material()); }
        }
    }
}

SCENARIO("Assigning a material to shape", "[shapes]")
{
    GIVEN("s = test_shape()")
    {
        auto s = rtc::test_shape();

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
