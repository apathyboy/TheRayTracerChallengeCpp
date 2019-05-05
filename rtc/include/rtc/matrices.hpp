
#ifndef RTC_MATRICES_HPP_
#define RTC_MATRICES_HPP_

#include "tuple.hpp"

#include <memory>

namespace rtc {

class matrix2x2_t {
public:
    constexpr static int row_count = 2;
    constexpr static int col_count = 2;

private:
    tuple4_t rows_[row_count] = {};

public:
    matrix2x2_t() = default;

    // clang-format off
    matrix2x2_t(float val0_0, float val0_1,
                float val1_0, float val1_1) noexcept
        : rows_{{val0_0, val0_1},
                {val1_0, val1_1}}
    {}
    // clang-format on

    const tuple4_t& operator[](int index) const { return rows_[index]; }
    tuple4_t&       operator[](int index) { return rows_[index]; }
};

class matrix3x3_t {
public:
    constexpr static int row_count = 3;
    constexpr static int col_count = 3;

private:
    tuple4_t rows_[row_count] = {};

public:
    matrix3x3_t() = default;

    // clang-format off
    matrix3x3_t(float val0_0, float val0_1, float val0_2,
                float val1_0, float val1_1, float val1_2,
                float val2_0, float val2_1, float val2_2) noexcept
        : rows_{{val0_0, val0_1, val0_2},
                {val1_0, val1_1, val1_2},
                {val2_0, val2_1, val2_2}}
    {}
    // clang-format on

    const tuple4_t& operator[](int index) const { return rows_[index]; }
    tuple4_t&       operator[](int index) { return rows_[index]; }
};

class matrix4x4_t {
public:
    constexpr static int row_count = 4;
    constexpr static int col_count = 4;

private:
    tuple4_t rows_[row_count] = {};

public:
    matrix4x4_t() = default;

    // clang-format off
    matrix4x4_t(float val0_0, float val0_1, float val0_2, float val0_3,
                float val1_0, float val1_1, float val1_2, float val1_3,
                float val2_0, float val2_1, float val2_2, float val2_3,
                float val3_0, float val3_1, float val3_2, float val3_3) noexcept
        : rows_{{val0_0, val0_1, val0_2, val0_3},
                {val1_0, val1_1, val1_2, val1_3},
                {val2_0, val2_1, val2_2, val2_3},
                {val3_0, val3_1, val3_2, val3_3}}
    {}
    // clang-format on

    static const matrix4x4_t identity() noexcept
    {
        return matrix4x4_t{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    }

    const tuple4_t& operator[](int index) const { return rows_[index]; }
    tuple4_t&       operator[](int index) { return rows_[index]; }

    friend tuple4_t operator*(const matrix4x4_t& a, const tuple4_t& b)
    {
        tuple4_t result = {};

        for (int row = 0; row < row_count; ++row) {
            result[row] = rtc::dot(a.rows_[row], b);
        }

        return result;
    }
};

template <typename MatrixT>
[[nodiscard]] bool operator==(const MatrixT& a, const MatrixT& b) noexcept
{
    bool equal = true;

    for (int i = 0; i < MatrixT::row_count && equal; ++i) {
        equal = a[i] == b[i];
    }

    return equal;
}

template <typename MatrixT>
[[nodiscard]] bool operator!=(const MatrixT& a, const MatrixT& b) noexcept
{
    return !(a == b);
}

template <typename MatrixT>
MatrixT operator*(const MatrixT& a, const MatrixT& b) noexcept
{
    MatrixT result = {};

    for (int row = 0; row < MatrixT::row_count; ++row) {
        for (int col = 0; col < MatrixT::col_count; ++col) {
            result[row][col] = a[row][0] * b[0][col] + a[row][1] * b[1][col]
                               + a[row][2] * b[2][col] + a[row][3] * b[3][col];
        }
    }

    return result;
}

template <typename MatrixT>
MatrixT transpose(const MatrixT& a)
{
    MatrixT result = {};

    for (int row = 0; row < MatrixT::row_count; ++row) {
        for (int col = 0; col < MatrixT::col_count; ++col) {
            result[col][row] = a[row][col];
        }
    }

    return result;
}

inline float determinant(const matrix2x2_t& a)
{
    return a[0][0] * a[1][1] - a[0][1] * a[1][0];
}

template <typename FromMatrixT, typename ToMatrixT>
ToMatrixT submatrix(const FromMatrixT& a, int exclusion_row, int exclusion_col)
{
    ToMatrixT result = {};

    for (int r = 0, r1 = 0; r < FromMatrixT::row_count; ++r) {
        if (r == exclusion_row)
            continue;

        for (int c = 0, c1 = 0; c < FromMatrixT::col_count; ++c) {
            if (c == exclusion_col)
                continue;

            result[r1][c1] = a[r][c];

            ++c1;
        }

        ++r1;
    }

    return result;
}

inline matrix2x2_t
submatrix(const matrix3x3_t& a, int exclusion_row, int exclusion_col)
{
    return submatrix<matrix3x3_t, matrix2x2_t>(a, exclusion_row, exclusion_col);
}

inline matrix3x3_t
submatrix(const matrix4x4_t& a, int exclusion_row, int exclusion_col)
{
    return submatrix<matrix4x4_t, matrix3x3_t>(a, exclusion_row, exclusion_col);
}

} // namespace rtc

#endif // RTC_MATRICES_HPP_
