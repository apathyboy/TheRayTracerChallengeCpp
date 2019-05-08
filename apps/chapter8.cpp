
#include <rtc/canvas.hpp>
#include <rtc/camera.hpp>
#include <rtc/sphere.hpp>
#include <rtc/tuple.hpp>
#include <rtc/world.hpp>

int main()
{
    auto world         = rtc::world_t();
    world.light_source = rtc::point_light_t{rtc::point(-10, 10, -10),
                                            rtc::color(1, 1, 1)};

    auto camera = rtc::camera_t(500, 500, rtc::PI / 3);
    camera.transform(rtc::view_transform(
        rtc::point(0, 1.5f, -5), rtc::point(0, 1, 0), rtc::vector(0, 1, 0)));

    auto floor              = rtc::sphere();
    floor.transform         = rtc::scaling(10, 0.01f, 10);
    floor.material          = rtc::material();
    floor.material.color    = rtc::color(1, 0.9f, 0.9f);
    floor.material.specular = 0;

    auto left_wall      = rtc::sphere();
    left_wall.transform = rtc::translation(0, 0, 5) * rtc::rotation_y(-rtc::PI_4)
                          * rtc::rotation_x(rtc::PI_2)
                          * rtc::scaling(10, 0.01f, 10);
    left_wall.material = floor.material;

    auto right_wall      = rtc::sphere();
    right_wall.transform = rtc::translation(0, 0, 5) * rtc::rotation_y(rtc::PI_4)
                           * rtc::rotation_x(rtc::PI_2)
                           * rtc::scaling(10, 0.01f, 10);
    right_wall.material = floor.material;

    auto middle              = rtc::sphere();
    middle.transform         = rtc::translation(-0.5f, 1, 0.5f);
    middle.material          = rtc::material();
    middle.material.color    = rtc::color(0.1f, 1, 0.5f);
    middle.material.diffuse  = 0.7f;
    middle.material.specular = 0.3f;

    auto right      = rtc::sphere();
    right.transform = rtc::translation(1.5f, 0.5f, -0.5f)
                      * rtc::scaling(0.5f, 0.5f, 0.5f);
    right.material          = rtc::material();
    right.material.color    = rtc::color(0.5f, 1, 0.1f);
    right.material.diffuse  = 0.7f;
    right.material.specular = 0.3f;

    auto left      = rtc::sphere();
    left.transform = rtc::translation(-1.5f, 0.33f, -0.75f)
                     * rtc::scaling(0.33f, 0.33f, 0.33f);
    left.material          = rtc::material();
    left.material.color    = rtc::color(1.f, 0.8f, 0.1f);
    left.material.diffuse  = 0.7f;
    left.material.specular = 0.3f;

    world.objects.push_back(floor);
    world.objects.push_back(left_wall);
    world.objects.push_back(right_wall);
    world.objects.push_back(middle);
    world.objects.push_back(right);
    world.objects.push_back(left);

    auto canvas = rtc::render(camera, world);

    rtc::write_bmp_to_file("chapter8.bmp", rtc::canvas_to_bmp(canvas));

    return 0;
}
