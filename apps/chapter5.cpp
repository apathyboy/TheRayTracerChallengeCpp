
#include <rtc/canvas.hpp>
#include <rtc/intersections.hpp>
#include <rtc/sphere.hpp>
#include <rtc/tuple.hpp>

int main()
{
    auto  ray_origin = rtc::point(0.f, 0.f, -5.f);
    float wall_z     = 10.f;
    float wall_size  = 7.f;

    uint32_t canvas_pixels = 500;
    auto     pixel_size    = wall_size / canvas_pixels;
    auto     half          = wall_size / 2.f;

    auto canvas    = rtc::canvas_t(canvas_pixels, canvas_pixels);
    auto hit_color = rtc::color(1.f, 0.f, 0.f);
    auto shape     = rtc::sphere();

    // shrink the shape along the y axis
    // shape.transform = rtc::scaling(1.f, 0.5f, 1.f);

    // shrink the shape along the x axis
    // shape.transform = rtc::scaling(0.5f, 1.f, 1.f);

    // shrink the shape and rotate it
    // shape.transform = rtc::rotation_z(rtc::PI_4) * rtc::scaling(0.5f, 1.f, 1.f);

    // shrink the shape and skew it
    // shape.transform = rtc::shearing(1.f, 0.f, 0.f, 0.f, 0.f, 0.f) *
    // rtc::scaling(0.5f, 1.f, 1.f);

    for (uint32_t y = 0; y < canvas.height(); ++y) {
        auto world_y = half - pixel_size * y;

        for (uint32_t x = 0; x < canvas.width(); ++x) {
            auto world_x = -half + pixel_size * x;

            auto endpoint = rtc::point(world_x, world_y, wall_z);

            auto ray = rtc::ray_t{ray_origin,
                                  rtc::normalize(endpoint - ray_origin)};
            auto xs  = rtc::intersect(shape, ray);

            if (rtc::hit(xs)) {
                canvas.write_pixel(x, y, hit_color);
            }
        }
    }

    rtc::write_bmp_to_file("chapter5.bmp", rtc::canvas_to_bmp(canvas));

    return 0;
}
