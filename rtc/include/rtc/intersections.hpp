
#ifndef RTC_INTERSECTIONS_HPP_
#define RTC_INTERSECTIONS_HPP_

#include "sphere.hpp"

#include <algorithm>
#include <optional>
#include <vector>

namespace rtc {

struct intersection_t {
    float    t;
    sphere_t object;

    friend bool operator==(const intersection_t& l,
                           const intersection_t& r) noexcept
    {
        return l.t == r.t && l.object == r.object;
    }
};

using intersections_t = std::vector<intersection_t>;

[[nodiscard]] inline intersections_t intersect(const sphere_t& sphere,
                                               const ray_t&    ray)
{
    auto sphere_to_ray = ray.origin - rtc::point(0, 0, 0);

    auto a = rtc::dot(ray.direction, ray.direction);
    auto b = 2 * rtc::dot(ray.direction, sphere_to_ray);
    auto c = rtc::dot(sphere_to_ray, sphere_to_ray) - 1;

    auto discriminant = (b * b) - (4 * a * c);

    intersections_t intersections = {};

    if (discriminant >= 0) {
        auto t1 = (-b - std::sqrtf(discriminant)) / (2 * a);
        auto t2 = (-b + std::sqrtf(discriminant)) / (2 * a);

        intersections.push_back({t1, sphere});
        intersections.push_back({t2, sphere});
    }

    return intersections;
}

[[nodiscard]] inline std::optional<intersection_t>
hit(intersections_t intersections)
{
    std::sort(intersections.begin(),
              intersections.end(),
              [](const auto& l, const auto& r) { return l.t < r.t; });

    auto const_iter = std::upper_bound(
        intersections.begin(),
        intersections.end(),
        0,
        [](const auto& val, const auto& element) { return element.t > val; });

    std::optional<intersection_t> intersection;

    if (const_iter != intersections.end()) {
        intersection = *const_iter;
    }

    return intersection;
}

} // namespace rtc

#endif // RTC_INTERSECTIONS_HPP_
