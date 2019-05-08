
#ifndef RTC_MATERIALS_HPP_
#define RTC_MATERIALS_HPP_

#include "tuple.hpp"

namespace rtc {

struct material_t {
    rtc::tuple4_t color;
    float         ambient;
    float         diffuse;
    float         specular;
    float         shininess;
};

[[nodiscard]] inline material_t material() noexcept
{
    return {rtc::color(1, 1, 1), 0.1f, 0.9f, 0.9f, 200.f};
}

} // namespace rtc

#endif // RTC_MATERIALS_HPP_
