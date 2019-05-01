
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

struct bitmap_header_t {
    const uint32_t size = sizeof(bitmap_header_t);
    int32_t        width;
    int32_t        height;
    uint16_t       planes;
    uint16_t       bit_count;
    uint32_t       compression;
    uint32_t       size_image;
    int32_t        x_pels_per_meter;
    int32_t        y_pels_per_meter;
    uint32_t       clr_used;
    uint32_t       clr_important;
};

struct bitmap_t {
    bitmap_header_t header;
};

inline bitmap_t canvas_to_bmp(const canvas_t& canvas)
{
    bitmap_t bitmap = {};

    bitmap.header.height    = canvas.height();
    bitmap.header.width     = canvas.width();
    bitmap.header.planes    = 1;
    bitmap.header.bit_count = 32;

    return bitmap;
}

} // namespace rtc

#endif // RTC_CANVAS_HPP_
