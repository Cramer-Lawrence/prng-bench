#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <chrono>
#include <iostream>
#include <functional>
#include <thread>

using Time = std::chrono::high_resolution_clock;
using DDuration = std::chrono::duration<double>;

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

        static void runMultiThreadBenchmark(
                const std::string& label,
                std::function<void(size_t, const uint64_t&, const uint64_t&)> benchmarkFunc,
                size_t iterationsPerThread,
                size_t numThreads,
                const uint64_t& min,
                const uint64_t& max);

        static void runSingleThreadBenchmark( 
                const std::string& label,
                std::function<void(size_t, const uint64_t&, const uint64_t&)> benchmarkFunc,
                size_t totalIterations,
                const uint64_t& min,
                const uint64_t& max);

        // Single thread, full workload
        template <typename PRNG>
        static void singleThreadBenchmark(size_t totalIterations, const uint64_t& min, const uint64_t& max) {
            PRNG single {12345};
            for (size_t i = 0; i < totalIterations; ++i) {
                single.next(min, max);
            }
        }

        // Purposely bad.
        template <typename PRNG>
        static void sharedBenchmark(size_t iterationsPerThread, const uint64_t& min, const uint64_t& max) {
            static PRNG shared{12345};
            for (size_t i = 0; i < iterationsPerThread; ++i) {
                shared.next(min, max);
            }
        }

        // thread-safe approach.
        template <typename PRNG>
        static void threadLocalBenchmark(size_t iterationsPerThread, const uint64_t& min, const uint64_t& max) {
            thread_local PRNG local {12345 + static_cast<uint64_t>(std::hash<std::thread::id>{}(std::this_thread::get_id()))};
            for (size_t i {0}; i < iterationsPerThread; ++i) {
                local.next(min, max);
            }
        }

        template <typename PRNG>
        static void benchmarkPRNG(const std::string& label, size_t iterationsPerThread, size_t numThreads, const uint64_t& min, const uint64_t& max) {
            runSingleThreadBenchmark(label + " (Single Thread)", singleThreadBenchmark<PRNG>, iterationsPerThread * numThreads, min, max);
            runMultiThreadBenchmark(label + " (Shared)", sharedBenchmark<PRNG>, iterationsPerThread, numThreads, min, max);
            runMultiThreadBenchmark(label + " (Thread-Local)", threadLocalBenchmark<PRNG>, iterationsPerThread, numThreads, min, max);
        }

        static void report (const std::string& name, double duration, size_t iterations) {
            std::cout << "Benchmark: " << name << "\n";
            std::cout << "Total Time: " << duration << "s\n";
            std::cout << "Avg Time per Call: " << (duration / iterations) * 1e6 << " us" << std::endl;
        }
};

#endif

