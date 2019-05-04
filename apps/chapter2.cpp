
#include <rtc/canvas.hpp>
#include <rtc/tuple.hpp>

struct projectile_t {
    rtc::tuple4_t position;
    rtc::tuple4_t velocity;
};

struct environment_t {
    rtc::tuple4_t gravity;
    rtc::tuple4_t wind;
};

[[nodiscard]] static projectile_t tick(const environment_t& env,
                                       const projectile_t&  proj) noexcept
{
    auto position = proj.position + proj.velocity;
    auto velocity = proj.velocity + env.gravity + env.wind;

    return {position, velocity};
}

int main()
{
    auto start    = rtc::point(0, 1, 0);
    auto velocity = rtc::normalize(rtc::vector(1, 1.8f, 0)) * 8.25f;
    auto proj     = projectile_t{start, velocity};

    auto gravity = rtc::vector(0, -0.1f, 0);
    auto wind    = rtc::vector(-0.01f, 0, 0);
    auto env     = environment_t{gravity, wind};

    auto canvas = rtc::canvas_t{500, 300};
    auto color  = rtc::color(1, 1, 1);

    while (proj.position.y > 0.f) {
        proj = tick(env, proj);

        auto x = static_cast<uint32_t>(std::roundf(proj.position.x));
        auto y = static_cast<uint32_t>(
            std::roundf(canvas.height() - proj.position.y));

        if (x < canvas.width() && y < canvas.height()) {
            canvas.write_pixel(x, y, color);
        }
    }

    rtc::write_bmp_to_file("chapter2.bmp", rtc::canvas_to_bmp(canvas));

    return 0;
}
