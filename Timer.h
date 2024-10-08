#pragma once
#include <chrono>

class Timer {
public:
    Timer();
    void reset();
    double elapsedHour() const;
    double elapsedMinutes() const;
    double elapsedSeconds() const;
    double elapsedMiliseconds() const;
    double elapsedMicroseconds() const;

private:
    std::chrono::high_resolution_clock::time_point start_time;
};
