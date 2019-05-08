
#ifndef RTC_LIGHTS_HPP_
#define RTC_LIGHTS_HPP_

#include "tuple.hpp"

namespace rtc {

struct point_light_t {
    tuple4_t position;
    tuple4_t intensity;
};

} // namespace rtc

#endif // RTC_LIGHTS_HPP_
