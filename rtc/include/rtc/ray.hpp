
#ifndef RTC_RAY_HPP_
#define RTC_RAY_HPP_

#include "tuple.hpp"

namespace rtc {

struct ray_t {
    tuple4_t origin;
    tuple4_t direction;
};

[[nodiscard]] inline tuple4_t position(const ray_t& ray, float t) noexcept
{
    return ray.origin + ray.direction * t;
}

} // namespace rtc

#endif // RTC_RAY_HPP_
