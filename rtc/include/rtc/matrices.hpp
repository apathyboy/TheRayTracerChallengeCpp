
#ifndef RTC_MATRICES_HPP_
#define RTC_MATRICES_HPP_

#include <memory>

namespace rtc {

class matrix4x4_t {
    constexpr static int rows    = 4;
    constexpr static int columns = 4;

    float data_[rows * columns] = {};

public:
    matrix4x4_t() = default;

    // clang-format off
    matrix4x4_t(float val0_0, float val0_1, float val0_2, float val0_3,
              float val1_0, float val1_1, float val1_2, float val1_3,
              float val2_0, float val2_1, float val2_2, float val2_3,
              float val3_0, float val3_1, float val3_2, float val3_3) noexcept
        : data_{val0_0, val0_1, val0_2, val0_3,
                val1_0, val1_1, val1_2, val1_3,
                val2_0, val2_1, val2_2, val2_3,
                val3_0, val3_1, val3_2, val3_3}
    {}
    // clang-format on

    template <typename T>
    class proxy {
        T arr_;

    public:
        explicit proxy(T arr)
            : arr_{arr}
        {
        }

        // clang-format off
        typename std::pointer_traits<T>::element_type
            & operator[](int index)
        {
            return arr_[index];
        }
        // clang-format on
    };

    auto operator[](int index) const { return proxy(data_ + index * columns); }
    auto operator[](int index) { return proxy(data_ + index * columns); }
};

} // namespace rtc

#endif // RTC_MATRICES_HPP_
