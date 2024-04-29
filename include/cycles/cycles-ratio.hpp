#ifndef CYCLES_RATIO_HPP__
#define CYCLES_RATIO_HPP__

#include <cmath>
#include <type_traits>

#include "cycles/cycles-exception.hpp"
#include "cycles/cycles-frequency.hpp"
#include "cycles/cycles-time.hpp"

namespace cycles {
    template <typename T>
    class Ratio {
        static_assert(std::is_floating_point<T>::value);
        public:
            constexpr explicit Ratio(T i, T e) 
                : ratio_({i, e})
            {
                if (not std::isfinite(i) or (i <= 0.0)) { throw cycles::exception::ratio(); }
                if (not std::isfinite(e) or (e <= 0.0)) { throw cycles::exception::ratio(); }
            }

            friend std::ostream&
            operator<<(std::ostream& os, const Ratio<T>& f) {
                return os << f.ratio_.first << " : " << f.ratio_.second;
            }

            Inspiration<T>
            inspiration(const Period<T>& period) const {
                T fraction = ratio_.first / this->total();
                return period * fraction;
            }

            Expiration<T>
            expiration(const Period<T>& period) const {
                T fraction = ratio_.second / this->total();
                return period * fraction;
            }

            Inspiration<T>
            inspiration(const Frequency<T>& f) const {
                return this->inspiration(static_cast<Period<T>>(f));
            }

            Expiration<T>
            expiration(const Frequency<T>& f) const {
                return this->expiration(static_cast<Period<T>>(f));
            }
        private:
            T total() const { return ratio_.first + ratio_.second; }

            std::pair<T, T> ratio_;
    };
} // namespace cycles

#endif // CYCLES_RATIO_HPP__
