
#include <rtc/tuple.hpp>

struct projectile_t {
    rtc::tuple_t position;
    rtc::tuple_t velocity;
};

struct environment_t {
    rtc::tuple_t gravity;
    rtc::tuple_t wind;
};

static projectile_t tick(const environment_t& env, const projectile_t& proj)
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
