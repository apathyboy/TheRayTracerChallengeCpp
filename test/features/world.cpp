
#include <rtc/algorithm.hpp>
#include <rtc/transformations.hpp>
#include <rtc/world.hpp>

#include <catch2/catch.hpp>

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
