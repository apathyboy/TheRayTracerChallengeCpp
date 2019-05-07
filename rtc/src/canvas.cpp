
#include <rtc/canvas.hpp>

#include <algorithm>
#include <fstream>

rtc::bitmap_t rtc::canvas_to_bmp(const rtc::canvas_t& canvas)
{
    rtc::bitmap_t bitmap = {};

    bitmap.header.height    = -static_cast<int32_t>(canvas.height());
    bitmap.header.width     = canvas.width();
    bitmap.header.planes    = 1;
    bitmap.header.bit_count = 32;

    bitmap.data.resize(canvas.height() * canvas.width() * sizeof(uint32_t));

    uint32_t pixel_offset = 0;

    for (uint32_t y = 0; y < canvas.height(); ++y) {
        for (uint32_t x = 0; x < canvas.width(); ++x) {
            auto pixel = canvas.pixel_at(x, y);

            bitmap.data[pixel_offset++] = static_cast<uint8_t>(
                std::clamp(std::roundf(255.f * pixel.blue), 0.f, 255.f));
            bitmap.data[pixel_offset++] = static_cast<uint8_t>(
                std::clamp(std::roundf(255.f * pixel.green), 0.f, 255.f));
            bitmap.data[pixel_offset++] = static_cast<uint8_t>(
                std::clamp(std::roundf(255.f * pixel.red), 0.f, 255.f));
            bitmap.data[pixel_offset++] = static_cast<uint8_t>(
                std::clamp(std::roundf(255.f * pixel.alpha), 0.f, 255.f));
        }
    }
    return bitmap;
}

void rtc::write_bmp_to_file(const char* filename, const rtc::bitmap_t& bitmap)
{
    std::ofstream output(filename, std::ios::binary);

    if (output) {
        output.write(reinterpret_cast<const char*>(&bitmap.file_header),
                     sizeof(bitmap.file_header));
        output.write(reinterpret_cast<const char*>(&bitmap.header),
                     sizeof(bitmap.header));
        output.write(reinterpret_cast<const char*>(bitmap.data.data()),
                     bitmap.data.size());
    }
    // else handle an error condition here
}
