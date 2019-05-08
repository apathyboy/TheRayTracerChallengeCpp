
#ifndef RTC_SPHERE_HPP_
#define RTC_SPHERE_HPP_

#include "materials.hpp"
#include "matrices.hpp"
#include "ray.hpp"

#include <cstdint>
#include <vector>

namespace rtc {

struct sphere_t {
    uint32_t    id;
    matrix4x4_t transform;
    material_t  material;

    friend bool operator==(const sphere_t& a, const sphere_t& b) noexcept
    {
        return a.transform == b.transform && a.material == b.material;
    }
};

[[nodiscard]] inline sphere_t sphere() noexcept
{
    static uint32_t next_id = 0;

    return sphere_t{next_id++, matrix4x4_t::identity(), rtc::material()};
}

[[nodiscard]] inline tuple4_t normal_at(const sphere_t& sphere,
                                        const tuple4_t& point)
{
    (sphere);
    auto object_point  = rtc::inverse(sphere.transform) * point;
    auto object_normal = object_point - rtc::point(0, 0, 0);

    auto world_normal = rtc::transpose(rtc::inverse(sphere.transform))
                        * object_normal;
    world_normal.w = 0;

    return rtc::normalize(world_normal);
}

} // namespace rtc

#endif // RTC_SPHERE_HPP_
