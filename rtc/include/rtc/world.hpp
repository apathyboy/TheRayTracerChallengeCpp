
#ifndef RTC_WORLD_HPP_
#define RTC_WORLD_HPP_

#include "intersections.hpp"
#include "lights.hpp"
#include "sphere.hpp"
#include "transformations.hpp"

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

[[nodiscard]] inline tuple4_t shade_hit(const world_t&        world,
                                        const computations_t& computations)
{
    // @todo should world light_source be an optional object, or should
    // there be a default "non" light?
    return rtc::lighting(computations.object.material,
                         *world.light_source,
                         computations.point,
                         computations.eyev,
                         computations.normalv,
                         false);
}

[[nodiscard]] inline tuple4_t color_at(const world_t& world, const ray_t& ray)
{
    tuple4_t color = {};

    auto intersections = rtc::intersect(world, ray);
    auto intersection  = rtc::hit(intersections);

    if (intersection) {
        auto comps = rtc::prepare_computations(*intersection, ray);
        color      = rtc::shade_hit(world, comps);
    }

    return color;
}

[[nodiscard]] inline bool is_shadowed(const world_t& world, const tuple4_t& point)
{
    auto v         = world.light_source->position - point;
    auto distance  = rtc::magnitude(v);
    auto direction = rtc::normalize(v);

    auto r             = rtc::ray_t{point, direction};
    auto intersections = rtc::intersect(world, r);

    auto h = rtc::hit(intersections);

    return (h && h->t < distance);
}

} // namespace rtc

#endif // RTC_WORLD_HPP_
