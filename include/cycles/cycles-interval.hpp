#ifndef CYCLES_INTERVAL_HPP__
#define CYCLES_INTERVAL_HPP__

#include <type_traits>

#include "cycles-exception.hpp"
#include "cycles-time.hpp"

namespace cycles {
    enum class State {
          INSPIRATION
        , INSPIRATORY_PAUSE
        , EXPIRATION
        , EXPIRATORY_PAUSE
    };

    template <typename T>
    class Interval {
        static_assert(std::is_floating_point<T>::value);
        public:
            Interval(const Time<T>& start, const Time<T>& finish, State state) 
                : start_(start)
                , finish_(finish)
                , state_(state)
            {
                if (finish <= start) { throw cycles::exception::interval(); }
            }

            bool
            inside(const Time<T>& instant) const {
                return (start_ <= instant) and (instant < finish_);
            }

            bool
            outside(const Time<T>& instant) const {
                return not inside(instant);
            }

            State
            state() const {
                return state_;
            }
        private:
            Time<T> start_;
            Time<T> finish_;
            State   state_;
    };
} // namespace cycles

#endif // CYCLES_INTERVAL_HPP__
