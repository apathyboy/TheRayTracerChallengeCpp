
#ifndef RTC_ALGORITHM_HPP_
#define RTC_ALGORITHM_HPP_

#include <algorithm>
#include <iterator>

namespace rtc {

template <typename ContainerT, typename T>
auto contains(const ContainerT& c, const T& x)
{
    return std::end(c) != std::find(std::begin(c), std::end(c), x);
}

} // namespace rtc

#endif // RTC_ALGORITHM_HPP_
