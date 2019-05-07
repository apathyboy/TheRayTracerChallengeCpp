
#ifndef RTC_SPHERE_HPP_
#define RTC_SPHERE_HPP_

#include "ray.hpp"

#include <cstdint>
#include <vector>

namespace rtc {

struct sphere_t {
    uint32_t id;
};

[[nodiscard]] inline sphere_t sphere() noexcept
{
    static uint32_t next_id = 0;

    return sphere_t{next_id++};
}

[[nodiscard]] inline std::vector<float> intersect(const sphere_t& sphere,
                                                  const ray_t&    ray)
{
    (sphere);
    auto sphere_to_ray = ray.origin - rtc::point(0, 0, 0);

    auto a = rtc::dot(ray.direction, ray.direction);
    auto b = 2 * rtc::dot(ray.direction, sphere_to_ray);
    auto c = rtc::dot(sphere_to_ray, sphere_to_ray) - 1;

    auto discriminant = (b * b) - (4 * a * c);

    std::vector<float> intersections = {};

    if (discriminant >= 0) {
        auto t1 = (-b - std::sqrtf(discriminant)) / (2 * a);
        auto t2 = (-b + std::sqrtf(discriminant)) / (2 * a);

        intersections.push_back(t1);
        intersections.push_back(t2);
    }

    return intersections;
}

} // namespace rtc

#endif // RTC_SPHERE_HPP_
