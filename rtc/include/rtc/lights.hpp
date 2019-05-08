
#ifndef RTC_LIGHTS_HPP_
#define RTC_LIGHTS_HPP_

#include "tuple.hpp"

namespace rtc {

struct point_light_t {
    tuple4_t position;
    tuple4_t intensity;

    friend bool operator==(const point_light_t& a, const point_light_t& b) noexcept
    {
        return a.position == b.position && a.intensity == b.intensity;
    }
};

} // namespace rtc

#endif // RTC_LIGHTS_HPP_
