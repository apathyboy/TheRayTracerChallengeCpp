
#include <rtc/matrices.hpp>

#include <catch2/catch.hpp>

using namespace Catch::literals;

SCENARIO("Constructing and inspecting a 4x4 matrix", "[matrices]")
{
    GIVEN(
        "The following 4x4 matrix M:\n"
        "|  1   |  2   |  3   |  4   |\n"
        "|  5.5 |  6.5 |  7.5 |  8.5 |\n"
        "|  9   | 10   | 11   | 12   |\n"
        "| 13.5 | 14.5 | 15.5 | 16.5 |")
    {
        // clang-format off
        auto M = rtc::matrix4x4_t{1, 2, 3, 4,
                                  5.5f, 6.5f, 7.5f, 8.5f,
                                  9, 10, 11, 12,
                                  13.5f, 14.5f, 15.5f, 16.5f};
        // clang-format on

        THEN("M[0,0] == 1") { REQUIRE(M[0][0] == 1_a); }
        AND_THEN("M[0,3] == 4") { REQUIRE(M[0][3] == 4_a); }
        AND_THEN("M[1,0] == 5.5") { REQUIRE(M[1][0] == 5.5_a); }
        AND_THEN("M[1,2] == 7.5") { REQUIRE(M[1][2] == 7.5_a); }
        AND_THEN("M[2,2] == 11") { REQUIRE(M[2][2] == 11_a); }
        AND_THEN("M[3,0] == 13.5") { REQUIRE(M[3][0] == 13.5_a); }
        AND_THEN("M[3,2] == 15.5") { REQUIRE(M[3][2] == 15.5_a); }
    }
}