
#ifndef RTC_TUPLE_HPP_
#define RTC_TUPLE_HPP_

#include "math.hpp"

namespace rtc {

struct tuple_t {
    union {
        struct {
            float x;
            float y;
            float z;
            float w;
        };

        float elements[4];
    };
};

[[nodiscard]] inline bool is_point(const tuple_t& t) noexcept
{
    return rtc::equal(t.w, 1.f);
}

[[nodiscard]] inline bool is_vector(const tuple_t& t) noexcept
{
    return rtc::equal(t.w, 0.f);
}

} // namespace rtc

#endif // RTC_TUPLE_HPP_
