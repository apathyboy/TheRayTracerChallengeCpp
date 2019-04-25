
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

[[nodiscard]] inline bool operator==(const tuple_t& a, const tuple_t& b) noexcept
{
    return rtc::equal(a.x, b.x) && rtc::equal(a.y, b.y) && rtc::equal(a.z, b.z)
           && rtc::equal(a.w, b.w);
}

[[nodiscard]] inline tuple_t operator+(const tuple_t& a, const tuple_t& b) noexcept
{
    return {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

[[nodiscard]] inline tuple_t operator-(const tuple_t& a, const tuple_t& b) noexcept
{
    return {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}

[[nodiscard]] inline tuple_t operator-(const tuple_t& a) noexcept
{
    return {-a.x, -a.y, -a.z, -a.w};
}

[[nodiscard]] inline tuple_t operator*(const tuple_t& a, float b) noexcept
{
    return {a.x * b, a.y * b, a.z * b, a.w * b};
}

// @todo prevent divide by 0
[[nodiscard]] inline tuple_t operator/(const tuple_t& a, float b)
{
    return {a.x / b, a.y / b, a.z / b, a.w / b};
}

[[nodiscard]] inline bool is_point(const tuple_t& t) noexcept
{
    return rtc::equal(t.w, 1.f);
}

[[nodiscard]] inline bool is_vector(const tuple_t& t) noexcept
{
    return rtc::equal(t.w, 0.f);
}

[[nodiscard]] inline tuple_t point(float x, float y, float z) noexcept
{
    return {x, y, z, 1.f};
}

[[nodiscard]] inline tuple_t vector(float x, float y, float z) noexcept
{
    return {x, y, z, 0.f};
}

[[nodiscard]] inline float dot(const tuple_t& a, const tuple_t& b) noexcept
{
    return {a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w};
}

[[nodiscard]] inline float magnitude(const tuple_t& v) noexcept
{
    return rtc::sqrt(rtc::dot(v, v));
}

[[nodiscard]] inline tuple_t normalize(const tuple_t& v) noexcept
{
    auto m = rtc::magnitude(v);
    return v * (1.f / m);
}

[[nodiscard]] inline tuple_t cross(const tuple_t& a, const tuple_t& b) noexcept
{
    return rtc::vector(
        a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

} // namespace rtc

#endif // RTC_TUPLE_HPP_
