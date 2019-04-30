
#include <rtc/canvas.hpp>

#include <rtc/canvas.hpp>

#include <catch2/catch.hpp>

using namespace Catch::literals;

SCENARIO("Creating a canvas", "[canvas]")
{
    GIVEN("c = canvas(10, 20)")
    {
        auto c = rtc::canvas_t{10, 20};

        THEN("c.width = 10") { REQUIRE(c.width() == 10.0_a); }
        AND_THEN("c.height = 20") { REQUIRE(c.height() == 20.0_a); }
        AND_THEN("every pixel of c is color(0, 0, 0)")
        {
            auto black = rtc::color(0, 0, 0);

            for (uint32_t y = 0; y < c.height(); ++y) {
                for (uint32_t x = 0; x < c.width(); ++x) {
                    REQUIRE(c.pixel_at(x, y) == black);
                }
            }
        }
    }
}

SCENARIO("Writing pixels to a canvas", "[canvas]")
{
    GIVEN("c = canvas(10, 20)")
    {
        auto c = rtc::canvas_t{10, 20};

        AND_GIVEN("red = color(1, 0, 0)")
        {
            auto red = rtc::color(1, 0, 0);

            WHEN("write_pixel(c, 2, 3, red)")
            {
                c.write_pixel(2, 3, red);

                THEN("pixel_at(c, 2, 3) == red")
                {
                    REQUIRE(c.pixel_at(2, 3) == red);
                }
            }
        }
    }
}
