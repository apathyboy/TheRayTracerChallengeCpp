
#include <rtc/camera.hpp>
#include <rtc/math.hpp>
#include <rtc/matrices.hpp>
#include <rtc/transformations.hpp>
#include <rtc/world.hpp>

#include <catch2/catch.hpp>

using namespace Catch::literals;

SCENARIO("Constructing a camera", "[camera]")
{
    GIVEN("width = 160")
    {
        uint32_t width = 160;

        AND_GIVEN("height = 120")
        {
            uint32_t height = 120;

            AND_GIVEN("field_of_view = PI / 2")
            {
                float field_of_view = rtc::PI / 2;

                WHEN("c = camera(width, height, field_of_view)")
                {
                    auto c = rtc::camera_t{width, height, field_of_view};

                    THEN("c.width == 160") { REQUIRE(c.width() == width); }
                    AND_THEN("c.height == 120") { REQUIRE(c.height() == height); }
                    AND_THEN("c.field_of_view = PI/2")
                    {
                        REQUIRE(rtc::approx(c.field_of_view(), rtc::PI / 2));
                    }
                    AND_THEN("c.transform == identity_matrix")
                    {
                        c.transform() == rtc::matrix4x4_t::identity();
                    }
                }
            }
        }
    }
}

SCENARIO("The pixel size for a horizontal canvas", "[camera]")
{
    GIVEN("c = camera(200, 125, PI/2)")
    {
        auto c = rtc::camera_t{200, 125, rtc::PI / 2};

        THEN("c.pixel_size == 0.01") { REQUIRE(c.pixel_size() == 0.01_a); }
    }
}

SCENARIO("Constructing a ray through the center of the canvas", "[camera]")
{
    GIVEN("c = camera(201, 101, PI/2)")
    {
        auto c = rtc::camera_t{201, 101, rtc::PI / 2};

        WHEN("r = ray_for_pixel(c, 100, 50)")
        {
            auto r = rtc::ray_for_pixel(c, 100, 50);

            THEN("r.origin == point(0, 0, 0)")
            {
                REQUIRE(r.origin == rtc::point(0, 0, 0));
            }
            AND_THEN("r.direction == vector(0, 0, -1)")
            {
                REQUIRE(r.direction == rtc::vector(0, 0, -1));
            }
        }
    }
}

SCENARIO("Constructing a ray through a corner of the canvas", "[camera]")
{
    GIVEN("c = camera(201, 101, PI/2)")
    {
        auto c = rtc::camera_t{201, 101, rtc::PI / 2};

        WHEN("r = ray_for_pixel(c, 0, 0)")
        {
            auto r = rtc::ray_for_pixel(c, 0, 0);

            THEN("r.origin == point(0, 0, 0)")
            {
                REQUIRE(r.origin == rtc::point(0, 0, 0));
            }
            AND_THEN("r.direction == vector(0.66519, 0.33259, -0.66851)")
            {
                REQUIRE(r.direction == rtc::vector(0.66519f, 0.33259f, -0.66851f));
            }
        }
    }
}

SCENARIO("Constructing a ray  when the camera is transformed", "[camera]")
{
    GIVEN("c = camera(201, 101, PI/2)")
    {
        auto c = rtc::camera_t{201, 101, rtc::PI / 2};

        WHEN("c.transform = rotation_y(PI/4) * translation(0, -2, 5)")
        {
            c.transform(rtc::rotation_y(rtc::PI / 4) * rtc::translation(0, -2, 5));

            AND_WHEN("r = ray_for_pixel(c, 100, 50)")
            {
                auto r = rtc::ray_for_pixel(c, 100, 50);

                THEN("r.origin == point(0, 2, -5)")
                {
                    REQUIRE(r.origin == rtc::point(0, 2, -5));
                }
                AND_THEN("r.direction == vector(sqrt(2)/2, 0, -sqrt(2)/2)")
                {
                    REQUIRE(
                        r.direction
                        == rtc::vector(std::sqrtf(2) / 2, 0, -std::sqrtf(2) / 2));
                }
            }
        }
    }
}

SCENARIO("Rendering a world with a camera", "[camera]")
{
    GIVEN("w = default_world()")
    {
        auto w = rtc::default_world();

        AND_GIVEN("c = camera(11, 11, PI/2)")
        {
            auto c = rtc::camera_t{11, 11, rtc::PI / 2};

            AND_GIVEN("from = point(0, 0, -5)")
            {
                auto from = rtc::point(0, 0, -5);

                AND_GIVEN("to = point(0, 0, 0)")
                {
                    auto to = rtc::point(0, 0, 0);

                    AND_GIVEN("up = vector(0, 1, 0)")
                    {
                        auto up = rtc::vector(0, 1, 0);

                        AND_GIVEN("c.transform = view_transform(from, to, up)")
                        {
                            c.transform(rtc::view_transform(from, to, up));

                            WHEN("image = render(c, w)")
                            {
                                auto image = rtc::render(c, w);

                                THEN(
                                    "pixel_at(image, 5, 5) == color(0.38066, "
                                    "0.47583, 0.2855")
                                {
                                    REQUIRE(
                                        image.pixel_at(5, 5)
                                        == rtc::color(0.38066f, 0.47583f, 0.2855f));
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
