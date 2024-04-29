#ifndef CYCLES_EXCEPTION_HPP__
#define CYCLES_EXCEPTION_HPP__

#include <exception>

namespace cycles {
namespace exception {
    class frequency : public std::exception {
        public:
            const char * what() const noexcept {
                return "frequency must be finite and greater than zero";
            }
    };

    class period : public std::exception {
        public:
            const char * what() const noexcept {
                return "period must be finite and greater than zero";
            }
    };

    class ratio : public std::exception {
        public:
            const char * what() const noexcept {
                return "ratio must be finite and greater than zero";
            }
    };

    class interval : public std::exception {
        public:
            const char * what() const noexcept {
                return "interval finish must be greater than its start";
            }
    };
} // namespace exception
} // namespace cycles

#endif // CYCLES_EXCEPTION_HPP__
