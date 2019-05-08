
#ifndef RTC_SPHERE_HPP_
#define RTC_SPHERE_HPP_

#include "matrices.hpp"
#include "ray.hpp"

#include <cstdint>
#include <vector>

namespace rtc {

struct sphere_t {
    uint32_t    id;
    matrix4x4_t transform;

    friend bool operator==(const sphere_t& l, const sphere_t& r) noexcept
    {
        return l.id == r.id && l.transform == r.transform;
    }
};

[[nodiscard]] inline sphere_t sphere() noexcept
{
    static uint32_t next_id = 0;

    return sphere_t{next_id++, matrix4x4_t::identity()};
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
