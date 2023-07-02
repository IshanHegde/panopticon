#pragma once

#include <chrono>
#include <string>
#include <map>
#include <iostream>

class Timer
{

private:

    std::string m_name;
    std::chrono::high_resolution_clock::time_point m_start;
    

    static std::map<std::string, long long> m_timings;
    

public:

    Timer(const std::string & t_name): m_name(t_name), m_start(std::chrono::high_resolution_clock::now()) {};

    ~Timer()
        {
            auto end = std::chrono::high_resolution_clock::now();
            auto duration  = std::chrono::duration_cast<std::chrono::microseconds>(end - m_start);
            m_timings[m_name] += duration.count();

        }

    static void outputTimings() {
        for (const auto& timing : m_timings) {
            std::cout << timing.first << ": " << timing.second << " us\n";
        }
    }
    

};

std::map<std::string, long long> Timer::m_timings;


