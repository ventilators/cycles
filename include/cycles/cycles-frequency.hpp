#ifndef CYCLES_FREQUENCY_HPP__
#define CYCLES_FREQUENCY_HPP__

#include <cmath>
#include <type_traits>

#include "cycles-exception.hpp"
#include "cycles-time.hpp"

namespace cycles {
    template <typename T>
    class Frequency {
        static_assert(std::is_floating_point<T>::value);
        public:
            constexpr explicit Frequency(T value) : value_(value) {
                if ((value <= 0.0) or (not std::isfinite(value))) {
                    throw cycles::exception::frequency();
                }
            }

            constexpr explicit Frequency(const Period<T>& period) {
                T value = period.count();
                if ((value <= 0.0) or (not std::isfinite(value))) {
                    throw cycles::exception::period();
                }
                value_ = 1.0 / value;
            }

            explicit operator
            T() const noexcept {
                return value_;
            }

            template <typename U>
            explicit operator
            Frequency<U>() const noexcept {
                return Frequency<U>(static_cast<U>(value_));
            }

            explicit operator
            Period<T>() const noexcept {
                return Period<T>(1.0 / value_);
            }

            friend std::ostream&
            operator<<(std::ostream& os, const Frequency<T>& f) {
                return os << f.value_;
            }

            friend std::partial_ordering
            operator<=>(const Frequency<T>& lhs, const Frequency<T>& rhs) {
                if (std::isnan(lhs.value_) or std::isnan(rhs.value_)) {
                    return std::partial_ordering::unordered;
                }
                const T TOLERANCE = 0.1;

                T difference = lhs.value_ - rhs.value_;
                if ((lhs.value_ == rhs.value_) or (std::abs(difference) <= TOLERANCE)) {
                    return std::partial_ordering::equivalent;
                } else if (difference > 0) {
                    return std::partial_ordering::greater;
                } else {
                    return std::partial_ordering::less;
                }
            }

            friend bool
            operator==(const Frequency<T>& lhs, const Frequency<T>& rhs) {
                return (lhs <=> rhs) == std::partial_ordering::equivalent;
            }

            friend bool
            operator!=(const Frequency<T>& lhs, const Frequency<T>& rhs) {
                return (lhs <=> rhs) != std::partial_ordering::equivalent;
            }

            friend bool
            operator<(const Frequency<T>& lhs, const Frequency<T>& rhs) {
                return (lhs <=> rhs) == std::partial_ordering::less;
            }

            friend bool
            operator<=(const Frequency<T>& lhs, const Frequency<T>& rhs) {
                std::partial_ordering order = (lhs <=> rhs);
                return (order == std::partial_ordering::less)
                    or (order == std::partial_ordering::equivalent)
                    ;
            }

            friend bool
            operator>=(const Frequency<T>& lhs, const Frequency<T>& rhs) {
                std::partial_ordering order = (lhs <=> rhs);
                return (order == std::partial_ordering::greater)
                    or (order == std::partial_ordering::equivalent)
                    ;
            }
        private:
            T value_;
    };
namespace frequency {
namespace literals {
    constexpr cycles::Frequency<double>
    operator""_hz(long double value) {
        return cycles::Frequency(static_cast<double>(value));
    }

    constexpr cycles::Frequency<double>
    operator""_hz(unsigned long long value) {
        return cycles::Frequency(static_cast<double>(value));
    }

    constexpr cycles::Frequency<double>
    operator""_bpm(long double value) {
        return cycles::Frequency(static_cast<double>(value / 60.0));
    }

    constexpr cycles::Frequency<double>
    operator""_bpm(unsigned long long value) {
        return cycles::Frequency(static_cast<double>(value / 60.0));
    }
} // namespace literals
} // namespace frequency
} // namespace cycles

#endif // CYCLES_FREQUENCY_HPP__
