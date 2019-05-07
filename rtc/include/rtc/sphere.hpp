
#ifndef RTC_SPHERE_HPP_
#define RTC_SPHERE_HPP_

#include "ray.hpp"

#include <cstdint>
#include <vector>

namespace rtc {

struct sphere_t {
    uint32_t id;

    friend bool operator==(const sphere_t& l, const sphere_t& r) noexcept
    {
        return l.id == r.id;
    }
};

[[nodiscard]] inline sphere_t sphere() noexcept
{
    static uint32_t next_id = 0;

    return sphere_t{next_id++};
}

} // namespace rtc

#endif // RTC_SPHERE_HPP_
