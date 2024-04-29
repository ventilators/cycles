#ifndef CYCLES_TIME_HPP__
#define CYCLES_TIME_HPP__

#include <chrono>

namespace cycles {
    template <typename T> using Time        = std::chrono::duration<T>;
    template <typename T> using Pause       = Time<T>;
    template <typename T> using Period      = Time<T>;
    template <typename T> using Expiration  = Time<T>;
    template <typename T> using Inspiration = Time<T>;
namespace inspiratory {
    template <typename T> using Pause = std::optional<Pause<T>>;
} // namespace inspiratory
namespace expiratory {
    template <typename T> using Pause = std::optional<Pause<T>>;
} // namespace expiratory
} // namespace cycles

#endif // CYCLES_TIME_HPP__
