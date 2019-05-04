
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
    auto p = projectile_t{rtc::point(0, 1, 0),
                          rtc::normalize(rtc::vector(1, 1, 0))};
    auto e = environment_t{rtc::vector(0, -0.1f, 0), rtc::vector(-0.01f, 0, 0)};

    while (p.position.y > 0.f) {
        p = tick(e, p);
    }

    return 0;
}
