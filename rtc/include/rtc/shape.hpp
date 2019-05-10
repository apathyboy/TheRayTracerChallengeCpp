
#ifndef RTC_SHAPE_HPP_
#define RTC_SHAPE_HPP_

#include "intersections.hpp"
#include "matrices.hpp"
#include "materials.hpp"
#include "ray.hpp"

namespace rtc {

struct shape_t {
    matrix4x4_t transform;
    material_t  material;
};

[[nodiscard]] inline shape_t test_shape() noexcept
{
    return {matrix4x4_t::identity(), rtc::material()};
}

[[nodiscard]] inline intersections_t intersect(const shape_t& shape,
                                               const ray_t&   ray)
{
    (shape, ray);
    return {};
}

} // namespace rtc

#endif // RTC_SHAPE_HPP_
