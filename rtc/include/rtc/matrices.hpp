
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

    friend bool operator==(const matrix2x2_t& a, const matrix2x2_t& b) noexcept
    {
        bool equal = true;

        for (int i = 0; i < row_count && equal; ++i) {
            equal = a[i] == b[i];
        }

        return equal;
    }

    friend bool operator!=(const matrix2x2_t& a, const matrix2x2_t& b) noexcept
    {
        return !(a == b);
    }
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

    friend bool operator==(const matrix3x3_t& a, const matrix3x3_t& b) noexcept
    {
        bool equal = true;

        for (int i = 0; i < row_count && equal; ++i) {
            equal = a[i] == b[i];
        }

        return equal;
    }

    friend bool operator!=(const matrix3x3_t& a, const matrix3x3_t& b) noexcept
    {
        return !(a == b);
    }
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

    friend bool operator==(const matrix4x4_t& a, const matrix4x4_t& b) noexcept
    {
        bool equal = true;

        for (int i = 0; i < row_count && equal; ++i) {
            equal = a[i] == b[i];
        }

        return equal;
    }

    friend bool operator!=(const matrix4x4_t& a, const matrix4x4_t& b) noexcept
    {
        return !(a == b);
    }

    friend matrix4x4_t operator*(const matrix4x4_t& a,
                                 const matrix4x4_t& b) noexcept
    {
        matrix4x4_t result = {};

        for (int row = 0; row < row_count; ++row) {
            for (int col = 0; col < col_count; ++col) {
                result[row][col] = a[row][0] * b[0][col] + a[row][1] * b[1][col]
                                   + a[row][2] * b[2][col] + a[row][3] * b[3][col];
            }
        }

        return result;
    }

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
[[nodiscard]] MatrixT transpose(const MatrixT& a) noexcept
{
    MatrixT result = {};

    for (int row = 0; row < MatrixT::row_count; ++row) {
        for (int col = 0; col < MatrixT::col_count; ++col) {
            result[col][row] = a[row][col];
        }
    }

    return result;
}

[[nodiscard]] inline float determinant(const matrix2x2_t& a) noexcept
{
    return a[0][0] * a[1][1] - a[0][1] * a[1][0];
}

template <typename FromMatrixT, typename ToMatrixT>
[[nodiscard]] ToMatrixT
submatrix(const FromMatrixT& a, int exclusion_row, int exclusion_col) noexcept
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

[[nodiscard]] inline matrix2x2_t
submatrix(const matrix3x3_t& a, int exclusion_row, int exclusion_col) noexcept
{
    return submatrix<matrix3x3_t, matrix2x2_t>(a, exclusion_row, exclusion_col);
}

[[nodiscard]] inline matrix3x3_t
submatrix(const matrix4x4_t& a, int exclusion_row, int exclusion_col) noexcept
{
    return submatrix<matrix4x4_t, matrix3x3_t>(a, exclusion_row, exclusion_col);
}

template <typename MatrixT>
float cofactor(const MatrixT& a, int exclusion_row, int exclusion_col) noexcept
{
    auto minor = rtc::minor(a, exclusion_row, exclusion_col);

    if ((exclusion_row + exclusion_col) % 2 != 0) {
        minor = -minor;
    }

    return minor;
}

template <typename MatrixT>
[[nodiscard]] float determinant(const MatrixT& a) noexcept
{
    float det = 0;

    for (int col = 0; col < MatrixT::col_count; ++col) {
        det = det + a[0][col] * rtc::cofactor(a, 0, col);
    }

    return det;
}

template <typename MatrixT>
inline float minor(const MatrixT& a, int exclusion_row, int exclusion_col) noexcept
{
    return rtc::determinant(rtc::submatrix(a, exclusion_row, exclusion_col));
}

inline bool is_invertible(const matrix4x4_t& a)
{
    return !rtc::approx(rtc::determinant(a), 0);
}

inline matrix4x4_t inverse(const matrix4x4_t& a)
{
    if (!rtc::is_invertible(a))
        return a;

    auto det = rtc::determinant(a);

    matrix4x4_t tmp = {};

    for (int row = 0; row < matrix4x4_t::row_count; ++row) {
        for (int col = 0; col < matrix4x4_t::col_count; ++col) {
            auto c = rtc::cofactor(a, row, col);

            tmp[col][row] = c / det;
        }
    }

    return tmp;
}

} // namespace rtc

#endif // RTC_MATRICES_HPP_
