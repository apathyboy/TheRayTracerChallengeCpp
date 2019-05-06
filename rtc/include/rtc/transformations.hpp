
#ifndef RTC_TRANSFORMATIONS_HPP_
#define RTC_TRANSFORMATIONS_HPP_

#include "matrices.hpp"

namespace rtc {

[[nodiscard]] inline matrix4x4_t translation(float x, float y, float z) noexcept
{
    // clang-format off
    return {1, 0, 0, x,
            0, 1, 0, y,
            0, 0, 1, z,
            0, 0, 0, 1};
    // clang-format on
}

[[nodiscard]] inline matrix4x4_t scaling(float x, float y, float z) noexcept
{
    // clang-format off
    return {x, 0, 0, 0,
            0, y, 0, 0,
            0, 0, z, 0,
            0, 0, 0, 1};
    // clang-format on
}

[[nodiscard]] inline matrix4x4_t rotation_x(float radians)
{
    // clang-format off
    return {1, 0, 0, 0,
            0, std::cosf(radians), -std::sinf(radians), 0,
            0, std::sinf(radians), std::cosf(radians), 0,
            0, 0, 0, 1};
    // clang-format on
}

[[nodiscard]] inline matrix4x4_t rotation_y(float radians)
{
    // clang-format off
    return {std::cosf(radians), 0, std::sinf(radians), 0,
            0, 1, 0, 0,
            -std::sinf(radians), 0, std::cosf(radians), 0,
            0, 0, 0, 1};
    // clang-format on
}

[[nodiscard]] inline matrix4x4_t rotation_z(float radians)
{
    // clang-format off
    return {std::cosf(radians), -std::sinf(radians), 0, 0,
            std::sinf(radians), std::cosf(radians), 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1};
    // clang-format on
}

[[nodiscard]] inline matrix4x4_t
shearing(float x_y, float x_z, float y_x, float y_z, float z_x, float z_y) noexcept
{
    // clang-format off
    return {  1, x_y, x_z, 0,
            y_x,   1, y_z, 0,
            z_x, z_y,   1, 0,
              0,   0,   0, 1};
    // clang-format on
}

} // namespace rtc

#endif // RTC_TRANSFORMATIONS_HPP_
