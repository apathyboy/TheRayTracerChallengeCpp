
#ifndef RTC_WORLD_HPP_
#define RTC_WORLD_HPP_

#include "intersections.hpp"
#include "lights.hpp"
#include "sphere.hpp"

#include <optional>
#include <vector>

namespace rtc {

struct world_t {
    std::vector<sphere_t>        objects;
    std::optional<point_light_t> light_source;
};

[[nodiscard]] inline world_t default_world() noexcept
{
    world_t world;

    world.light_source = rtc::point_light_t{rtc::point(-10, 10, -10),
                                            rtc::color(1, 1, 1)};

    auto s1              = rtc::sphere();
    s1.material.color    = rtc::color(0.8f, 1.f, 0.6f);
    s1.material.diffuse  = 0.7f;
    s1.material.specular = 0.2f;

    auto s2      = rtc::sphere();
    s2.transform = rtc::scaling(0.5f, 0.5f, 0.5f);

    world.objects.push_back(s1);
    world.objects.push_back(s2);

    return world;
}

[[nodiscard]] inline intersections_t intersect(const world_t& world,
                                               const ray_t&   ray)
{
    intersections_t intersections;

    for (const auto& obj : world.objects) {
        auto tmp = rtc::intersect(obj, ray);
        intersections.reserve(intersections.size() + tmp.size());
        intersections.insert(intersections.end(), tmp.begin(), tmp.end());
    }

    std::sort(intersections.begin(),
              intersections.end(),
              [](const auto& a, const auto& b) noexcept { return a.t < b.t; });

    return intersections;
}

} // namespace rtc

#endif // RTC_WORLD_HPP_
