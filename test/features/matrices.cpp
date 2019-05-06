
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

SCENARIO("Calculating a cofactor of a 3x3 matrix", "[matrices]")
{
    GIVEN(
        "the following 3x3 matrix A:\n"
        "|  3 |  5 |  0 |\n"
        "|  2 | -1 | -7 |\n"
        "|  6 | -1 |  5 |")
    {
        auto A = rtc::matrix3x3_t{3, 5, 0, 2, -1, -7, 6, -1, 5};

        THEN("minor(A, 0, 0) == -12")
        {
            REQUIRE(rtc::minor(A, 0, 0) == -12_a);

            AND_THEN("cofactor(A, 0, 0) == -12")
            {
                REQUIRE(rtc::cofactor(A, 0, 0) == -12_a);
            }
        }

        THEN("minor(A, 1, 0) == 25")
        {
            REQUIRE(rtc::minor(A, 1, 0) == 25_a);

            AND_THEN("cofactor(A, 1, 0) == -25")
            {
                REQUIRE(rtc::cofactor(A, 1, 0) == -25_a);
            }
        }
    }
}

SCENARIO("Calculating the determinant of a 3x3 matrix", "[matrices]")
{
    GIVEN(
        "the following 3x3 matrix A:\n"
        "|  1 |  2 |  6 |\n"
        "| -5 |  8 | -4 |\n"
        "|  2 |  6 |  4 |")
    {
        auto A = rtc::matrix3x3_t{1, 2, 6, -5, 8, -4, 2, 6, 4};

        THEN("cofactor(A, 0, 0) == 56") { REQUIRE(rtc::cofactor(A, 0, 0) == 56_a); }
        AND_THEN("cofactor(A, 0, 1) == 12")
        {
            REQUIRE(rtc::cofactor(A, 0, 1) == 12_a);
        }
        AND_THEN("cofactor(A, 0, 2) == -46")
        {
            REQUIRE(rtc::cofactor(A, 0, 2) == -46_a);
        }
        AND_THEN("determinant(A) == -196") { REQUIRE(determinant(A) == -196_a); }
    }
}

SCENARIO("Calculating the determinant of a 4x4 matrix", "[matrices]")
{
    GIVEN(
        "the following 4x4 matrix A:\n"
        "| -2 | -8 |  3 |  5 |\n"
        "| -3 |  1 |  7 |  3 |\n"
        "|  1 |  2 | -9 |  6 |\n"
        "| -6 |  7 |  7 | -9 |")
    {
        // clang-format off
        auto A = rtc::matrix4x4_t{-2, -8,  3,  5,
                                  -3,  1,  7,  3,
                                   1,  2, -9,  6,
                                  -6,  7,  7, -9};
        // clang-format on

        THEN("cofactor(A, 0, 0,) == 690")
        {
            REQUIRE(rtc::cofactor(A, 0, 0) == 690_a);
        }
        AND_THEN("cofactor(A, 0, 1) == 447")
        {
            REQUIRE(rtc::cofactor(A, 0, 1) == 447_a);
        }
        AND_THEN("cofactor(A, 0, 2) == 210")
        {
            REQUIRE(rtc::cofactor(A, 0, 2) == 210_a);
        }
        AND_THEN("cofactor(A, 0, 3) == 51")
        {
            REQUIRE(rtc::cofactor(A, 0, 3) == 51_a);
        }
        AND_THEN("determinant(A) == -4071")
        {
            REQUIRE(rtc::determinant(A) == -4071_a);
        }
    }
}

SCENARIO("Testing an invertible matrix for invertibility", "[matrices]")
{
    GIVEN(
        "the following 4x4 matrix A:\n"
        "|  6 |  4 |  4 |  4 |\n"
        "|  5 |  5 |  7 |  6 |\n"
        "|  4 | -9 |  3 | -7 |\n"
        "|  9 |  1 |  7 | -6 |")
    {
        // clang-format off
        auto A = rtc::matrix4x4_t{6,  4, 4,  4,
                                  5,  5, 7,  6,
                                  4, -9, 3, -7,
                                  9,  1, 7, -6};
        // clang-format on

        THEN("determinant(A) == -2120")
        {
            REQUIRE(rtc::determinant(A) == -2120_a);

            AND_THEN("A is invertible") { REQUIRE(rtc::is_invertible(A)); }
        }
    }
}

