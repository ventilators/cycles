#ifndef CYCLES_HPP__
#define CYCLES_HPP__

#include <type_traits>

#include "cycles-exception.hpp"

#include "cycles-frequency.hpp"
#include "cycles-interval.hpp"
#include "cycles-time.hpp"
#include "cycles-ratio.hpp"

namespace cycles {
    enum class Mark { START_OF_INSPIRATION, START_OF_EXPIRATION };

    template <typename T>
    class Cycle {
        static_assert(std::is_floating_point<T>::value);
        public:
            Cycle(
                      const Inspiration<T>&         i
                    , const inspiratory::Pause<T>&  fst
                    , const Expiration<T>&          e
                    , const expiratory::Pause<T>&   snd
                    ) 
                : current_(Time<T>::zero())
                , index_(0)
            {
                // Inspiratory phase
                Time<T> prev = Time<T>::zero();
                Time<T> next = i;
                intervals_.emplace_back(prev, next, cycles::State::INSPIRATION);
                // Inspiratory pause
                if (fst) {
                    prev = next;
                    next += *fst;
                    intervals_.emplace_back(prev, next, cycles::State::INSPIRATORY_PAUSE);
                }
                // Expiratory phase
                prev = next;
                next += e;
                intervals_.emplace_back(prev, next, cycles::State::EXPIRATION);
                // Expiratory pause
                if (snd) {
                    prev = next;
                    next += e;
                    intervals_.emplace_back(prev, next, cycles::State::EXPIRATORY_PAUSE);
                }
            }

            Cycle(const Inspiration<T>& i, const Expiration<T>& e) : Cycle(i, {}, e, {}) {}

            std::optional<Mark>
            operator()(const Time<T>& step) {
                current_ += step;
                if (intervals_[index_].inside(current_)) { return {}; }

                index_ = (index_ + 1) % intervals_.size();
                if (index_ == 0) { current_ = Time<T>::zero(); }

                switch(this->state()) {
                    case cycles::State::INSPIRATION:
                        return Mark::START_OF_INSPIRATION;
                    case cycles::State::EXPIRATION:
                        return Mark::START_OF_EXPIRATION;
                    default:
                        return {};
                }
            }

            State
            state() const { return intervals_[index_].state(); }
        private:
            Time<T>                             current_;

            std::vector<cycles::Interval<T>>    intervals_;
            std::size_t                         index_;
    };
} // namespace cycles

#endif // CYCLES_HPP__
