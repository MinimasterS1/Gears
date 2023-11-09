#pragma once


#include <chrono>

class Timer {
public:
    Timer() : startTime(std::chrono::high_resolution_clock::now()) {}

  
    float getElapsedTime() const {
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = currentTime - startTime;
        return duration.count();
    }

   
    void reset() {
        startTime = std::chrono::high_resolution_clock::now();
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
};
