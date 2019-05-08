
#ifndef RTC_MATERIALS_HPP_
#define RTC_MATERIALS_HPP_

#include "math.hpp"
#include "tuple.hpp"

namespace rtc {

struct material_t {
    rtc::tuple4_t color;
    float         ambient;
    float         diffuse;
    float         specular;
    float         shininess;
};

[[nodiscard]] inline bool operator==(const material_t& a,
                                     const material_t& b) noexcept
{
    return a.color == b.color && rtc::approx(a.ambient, b.ambient)
           && rtc::approx(a.diffuse, b.diffuse)
           && rtc::approx(a.specular, b.specular)
           && rtc::approx(a.shininess, a.shininess);
}

[[nodiscard]] inline material_t material() noexcept
{
    return {rtc::color(1, 1, 1), 0.1f, 0.9f, 0.9f, 200.f};
}

} // namespace rtc

#endif // RTC_MATERIALS_HPP_
