
#include <rtc/lights.hpp>
#include <rtc/materials.hpp>
#include <rtc/tuple.hpp>

#include <catch2/catch.hpp>

SCENARIO("The default material", "[materials]")
{
    GIVEN("m = material()")
    {
        auto m = rtc::material_t{};

        THEN("m.color = color(1, 1, 1)") {}
        AND_THEN("m.ambient == 0.1") {}
        AND_THEN("m.diffuse == 0.9") {}
        AND_THEN("m.specular == 0.9") {}
        AND_THEN("m.shininess == 200.0") {}
    }
}

SCENARIO("Lighting with eye between light and surface", "[materials]")
{
    GIVEN("m = material()")
    {
        auto m = rtc::material();

        AND_GIVEN("position = point(0, 0, 0)")
        {
            auto position = rtc::point(0, 0, 0);

            AND_GIVEN("eyev = vector(0, 0, -1)")
            {
                auto eyev = rtc::vector(0, 0, -1);

                AND_GIVEN("normalv = vector(0, 0, -1)")
                {
                    auto normalv = rtc::vector(0, 0, -1);

                    AND_GIVEN(
                        "light = point_light(point(0, 0, -10), color(1, 1, 1))")
                    {
                        auto light = rtc::point_light_t{rtc::point(0, 0, -10),
                                                        rtc::color(1, 1, 1)};

                        WHEN("result = lighting(m, light, position, eyev, normalv)")
                        {
                            auto result = rtc::lighting(
                                m, light, position, eyev, normalv);

                            THEN("result == color(1.9, 1.9, 1.9)")
                            {
                                REQUIRE(result == rtc::color(1.9f, 1.9f, 1.9f));
                            }
                        }
                    }
                }
            }
        }
    }
}

SCENARIO("Lighting with eye between light and surface, eye offset 45 degrees",
         "[materials]")
{
    GIVEN("m = material()")
    {
        auto m = rtc::material();

        AND_GIVEN("position = point(0, 0, 0)")
        {
            auto position = rtc::point(0, 0, 0);

            AND_GIVEN("eyev = vector(0, sqrt(2)/2, -sqrt(2)/2)")
            {
                auto eyev = rtc::vector(0, std::sqrtf(2) / 2, -std::sqrtf(2) / 2);

                AND_GIVEN("normalv = vector(0, 0, -1)")
                {
                    auto normalv = rtc::vector(0, 0, -1);

                    AND_GIVEN(
                        "light = point_light(point(0, 0, -10), color(1, 1, 1))")
                    {
                        auto light = rtc::point_light_t{rtc::point(0, 0, -10),
                                                        rtc::color(1, 1, 1)};

                        WHEN("result = lighting(m, light, position, eyev, normalv)")
                        {
                            auto result = rtc::lighting(
                                m, light, position, eyev, normalv);

                            THEN("result = color(1.0, 1.0, 1.0)")
                            {
                                REQUIRE(result == rtc::color(1.f, 1.f, 1.f));
                            }
                        }
                    }
                }
            }
        }
    }
}

SCENARIO("Lighting with eye opposite surface, light offest 45 degrees",
         "[materials]")
{
    GIVEN("m = material()")
    {
        auto m = rtc::material();

        AND_GIVEN("position = point(0, 0, 0)")
        {
            auto position = rtc::point(0, 0, 0);

            AND_GIVEN("eyev = vector(0, 0, -1)")
            {
                auto eyev = rtc::vector(0, 0, -1);

                AND_GIVEN("normalv = vector(0, 0, -1)")
                {
                    auto normalv = rtc::vector(0, 0, -1);

                    AND_GIVEN(
                        "light = point_light(point(0, 10, -10), color(1, 1, 1))")
                    {
                        auto light = rtc::point_light_t{rtc::point(0, 10, -10),
                                                        rtc::color(1, 1, 1)};

                        WHEN("result = lighting(m, light, position, eyev, normalv)")
                        {
                            auto result = rtc::lighting(
                                m, light, position, eyev, normalv);

                            THEN("result == color(0.7364, 0.7364, 0.7364)")
                            {
                                REQUIRE(result
                                        == rtc::color(0.7364f, 0.7364f, 0.7364f));
                            }
                        }
                    }
                }
            }
        }
    }
}

SCENARIO("Lighting with eye in the path of the reflection vector", "[materials]")
{
    GIVEN("m = material()")
    {
        auto m = rtc::material();

        AND_GIVEN("position = point(0, 0, 0)")
        {
            auto position = rtc::point(0, 0, 0);

            AND_GIVEN("eyev = vector(0, -sqrt(2)/2, -sqrt(2)/2)")
            {
                auto eyev = rtc::vector(0, -std::sqrtf(2) / 2, -std::sqrtf(2) / 2);

                AND_GIVEN("normalv = vector(0, 0, -1)")
                {
                    auto normalv = rtc::vector(0, 0, -1);

                    AND_GIVEN(
                        "light = point_light(point(0, 10, -10), color(1, 1, 1))")
                    {
                        auto light = rtc::point_light_t{rtc::point(0, 10, -10),
                                                        rtc::color(1, 1, 1)};

                        WHEN("result = lighting(m, light, position, eyev, normalv)")
                        {
                            auto result = rtc::lighting(
                                m, light, position, eyev, normalv);

                            THEN("result = color(1.6364, 1.6364, 1.6364)")
                            {
                                REQUIRE(result
                                        == rtc::color(1.6364f, 1.6364f, 1.6364f));
                            }
                        }
                    }
                }
            }
        }
    }
}

SCENARIO("Lighting with the light behind the surface", "[materials]")
{
    GIVEN("m = material()")
    {
        auto m = rtc::material();

        AND_GIVEN("position = point(0, 0, 0)")
        {
            auto position = rtc::point(0, 0, 0);

            AND_GIVEN("eyev = vector(0, 0, -1)")
            {
                auto eyev = rtc::vector(0, 0, -1);

                AND_GIVEN("normalv = vector(0, 0, -1)")
                {
                    auto normalv = rtc::vector(0, 0, -1);

                    AND_GIVEN(
                        "light = point_light(point(0, 0, 10), color(1, 1, 1))")
                    {
                        auto light = rtc::point_light_t{rtc::point(0, 0, 10),
                                                        rtc::color(1, 1, 1)};

                        WHEN("result = lighting(m, light, position, eyev, normalv)")
                        {
                            auto result = rtc::lighting(
                                m, light, position, eyev, normalv);

                            THEN("result == color(0.1, 0.1, 0.1)")
                            {
                                REQUIRE(result == rtc::color(0.1f, 0.1f, 0.1f));
                            }
                        }
                    }
                }
            }
        }
    }
}
