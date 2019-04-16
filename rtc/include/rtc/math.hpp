
#ifndef RTC_MATH_HPP_
#define RTC_MATH_HPP_

#include <cmath>

namespace rtc {

static constexpr float PI      = 3.1415927f;
static constexpr float PI_4    = PI / 4.f;
static constexpr float PI_3    = PI / 3.f;
static constexpr float PI_2    = PI / 2.f;
static constexpr float EPSILON = 0.00001f;

[[nodiscard]] inline bool equal(float a, float b) noexcept
{
    return std::fabs(a - b) < EPSILON;
}

} // namespace rtc

#endif // RTC_MATH_HPP_
