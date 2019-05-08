
#ifndef RTC_TUPLE_HPP_
#define RTC_TUPLE_HPP_

#include "math.hpp"

namespace rtc {

template <int Length, typename T>
struct tuple_t;

template <typename T>
struct tuple_t<2, T> {
    union {
        struct {
            float x;
            float y;
        };

        float elements[2];
    };

    const float& operator[](int index) const { return elements[index]; }
    float&       operator[](int index) { return elements[index]; }
};

template <typename T>
struct tuple_t<3, T> {
    union {
        struct {
            float x;
            float y;
            float z;
        };

        struct {
            float red;
            float green;
            float blue;
        };

        float elements[3];
    };

    const float& operator[](int index) const { return elements[index]; }
    float&       operator[](int index) { return elements[index]; }
};

template <typename T>
struct tuple_t<4, T> {
    union {
        struct {
            float x;
            float y;
            float z;
            float w;
        };

        struct {
            float red;
            float green;
            float blue;
            float alpha;
        };

        float elements[4];
    };

    const float& operator[](int index) const { return elements[index]; }
    float&       operator[](int index) { return elements[index]; }
};

using tuple2_t = tuple_t<2, float>;
using tuple3_t = tuple_t<3, float>;
using tuple4_t = tuple_t<4, float>;

[[nodiscard]] inline bool operator==(const tuple2_t& a, const tuple2_t& b) noexcept
{
    return rtc::approx(a.x, b.x) && rtc::approx(a.y, b.y);
}

[[nodiscard]] inline bool operator==(const tuple3_t& a, const tuple3_t& b) noexcept
{
    return rtc::approx(a.x, b.x) && rtc::approx(a.y, b.y) && rtc::approx(a.z, b.z);
}

[[nodiscard]] inline bool operator==(const tuple4_t& a, const tuple4_t& b) noexcept
{
    return rtc::approx(a.x, b.x) && rtc::approx(a.y, b.y) && rtc::approx(a.z, b.z)
           && rtc::approx(a.w, b.w);
}

[[nodiscard]] inline tuple2_t operator+(const tuple2_t& a,
                                        const tuple2_t& b) noexcept
{
    return {a.x + b.x, a.y + b.y};
}

[[nodiscard]] inline tuple3_t operator+(const tuple3_t& a,
                                        const tuple3_t& b) noexcept
{
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

[[nodiscard]] inline tuple4_t operator+(const tuple4_t& a,
                                        const tuple4_t& b) noexcept
{
    return {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

[[nodiscard]] inline tuple2_t operator-(const tuple2_t& a,
                                        const tuple2_t& b) noexcept
{
    return {a.x - b.x, a.y - b.y};
}

[[nodiscard]] inline tuple3_t operator-(const tuple3_t& a,
                                        const tuple3_t& b) noexcept
{
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

[[nodiscard]] inline tuple4_t operator-(const tuple4_t& a,
                                        const tuple4_t& b) noexcept
{
    return {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}

[[nodiscard]] inline tuple2_t operator*(const tuple2_t& a,
                                        const tuple2_t& b) noexcept
{
    return {a.x * b.x, a.y * b.y};
}

[[nodiscard]] inline tuple3_t operator*(const tuple3_t& a,
                                        const tuple3_t& b) noexcept
{
    return {a.x * b.x, a.y * b.y, a.z * b.z};
}

[[nodiscard]] inline tuple4_t operator*(const tuple4_t& a,
                                        const tuple4_t& b) noexcept
{
    return {a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w};
}

[[nodiscard]] inline tuple2_t operator-(const tuple2_t& a) noexcept
{
    return {-a.x, -a.y};
}

[[nodiscard]] inline tuple3_t operator-(const tuple3_t& a) noexcept
{
    return {-a.x, -a.y, -a.z};
}

[[nodiscard]] inline tuple4_t operator-(const tuple4_t& a) noexcept
{
    return {-a.x, -a.y, -a.z, -a.w};
}

[[nodiscard]] inline tuple2_t operator*(const tuple2_t& a, float b) noexcept
{
    return {a.x * b, a.y * b};
}

[[nodiscard]] inline tuple3_t operator*(const tuple3_t& a, float b) noexcept
{
    return {a.x * b, a.y * b, a.z * b};
}

[[nodiscard]] inline tuple4_t operator*(const tuple4_t& a, float b) noexcept
{
    return {a.x * b, a.y * b, a.z * b, a.w * b};
}

// @todo prevent divide by 0
[[nodiscard]] inline tuple2_t operator/(const tuple2_t& a, float b)
{
    return {a.x / b, a.y / b};
}

[[nodiscard]] inline tuple3_t operator/(const tuple3_t& a, float b)
{
    return {a.x / b, a.y / b, a.z / b};
}

[[nodiscard]] inline tuple4_t operator/(const tuple4_t& a, float b)
{
    return {a.x / b, a.y / b, a.z / b, a.w / b};
}

[[nodiscard]] inline bool is_point(const tuple4_t& t) noexcept
{
    return rtc::approx(t.w, 1.f);
}

[[nodiscard]] inline bool is_vector(const tuple4_t& t) noexcept
{
    return rtc::approx(t.w, 0.f);
}

[[nodiscard]] inline tuple4_t point(float x, float y, float z) noexcept
{
    return {x, y, z, 1.f};
}

[[nodiscard]] inline tuple4_t vector(float x, float y, float z) noexcept
{
    return {x, y, z, 0.f};
}

[[nodiscard]] inline tuple4_t color(float r, float g, float b) noexcept
{
    return {r, g, b, 0.f};
}

[[nodiscard]] inline float dot(const tuple2_t& a, const tuple2_t& b) noexcept
{
    return {a.x * b.x + a.y * b.y};
}

[[nodiscard]] inline float dot(const tuple3_t& a, const tuple3_t& b) noexcept
{
    return {a.x * b.x + a.y * b.y + a.z * b.z};
}

[[nodiscard]] inline float dot(const tuple4_t& a, const tuple4_t& b) noexcept
{
    return {a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w};
}

template <typename T>
[[nodiscard]] inline float magnitude(const T& v) noexcept
{
    return std::sqrtf(rtc::dot(v, v));
}

template <typename T>
[[nodiscard]] inline tuple4_t normalize(const T& v) noexcept
{
    auto m = rtc::magnitude(v);
    return v * (1.f / m);
}

[[nodiscard]] inline tuple4_t cross(const tuple4_t& a, const tuple4_t& b) noexcept
{
    return rtc::vector(
        a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

[[nodiscard]] inline tuple4_t reflect(const tuple4_t& in,
                                      const tuple4_t& normal) noexcept
{
    return in - normal * 2 * rtc::dot(in, normal);
}

} // namespace rtc

#endif // RTC_TUPLE_HPP_
