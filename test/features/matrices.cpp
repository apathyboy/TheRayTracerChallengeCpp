
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

SCENARIO("Constructing and inspecting a 2x2 matrix", "[matrices]")
{
    GIVEN(
        "The following 2x2 matrix M:\n"
        "| -3 |  5 |\n"
        "|  1 | -2 |")
    {
        auto M = rtc::matrix2x2_t{-3, 5, 1, -2};

        THEN("M[0,0] == -3") { REQUIRE(M[0][0] == -3_a); }
        AND_THEN("M[0,1] == 5") { REQUIRE(M[0][1] == 5_a); }
        AND_THEN("M[1,0] == 1") { REQUIRE(M[1][0] == 1_a); }
        AND_THEN("M[1,1] == -2") { REQUIRE(M[1][1] == -2_a); }
    }
}

SCENARIO("Constructing and inspecting a 3x3 matrix", "[matrices]")
{
    GIVEN(
        "The following 3x3 matrix M:\n"
        "| -3 |  5 |  0 |\n"
        "|  1 | -2 | -7 |\n"
        "|  0 |  1 |  1 |")
    {
        auto M = rtc::matrix3x3_t{-3, 5, 0, 1, -2, -7, 0, 1, 1};

        THEN("M[0,0] == -3") { REQUIRE(M[0][0] == -3_a); }
        THEN("M[1,1] == -2") { REQUIRE(M[1][1] == -2_a); }
        THEN("M[2,2] == 1") { REQUIRE(M[2][2] == 1_a); }
    }
}

SCENARIO("Matrix equality with identical matrices", "[matrices]")
{
    GIVEN(
        "The following matrix A:\n"
        "| 1 | 2 | 3 | 4 |\n"
        "| 5 | 6 | 7 | 8 |\n"
        "| 9 | 8 | 7 | 6 |\n"
        "| 5 | 4 | 3 | 2 |")
    {
        // clang-format off
        auto A = rtc::matrix4x4_t{1, 2, 3, 4,
                                  5, 6, 7, 8,
                                  9, 8, 7, 6,
                                  5, 4, 3, 2};
        // clang-format on

        AND_GIVEN(
            "The following matrix B:\n"
            "| 1 | 2 | 3 | 4 |\n"
            "| 5 | 6 | 7 | 8 |\n"
            "| 9 | 8 | 7 | 6 |\n"
            "| 5 | 4 | 3 | 2 |")
        {
            // clang-format off
            auto B = rtc::matrix4x4_t{1, 2, 3, 4,
                                      5, 6, 7, 8,
                                      9, 8, 7, 6,
                                      5, 4, 3, 2};
            // clang-format on

            THEN("A == B") { REQUIRE(A == B); }
        }
    }
}

SCENARIO("Matrix equality with different matrices", "[matrices]")
{
    GIVEN(
        "the following matrix A:\n"
        "| 1 | 2 | 3 | 4 |\n"
        "| 5 | 6 | 7 | 8 |\n"
        "| 9 | 8 | 7 | 6 |\n"
        "| 5 | 4 | 3 | 2 |")
    {
        // clang-format off
        auto A = rtc::matrix4x4_t{1, 2, 3, 4,
                                  5, 6, 7, 8,
                                  9, 8, 7, 6,
                                  5, 4, 3, 2};
        // clang-format on
        AND_GIVEN(
            "the following matrix B:\n"
            "| 2 | 3 | 4 | 5 |\n"
            "| 6 | 7 | 8 | 9 |\n"
            "| 8 | 7 | 6 | 5 |\n"
            "| 4 | 3 | 2 | 1 |")
        {
            // clang-format off
            auto B = rtc::matrix4x4_t{2, 3, 4, 5,
                                      6, 7, 8, 9,
                                      8, 7, 6, 5,
                                      4, 3, 2, 1};
            // clang-format on

            THEN("A != B") { REQUIRE(A != B); }
        }
    }
}

SCENARIO("Multiplying two matrices", "[matrices]")
{
    GIVEN(
        "The following matrix A:\n"
        "| 1 | 2 | 3 | 4 |\n"
        "| 5 | 6 | 7 | 8 |\n"
        "| 9 | 8 | 7 | 6 |\n"
        "| 5 | 4 | 3 | 2 |")
    {
        // clang-format off
        auto A = rtc::matrix4x4_t{1, 2, 3, 4,
                                  5, 6, 7, 8,
                                  9, 8, 7, 6,
                                  5, 4, 3, 2};
        // clang-format on

        AND_GIVEN(
            "The following matrix B:\n"
            "| -2 | 1 | 2 |  3 |\n"
            "|  3 | 2 | 1 | -1 |\n"
            "|  4 | 3 | 6 |  5 |\n"
            "|  1 | 2 | 7 |  8 |")
        {
            // clang-format off
            auto B = rtc::matrix4x4_t{-2, 1, 2, 3,
                                      3, 2, 1, -1,
                                      4, 3, 6, 5,
                                      1, 2, 7, 8};
            // clang-format on

            THEN(
                "A * B is the following 4x4 matrix\n"
                "| 20 |  22 |  50 |  48 |\n"
                "| 44 |  54 | 114 | 108 |\n"
                "| 40 |  58 | 110 | 102 |\n"
                "| 16 |  26 |  46 |  42 |")
            {
                // clang-format off
                auto C = rtc::matrix4x4_t{20, 22, 50, 48,
                                          44, 54, 114, 108,
                                          40, 58, 110, 102,
                                          16, 26, 46, 42};
                // clang-format on

                REQUIRE(A * B == C);
            }
        }
    }
}

SCENARIO("A matrix multiplied by a tuple", "[matrices]")
{
    GIVEN(
        "the following matrix A:\n"
        "| 1 | 2 | 3 | 4 |\n"
        "| 2 | 4 | 4 | 2 |\n"
        "| 8 | 6 | 4 | 1 |\n"
        "| 0 | 0 | 0 | 1 ")
    {
        // clang-format off
        auto A = rtc::matrix4x4_t{1, 2, 3, 4,
                                  2, 4, 4, 2,
                                  8, 6, 4, 1,
                                  0, 0, 0, 1};
        // clang-format on

        AND_GIVEN("b = tuple(1, 2, 3, 1)")
        {
            auto b = rtc::tuple4_t{1, 2, 3, 1};

            THEN("A * b  = tuple(18, 24, 33, 1)")
            {
                REQUIRE(A * b == rtc::tuple4_t{18, 24, 33, 1});
            }
        }
    }
}
