
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

SCENARIO("Constructing the BMP pixel data")
{
    GIVEN("c = canvas(5, 3)")
    {
        auto c = rtc::canvas_t{5, 3};

        AND_GIVEN("c1 = color(1.5, 0, 0)")
        {
            auto c1 = rtc::color(1.5f, 0, 0);

            AND_GIVEN("c2 = color(0, 0.5, 0)")
            {
                auto c2 = rtc::color(0, 0.5f, 0);

                AND_GIVEN("c3 = color(-0.5, 0, 1)")
                {
                    auto c3 = rtc::color(-0.5, 0, 1);

                    WHEN("write_pixel(c, 0, 0, c1)")
                    {
                        c.write_pixel(0, 0, c1);

                        AND_WHEN("write_pixel(c, 2, 1, c2)")
                        {
                            c.write_pixel(2, 1, c2);

                            AND_WHEN("write_pixel(c, 4, 2, c3)")
                            {
                                c.write_pixel(4, 2, c3);

                                AND_WHEN("bmp = canvas_to_bmp(c)")
                                {
                                    auto bmp = rtc::canvas_to_bmp(c);

                                    THEN("bmp.data at offset 0 is 255")
                                    {
                                        REQUIRE(bmp.data[0] == 255);
                                    }
                                    AND_THEN("bmp.data at offset 29 is 128")
                                    {
                                        REQUIRE(bmp.data[29] == 128);
                                    }
                                    AND_THEN("bmp.data at offset 58 is 255")
                                    {
                                        REQUIRE(bmp.data[58] == 255);
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

SCENARIO("Construct the BMP file header", "[canvas]")
{
    GIVEN("c = canvas(5, 3)")
    {
        auto c = rtc::canvas_t{5, 3};

        AND_GIVEN("bmp = canvas_to_bmp(c)")
        {
            auto bmp = rtc::canvas_to_bmp(c);

            WHEN("bmp_file_header = file_header_from_bmp(bmp)")
            {
                auto bmp_file_header = rtc::file_header_from_bmp(bmp);

                THEN("bmp_file_header.type == BM")
                {
                    REQUIRE(bmp_file_header.type == 'BM');
                }
                AND_THEN("bmp_file_header.size == 104")
                {
                    REQUIRE(bmp_file_header.size == 114);
                }
                AND_THEN("bmp_file_header.reserved1 == 0")
                {
                    REQUIRE(bmp_file_header.reserved1 == 0);
                }
                AND_THEN("bmp_file_header.reserved2 == 0")
                {
                    REQUIRE(bmp_file_header.reserved2 == 0);
                }
                AND_THEN("bmp_file_header.off_bits == 54")
                {
                    REQUIRE(bmp_file_header.off_bits == 54);
                }
            }
        }
    }
}
