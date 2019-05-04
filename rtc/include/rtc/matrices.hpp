
#ifndef RTC_MATRICES_HPP_
#define RTC_MATRICES_HPP_

#include "tuple.hpp"

#include <memory>

namespace rtc {

class matrix2x2_t {
    constexpr static int row_count = 2;

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

class matrix4x4_t {
    constexpr static int row_count = 4;

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

    const tuple4_t& operator[](int index) const { return rows_[index]; }
    tuple4_t&       operator[](int index) { return rows_[index]; }
};

} // namespace rtc

#endif // RTC_MATRICES_HPP_
