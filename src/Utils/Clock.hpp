/*
** EPITECH PROJECT, 2022
** Gomoku
** File description:
** Gomoku Clock
*/

#ifndef GOMOKU_CLOCK_HPP_
#define GOMOKU_CLOCK_HPP_

#include <chrono>

namespace Gomoku {

    class Clock {
        public:
            Clock() {}
            ~Clock() {}

            void start() {
                __setNow();
            }

            double getSecondsElapsed() const {
                int64_t elapsed = __getElapse();
                double result = static_cast<double>(elapsed) / 1000000.0f;

                return result;
            }

            double getMillisecondsElapsed() const {
                int64_t elapsed = __getElapse();
                double result = static_cast<double>(elapsed) / 1000.0f;

                return result;
            }

            double getMicrosecondsElapsed() const {
                int64_t elapsed = __getElapse();

                return static_cast<double>(elapsed);
            }

        protected:
            int64_t _start = 0;
        private:
            int64_t __getElapse() const {
                std::chrono::microseconds ms = std::chrono::duration_cast<std::chrono::microseconds >(
                    std::chrono::high_resolution_clock::now().time_since_epoch()
                );
                int64_t _nVal = ms.count();
                return (_nVal - _start);
            }

            void __setNow() {
                std::chrono::microseconds ms = std::chrono::duration_cast<std::chrono::microseconds >(
                    std::chrono::high_resolution_clock::now().time_since_epoch()
                );
                _start = ms.count();
            }
    };

}

#endif /* !GOMOKU_CLOCK_HPP_ */
