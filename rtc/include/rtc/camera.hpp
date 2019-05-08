
#ifndef RTC_CAMERA_HPP_
#define RTC_CAMERA_HPP_

#include "canvas.hpp"
#include "matrices.hpp"
#include "ray.hpp"
#include "world.hpp"

#include <cstdint>

namespace rtc {

class camera_t {
private:
    uint32_t    width_         = 0;
    uint32_t    height_        = 0;
    float       half_width_    = 0;
    float       half_height_   = 0;
    float       field_of_view_ = 0;
    float       pixel_size_    = 0;
    matrix4x4_t transform_     = matrix4x4_t::identity();

public:
    camera_t() = default;
    camera_t(uint32_t width, uint32_t height, float field_of_view)
        : width_{width}
        , height_{height}
        , field_of_view_{field_of_view}
    {
        calculate_pixel_size();
    }

    uint32_t width() const noexcept { return width_; }
    uint32_t height() const noexcept { return height_; }

    float half_width() const noexcept { return half_width_; }
    float half_height() const noexcept { return half_height_; }

    float              field_of_view() const noexcept { return field_of_view_; }
    float              pixel_size() const noexcept { return pixel_size_; }
    const matrix4x4_t& transform() const noexcept { return transform_; }
    void               transform(matrix4x4_t new_transform) noexcept
    {
        transform_ = std::move(new_transform);
    }

private:
    void calculate_pixel_size()
    {
        auto half_view = std::tanf(field_of_view_ / 2);
        auto aspect    = static_cast<float>(width_) / static_cast<float>(height_);

        if (aspect >= 1) {
            half_width_  = half_view;
            half_height_ = half_view / aspect;
        }
        else {
            half_width_  = half_view * aspect;
            half_height_ = half_view;
        }

        pixel_size_ = (half_width_ * 2) / static_cast<float>(width_);
    }
};

[[nodiscard]] inline ray_t ray_for_pixel(const camera_t& camera, int x, int y)
{
    auto xoffset = (x + 0.5f) * camera.pixel_size();
    auto yoffset = (y + 0.5f) * camera.pixel_size();

    auto world_x = camera.half_width() - xoffset;
    auto world_y = camera.half_height() - yoffset;

    auto camera_inverse_transform = rtc::inverse(camera.transform());

    auto pixel     = camera_inverse_transform * rtc::point(world_x, world_y, -1);
    auto origin    = camera_inverse_transform * rtc::point(0, 0, 0);
    auto direction = rtc::normalize(pixel - origin);

    return {origin, direction};
}

[[nodiscard]] inline canvas_t render(const camera_t& camera, const world_t& world)
{
    (world);
    auto image = rtc::canvas_t{camera.width(), camera.height()};

    for (uint32_t y = 0; y < camera.height(); ++y) {
        for (uint32_t x = 0; x < camera.width(); ++x) {
            auto ray   = rtc::ray_for_pixel(camera, x, y);
            auto color = rtc::color_at(world, ray);
            image.write_pixel(x, y, color);
        }
    }

    return image;
}

} // namespace rtc

#endif // RTC_CAMERA_HPP_
