#include "../../include/timer/Timer.h"
#include <iostream>
#include <chrono>
#include <stdexcept>

using namespace std;

void Timer::reset(){
    start_time={};
    end_time = {};
    is_running=false;
}

int Timer::start() {
    if (is_running)
        throw runtime_error("Timer already started!");
    start_time = std::chrono::high_resolution_clock::now();
    is_running=true;
    return 0;
}

int Timer::stop() {
    if (!is_running)
        throw std::runtime_error("Timer not started!");
    end_time = std::chrono::high_resolution_clock::now();
    is_running= false;
    return 0;
}

int Timer::result() {
    if (is_running) throw std::runtime_error("Timer still running!");
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time-start_time);
    int result = static_cast<int>(duration.count());
    cout << result << endl;
    return result;
}

Timer::Timer() = default;