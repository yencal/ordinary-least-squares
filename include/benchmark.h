#pragma once

#include <chrono>
#include <command.h>
#include <utilities.h>

// benchmark main
void benchmark(Command cmd);

// fill array with random numbers (0,1]
void fill_with_rand(real_t* ptr, int size);

// Timer class
class Timer
{
    using clock_t = std::chrono::high_resolution_clock;

  private:
    clock_t::time_point start_time_;
    clock_t::duration elapsed_time_;
    double elapsed_time_in_seconds_;

  public:
    void reset();
    double stop();
    // use default constructor and destructor for now
};