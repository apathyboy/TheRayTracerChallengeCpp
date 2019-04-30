
#ifndef RTC_CANVAS_HPP_
#define RTC_CANVAS_HPP_

#include "tuple.hpp"

#include <cstdint>
#include <vector>

namespace rtc {

class canvas_t {
    uint32_t width_;
    uint32_t height_;

    std::vector<tuple_t> pixels_;

public:
    canvas_t(uint32_t width, uint32_t height)
        : width_{width}
        , height_{height}
    {
        pixels_.resize(width_ * height_);
    }

    [[nodiscard]] uint32_t width() const noexcept { return width_; }
    [[nodiscard]] uint32_t height() const noexcept { return height_; }

    [[nodiscard]] tuple_t pixel_at(uint32_t x, uint32_t y) const {
        return pixels_.at(width_ * y + x);
    }

    void write_pixel(uint32_t x, uint32_t y, tuple_t color) noexcept
    {
        pixels_.at(width_ * y + x) = color;
    }
};

} // namespace rtc

#endif // RTC_CANVAS_HPP_
