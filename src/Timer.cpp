#include "Timer.hpp"

Timer::Timer() : start(std::chrono::steady_clock::now()) {}

std::chrono::duration<double> Timer::time_elapsed()
{
        auto now = std::chrono::steady_clock::now();
        auto duration = now - start;
        return duration;
}

void Timer::reset()
{
    auto now = std::chrono::steady_clock::now();
    start = now;
}