SCENARIO("Testing a noninvertible matrix for invertibility", "[matrices]")
{
    GIVEN(
        "the following 4x4 matrix A:\n"
        "| -4 |  2 | -2 | -3 |\n"
        "|  9 |  6 |  2 |  6 |\n"
        "|  0 | -5 |  1 | -5 |\n"
        "|  0 |  0 |  0 |  0 |")
    {
        // clang-format off
        auto A = rtc::matrix4x4_t{-4,  2, -2, -3,
                                   9,  6,  2,  6,
                                   0, -5,  1, -5,
                                   0,  0,  0,  0};
        // clang-format on

        THEN("determinant(A) == ")
        {
            REQUIRE(rtc::determinant(A) == 0_a);

            AND_THEN("A is not invertible")
            {
                REQUIRE_FALSE(rtc::is_invertible(A));
            }
        }
    }
}

SCENARIO("Calculating the inverse of a matix", "[matrices]")
{
    GIVEN(
        "the following 4x4 matrix A:\n"
        "| -5 |  2 |  6 | -8 |\n"
        "|  1 | -5 |  1 |  8 |\n"
        "|  7 |  7 | -6 | -7 |\n"
        "|  1 | -3 |  7 |  4 |")
    {
        // clang-format off
        auto A = rtc::matrix4x4_t{-5,  2,  6, -8,
                                   1, -5,  1,  8,
                                   7,  7, -6, -7,
                                   1, -3,  7,  4};
        // clang-format on

        AND_GIVEN("B = inverse(A)")
        {
            auto B = rtc::inverse(A);

            THEN("determinant(A) == 532")
            {
                REQUIRE(rtc::determinant(A) == 532_a);

                AND_THEN("cofactor(A, 2, 3) == -160")
                {
                    REQUIRE(rtc::cofactor(A, 2, 3) == -160_a);

                    AND_THEN("B[3,2] == -160/532")
                    {
                        REQUIRE(B[3][2] == -160.f / 532.f);
                    }
                }
                AND_THEN("cofactor(A, 3, 2) == 105")
                {
                    REQUIRE(rtc::cofactor(A, 3, 2) == 105_a);

                    AND_THEN("B[2,3] == 105/532")
                    {
                        REQUIRE(B[2][3] == 105.f / 532.f);
                    }
                }
                AND_THEN(
                    "B is the following 4x4 matrix:\n"
                    "|  0.21805 |  0.45113 |  0.24060 | -0.04511 |\n"
                    "| -0.80827 | -1.45677 | -0.44361 |  0.52068 |\n"
                    "| -0.07895 | -0.22368 | -0.05263 |  0.19737 |\n"
                    "| -0.52256 | -0.81391 | -0.30075 |  0.30639 |")
                {
                    // clang-format off
                    auto C = rtc::matrix4x4_t{ 0.21805f,  0.45113f,  0.24060f, -0.04511f,
                                              -0.80827f, -1.45677f, -0.44361f,  0.52068f,
                                              -0.07895f, -0.22368f, -0.05263f,  0.19737f,
                                              -0.52256f, -0.81391f, -0.30075f,  0.30639f};
                    // clang-format on
                    REQUIRE(B == C);
                }
            }
        }
    }
}

SCENARIO("Calculating the inverse of a second matix", "[matrices]")
{
    GIVEN(
        "the following 4x4 matrix A:\n"
        "|  8 | -5 |  9 |  2 |\n"
        "|  7 |  5 |  6 |  1 |\n"
        "| -6 |  0 |  9 |  6 |\n"
        "| -3 |  0 | -9 | -4 |")
    {
        // clang-format off
        auto A = rtc::matrix4x4_t{ 8, -5,  9,  2,
                                   7,  5,  6,  1,
                                  -6,  0,  9,  6,
                                  -3,  0, -9, -4};
        // clang-format on

        THEN(
            "inverse(A) is the following 4x4 matrix:\n"
            "| -0.15385 | -0.15385 | -0.28205 | -0.53846 |\n"
            "| -0.07692 |  0.12308 |  0.02564 |  0.03077 |\n"
            "|  0.35897 |  0.35897 |  0.43590 |  0.92308 |\n"
            "| -0.69231 | -0.69231 | -0.76923 | -1.92308 |")
        {
            // clang-format off
            auto B = rtc::matrix4x4_t{-0.15385f, -0.15385f, -0.28205f, -0.53846f,
                                      -0.07692f,  0.12308f,  0.02564f,  0.03077f,
                                       0.35897f,  0.35897f,  0.43590f,  0.92308f,
                                      -0.69231f, -0.69231f, -0.76923f, -1.92308f};
            // clang-format on

            REQUIRE(rtc::inverse(A) == B);
        }
    }
}

