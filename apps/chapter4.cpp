
#include <rtc/canvas.hpp>
#include <rtc/transformations.hpp>

int main()
{
    auto canvas = rtc::canvas_t(500, 500);
    auto color  = rtc::color(1.f, 1.f, 1.f);

    auto translation = rtc::translation(
        canvas.width() / 2.f, canvas.height() / 2.f, 0.f);
    auto scaling = rtc::scaling(
        canvas.width() * (3.f / 8.f), canvas.height() * (3.f / 8.f), 0.f);

    auto twelve = rtc::point(0, 1, 0);

    for (int i = 0; i < 12; ++i) {
        auto rotation = rtc::rotation_z(i * (rtc::PI / 6));

        auto hour = translation * scaling * rotation * twelve;

        uint32_t x = static_cast<uint32_t>(std::roundf(hour.x));
        uint32_t y = static_cast<uint32_t>(std::roundf(canvas.height() - hour.y));

        if (x < canvas.width() && y < canvas.height()) {
            canvas.write_pixel(x, y, color);
        }
    }

    rtc::write_bmp_to_file("chapter4.bmp", rtc::canvas_to_bmp(canvas));

    return 0;
}
