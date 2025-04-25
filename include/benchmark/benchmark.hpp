#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <chrono>
#include <iostream>


class Benchmark {
    public:
        template<typename Func>
        static double run(Func&& func, size_t iterations = 1000000) {
            func();

            auto start = std::chrono::high_resolution_clock::now();
            for (size_t i = 0; i < iterations; ++i) {
                func();
            }

            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> duration = end - start;
            return duration.count();
        }

        static void report (const std::string& name, double duration, size_t iterations) {
            std::cout << "Benchmark: " << name << "\n";
            std::cout << "Total Time: " << duration << "s\n";
            std::cout << "Avg Time per Call: " << (duration / iterations) * 1e6 << " us" << std::endl;
        }
};

#endif

