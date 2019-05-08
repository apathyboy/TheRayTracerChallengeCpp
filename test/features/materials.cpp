
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
