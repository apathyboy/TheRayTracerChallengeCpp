
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

    auto canvas          = rtc::canvas_t{canvas_pixels, canvas_pixels};
    auto shape           = rtc::sphere();
    shape.material.color = rtc::color(1.f, 0.2f, 1.f);

    auto light_position = rtc::point(-10.f, 10.f, -10.f);
    auto light_color    = rtc::color(1.f, 1.f, 1.f);
    auto light          = rtc::point_light_t{light_position, light_color};

    for (uint32_t y = 0; y < canvas.height(); ++y) {
        auto world_y = half - pixel_size * y;

        for (uint32_t x = 0; x < canvas.width(); ++x) {
            auto world_x = -half + pixel_size * x;

            auto endpoint = rtc::point(world_x, world_y, wall_z);

            auto ray = rtc::ray_t{ray_origin,
                                  rtc::normalize(endpoint - ray_origin)};
            auto xs  = rtc::intersect(shape, ray);
            auto hit = rtc::hit(xs);

            if (hit) {
                auto point  = rtc::position(ray, hit->t);
                auto normal = rtc::normal_at(hit->object, point);
                auto eye    = -ray.direction;

                auto color = rtc::lighting(
                    hit->object.material, light, point, eye, normal);

                canvas.write_pixel(x, y, color);
            }
        }
    }

    rtc::write_bmp_to_file("chapter6.bmp", rtc::canvas_to_bmp(canvas));

    return 0;
}
