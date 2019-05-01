
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

SCENARIO("Constructing the BMP header", "[canvas]")
{
    GIVEN("c = canvas(5, 3)")
    {
        auto c = rtc::canvas_t{5, 3};

        WHEN("bmp = canvas_to_bmp(c)")
        {
            auto bmp = rtc::canvas_to_bmp(c);

            THEN("bmp.header.size == 40") { REQUIRE(bmp.header.size == 40); }
            AND_THEN("bmp.header.width == 5") { REQUIRE(bmp.header.width == 5); }
            AND_THEN("bmp.header.height == 3") { REQUIRE(bmp.header.height == 3); }
            AND_THEN("bmp.header.planes == 1") { REQUIRE(bmp.header.planes == 1); }
            AND_THEN("bmp.header.bit_count == 32")
            {
                REQUIRE(bmp.header.bit_count == 32);
            }
            AND_THEN("bmp.header.compression == 0")
            {
                REQUIRE(bmp.header.compression == 0);
            }
            AND_THEN("bmp.header.size_image == 0")
            {
                REQUIRE(bmp.header.size_image == 0);
            }
            AND_THEN("bmp.header.x_pels_per_meter == 0")
            {
                REQUIRE(bmp.header.x_pels_per_meter == 0);
            }
            AND_THEN("bmp.header.y_pels_per_meter == 0")
            {
                REQUIRE(bmp.header.y_pels_per_meter == 0);
            }
            AND_THEN("bmp.header.clr_used == 0")
            {
                REQUIRE(bmp.header.clr_used == 0);
            }
            AND_THEN("bmp.header.clr_important == 0")
            {
                REQUIRE(bmp.header.clr_important == 0);
            }
        }
    }
}