SCENARIO("Calculating the inverse of a third matix", "[matrices]")
{
    GIVEN(
        "the following 4x4 matrix A:\n"
        "|  9 |  3 |  0 |  9 |\n"
        "| -5 | -2 | -6 | -3 |\n"
        "| -4 |  9 |  6 |  4 |\n"
        "| -7 |  6 |  6 |  2 |")
    {
        // clang-format off
        auto A = rtc::matrix4x4_t{ 9,  3,  0,  9,
                                  -5, -2, -6, -3,
                                  -4,  9,  6,  4,
                                  -7,  6,  6,  2};
        // clang-format on

        THEN(
            "inverse(A) is the following 4x4 matrix:\n"
            "| -0.04074 | -0.07778 |  0.14444 | -0.22222 |\n"
            "| -0.07778 |  0.03333 |  0.36667 | -0.33333 |\n"
            "| -0.02901 | -0.14630 | -0.10926 |  0.12963 |\n"
            "|  0.17778 |  0.06667 | -0.26667 |  0.33333 |")
        {
            // clang-format off
            auto B = rtc::matrix4x4_t{-0.04074f, -0.07778f,  0.14444f, -0.22222f,
                                      -0.07778f,  0.03333f,  0.36667f, -0.33333f,
                                      -0.02901f, -0.14630f, -0.10926f,  0.12963f,
                                       0.17778f,  0.06667f, -0.26667f,  0.33333f};
            // clang-format on

            REQUIRE(rtc::inverse(A) == B);
        }
    }
}

SCENARIO("Multiplying a p roduct by its inverse", "[matrices]")
{
    GIVEN(
        "the following 4x4 matrix A:\n"
        "|  3 | -9 |  7 |  3 |\n"
        "|  3 | -8 |  2 | -9 |\n"
        "| -4 |  4 |  4 |  1 |\n"
        "| -6 |  5 | -1 |  1 |")
    {
        // clang-format off
        auto A = rtc::matrix4x4_t{ 3, -9,  7,  3,
                                   3, -8,  2, -9,
                                  -4,  4,  4,  1,
                                  -6,  5, -1,  1};
        // clang-format on

        AND_GIVEN(
            "the following 4x4 matrix B:\n"
            "|  8 |  2 |  2 |  2 |\n"
            "|  3 | -1 |  7 |  0 |\n"
            "|  7 |  0 |  5 |  4 |\n"
            "|  6 | -2 |  0 |  5 |")
        {
            // clang-format off
            auto B = rtc::matrix4x4_t{8,  2,  2, 2,
                                      3, -1,  7, 0,
                                      7,  0,  5, 4,
                                      6, -2,  0, 5};
            // clang-format on

            AND_GIVEN("C = A * B")
            {
                auto C = A * B;

                THEN("C * inverse(B) == A") { REQUIRE(C * rtc::inverse(B) == A); }
            }
        }
    }
}

SCENARIO("Multiplying by a translation matrix", "[matrices]")
{
    GIVEN("transform = translation(5, -3, 2)")
    {
        auto transform = rtc::translation(5, -3, 2);

        AND_GIVEN("p = point(-3, 4, 5)")
        {
            auto p = rtc::point(-3, 4, 5);

            THEN("transform * p == point(2, 1, 7)")
            {
                REQUIRE(transform * p == rtc::point(2, 1, 7));
            }
        }
    }
}

SCENARIO("Multiplying by teh inverse of a translation matrix", "[matrices]")
{
    GIVEN("transform = translation(5, -3, 2)")
    {
        auto transform = rtc::translation(5, -3, 2);

        AND_GIVEN("inv = inverse(transform)")
        {
            auto inv = rtc::inverse(transform);

            AND_GIVEN("p = point(-3, 4, 5)")
            {
                auto p = rtc::point(-3, 4, 5);

                THEN("inv * p == point(-8, 7, 3)")
                {
                    REQUIRE(inv * p == rtc::point(-8, 7, 3));
                }
            }
        }
    }
}

SCENARIO("Translation does not affect vectors", "[matrices]")
{
    GIVEN("transform = translation(5, -3, 2)")
    {
        auto transform = rtc::translation(5, -3, 2);

        AND_GIVEN("v = vector(-3, 4, 5)")
        {
            auto v = rtc::vector(-3, 4, 5);

            THEN("transform * v == v") { REQUIRE(transform * v == v); }
        }
    }
}
