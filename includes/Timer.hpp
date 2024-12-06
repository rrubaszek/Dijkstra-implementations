#pragma once

#include <chrono>

class Timer 
{
public:
    Timer();
    std::chrono::duration<double> time_elapsed();
    void reset();

private:
    std::chrono::steady_clock::time_point start;
};