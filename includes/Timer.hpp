#pragma once

#include <chrono>

class Timer 
{
private:
    std::chrono::steady_clock::time_point start;

public:
    Timer();
    void reset();
    std::chrono::duration<double> time_elapsed();
};