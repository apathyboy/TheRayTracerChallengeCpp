
#include <rtc/lights.hpp>
#include <rtc/tuple.hpp>

#include <catch2/catch.hpp>

SCENARIO("A point light has a position and intensity", "[lights]")
{
    GIVEN("intensity = color(1, 1, 1)")
    {
        auto intensity = rtc::color(1, 1, 1);

        AND_GIVEN("position = point(0, 0, 0)")
        {
            auto position = rtc::point(0, 0, 0);

            WHEN("light = point_light(position, intensity)")
            {
                auto light = rtc::point_light_t{position, intensity};

                THEN("light.position == position")
                {
                    REQUIRE(light.position == position);
                }
                AND_THEN("light.intensity == intensity")
                {
                    REQUIRE(light.intensity == intensity);
                }
            }
        }
    }
}
