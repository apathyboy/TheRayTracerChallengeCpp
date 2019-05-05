
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

SCENARIO("Multiplying a matrix by the identity matrix", "[matrices]")
{
    GIVEN(
        "the following matrix A:\n"
        "| 0 | 1 |  2 |  4 |\n"
        "| 1 | 2 |  4 |  8 |\n"
        "| 2 | 4 |  8 | 16 |\n"
        "| 4 | 8 | 16 | 32 |")
    {
        // clang-format off
        auto A = rtc::matrix4x4_t{1, 2, 3, 4,
                                  1, 2, 4, 8,
                                  2, 4, 8, 16,
                                  4, 8, 16, 32};
        // clang-format on

        THEN("A * identity_matrix == A")
        {
            REQUIRE(A * rtc::matrix4x4_t::identity() == A);
        }
    }
}

SCENARIO("Transposing a matrix", "[matrices]")
{
    GIVEN(
        "the following matrix A:\n"
        "| 0 | 9 | 3 | 0 |\n"
        "| 9 | 8 | 0 | 8 |\n"
        "| 1 | 8 | 5 | 3 |\n"
        "| 0 | 0 | 5 | 8 |\n")
    {
        // clang-format off
        auto A = rtc::matrix4x4_t{0, 9, 3, 0,
                                  9, 8, 0, 8,
                                  1, 8, 5, 3,
                                  0, 0, 5, 8};
        // clang-format on

        THEN(
            "transpose(A) is the following matrix:\n"
            "| 0 | 9 | 1 | 0 |\n"
            "| 9 | 8 | 0 | 8 |\n"
            "| 1 | 8 | 5 | 3 |\n"
            "| 0 | 0 | 5 | 8 |\n")
        {
            // clang-format off
            auto B = rtc::matrix4x4_t{0, 9, 1, 0,
                                      9, 8, 8, 0,
                                      3, 0, 5, 5,
                                      0, 8, 3, 8};
            // clang-format on

            REQUIRE(rtc::transpose(A) == B);
        }
    }
}

SCENARIO("Transposing the identity matrix", "[matrices]")
{
    GIVEN("A = transpose(identity_matrix)")
    {
        auto A = rtc::transpose(rtc::matrix4x4_t::identity());
        THEN("A = identity_matrix") { REQUIRE(A == rtc::matrix4x4_t::identity()); }
    }
}

SCENARIO("Calculating the determinant of a 2x2 matrix", "[matrices]")
{
    GIVEN(
        "the following 2x2 matrix A:\n"
        "|  1 | 5 |\n"
        "| -3 | 2 |")
    {
        auto A = rtc::matrix2x2_t{1, 5, -3, 2};

        THEN("determinant(A) == 17") { REQUIRE(rtc::determinant(A) == 17_a); }
    }
}

SCENARIO("A submatrix of a 3x3 matrix is a 2x2 matrix", "[matrices]")
{
    GIVEN(
        "the following 3x3 matrix A:\n"
        "|  1 | 5 |  0 |\n"
        "| -3 | 2 |  7 |\n"
        "|  0 | 6 | -3 |")
    {
        auto A = rtc::matrix3x3_t{1, 5, 0, -3, 2, 7, 0, 6, -3};

        THEN(
            "submatrix(A, 0, 2) is the following 2x2 matrix:\n"
            "| -3 | 2 |\n"
            "|  0 | 6 |\n")
        {
            REQUIRE(rtc::submatrix(A, 0, 2) == rtc::matrix2x2_t{-3, 2, 0, 6});
        }
    }
}

SCENARIO("A submatrix of a 4x4 matrix is a 3x3 matrix", "[matrices]")
{
    GIVEN(
        "the following 4x4 matrix A:\n"
        "| -6 |  1 |  1 |  6 |\n"
        "| -8 |  5 |  8 |  6 |\n"
        "| -1 |  0 |  8 |  2 |\n"
        "| -7 |  1 | -1 |  1 |")
    {
        // clang-format off
        auto A = rtc::matrix4x4_t{-6, 1, 1, 6,
                                  -8, 5, 8, 6,
                                  -1, 0, 8, 2,
                                  -7, 1, -1, 1};
        // clang-format on

        THEN(
            "submatrix(A, 2, 1) is the following 3x3 matrix:\n"
            "| -6 |  1 | 6 |\n"
            "| -8 |  8 | 6 |\n"
            "| -7 | -1 | 1 |")
        {
            REQUIRE(rtc::submatrix(A, 2, 1)
                    == rtc::matrix3x3_t{-6, 1, 6, -8, 8, 6, -7, -1, 1});
        }
    }
}

SCENARIO("Calculating a minor of a 3x3 matrix", "[matrices]")
{
    GIVEN(
        "the following 3x3 matrix A:\n"
        "|  3 |  5 |  0 |\n"
        "|  2 | -1 | -7 |\n"
        "|  6 | -1 |  5 |")
    {
        auto A = rtc::matrix3x3_t{3, 5, 0, 2, -1, -7, 6, -1, 5};

        AND_GIVEN("B = submatrix(A, 1, 0)")
        {
            auto B = rtc::submatrix(A, 1, 0);

            THEN("determinant(B) == 25")
            {
                REQUIRE(rtc::determinant(B) == 25_a);

                AND_THEN("minor(A, 1, 0) == 25")
                {
                    REQUIRE(rtc::minor(A, 1, 0) == 25_a);
                }
            }
        }
    }
}
