
#ifndef RTC_MATERIALS_HPP_
#define RTC_MATERIALS_HPP_

#include "lights.hpp"
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

[[nodiscard]] inline tuple4_t lighting(const material_t&    material,
                                       const point_light_t& light,
                                       const tuple4_t&      position,
                                       const tuple4_t&      eyev,
                                       const tuple4_t&      normalv)
{
    auto effective_color  = material.color * light.intensity;
    auto lightv           = rtc::normalize(light.position - position);
    auto ambient          = effective_color * material.ambient;
    auto light_dot_normal = rtc::dot(lightv, normalv);

    tuple4_t diffuse  = {};
    tuple4_t specular = {};

    if (light_dot_normal >= 0) {
        diffuse = effective_color * material.diffuse * light_dot_normal;

        auto reflectv        = rtc::reflect(-lightv, normalv);
        auto reflect_dot_eye = rtc::dot(reflectv, eyev);

        if (reflect_dot_eye > 0) {
            auto factor = std::powf(reflect_dot_eye, material.shininess);
            specular    = light.intensity * material.specular * factor;
        }
    }

    return ambient + diffuse + specular;
}

} // namespace rtc

#endif // RTC_MATERIALS_HPP_
