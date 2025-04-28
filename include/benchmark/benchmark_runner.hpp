#ifndef BENCHMARK_RUNNER_HPP
#define BENCHMARK_RUNNER_HPP

#include "benchmark.hpp"
#include "thread_safe_wrap.hpp"

#include <chrono>
#include <vector>
#include <string>
#include <thread>

using Time = std::chrono::high_resolution_clock;
using DDuration = std::chrono::duration<double>;


struct BenchmarkResult {
    
    std::string prngName;
    std::string version; // "Single", "Shared", "Thread-Local"
    double timeSeconds {};
    double avgDeviation {};
    double maxDeviation {};
};

class BenchmarkRunner {

public:

    BenchmarkRunner(
            size_t iterationsPerThread,
            size_t numThreads,
            const uint64_t& min,
            const uint64_t& max)
        : m_iterationsPerThread{iterationsPerThread},
        m_numThreads{numThreads},
        m_min{min},
        m_max{max} {};
    
    template <typename PRNG>
    void runBenchmark(const std::string& prngName) {
        m_results.push_back(benchmarkSingleThread<PRNG>(prngName));
        m_results.push_back(benchmarkShared<PRNG>(prngName));
        m_results.push_back(benchmarkThreadLocal<PRNG>(prngName));
    }

    void reportResults() const noexcept;
    void exportCSV(const std::string& filename) const;

private:
    size_t m_iterationsPerThread;
    size_t m_numThreads;

    const uint64_t& m_min;
    const uint64_t& m_max;
    std::vector<BenchmarkResult> m_results;

    template <typename PRNG>
    BenchmarkResult benchmarkSingleThread(const std::string& prngName) {    

        std::vector<uint64_t> values;
        values.reserve(m_iterationsPerThread * m_numThreads);

        auto start {Time::now()};
        PRNG rng{12345};
        for (size_t i {0}; i < m_iterationsPerThread * m_numThreads; ++i) {
            values.push_back(rng.next(m_min, m_max));
        }
        auto end {Time::now()};
    
        double duration {DDuration(end - start).count()};
        auto dist {Benchmark::calculateDistribution(values, m_min, m_max)};

        return {prngName, "Single Thread", duration, dist.avg, dist.max};
    }

    template <typename PRNG>
    BenchmarkResult benchmarkShared(const std::string& prngName) {
        std::vector<std::vector<uint64_t>> allValues(m_numThreads);

        auto start {Time::now()};
        std::vector<std::thread> threads;
        prng::ThreadSafePRNG<PRNG> shared{12345};
        for(size_t t {0}; t < m_numThreads; ++t) {
            threads.emplace_back([&, t]() {
                for (size_t i = 0; i < m_iterationsPerThread; ++i) {
                    allValues[t].push_back(shared.next(m_min, m_max));
                }
            });
        }

        for (auto& th : threads) th.join();

        auto end {Time::now()};
        double duration {DDuration(end - start).count()};
        std::vector<uint64_t> combined;

        for (auto& v : allValues) combined.insert(combined.end(), v.begin(), v.end());
        auto dist {Benchmark::calculateDistribution(combined, m_min, m_max)};

        return {prngName, "Shared", duration, dist.avg, dist.max};           
    }

    template <typename PRNG>
    BenchmarkResult benchmarkThreadLocal(const std::string& prngName) {

        std::vector<std::vector<uint64_t>> allValues(m_numThreads);
        auto start {Time::now()};
        std::vector<std::thread> threads;

        for (size_t t{0}; t < m_numThreads; ++t) {
            threads.emplace_back([&, t]() {
                thread_local PRNG local{12345 + static_cast<uint64_t>(std::hash<std::thread::id>{}(std::this_thread::get_id()))};
                for (size_t i{0}; i < m_iterationsPerThread; ++i) {
                    allValues[t].push_back(local.next());
                }
            });
        }

        for (auto& th : threads) th.join();
    
        auto end {Time::now()};
        double duration {DDuration(end - start).count()};
        std::vector<uint64_t> combined;

        for (auto& v : allValues) combined.insert(combined.end(), v.begin(), v.end());
        auto dist {Benchmark::calculateDistribution(combined, m_min, m_max)};

        return {prngName, "Thread-Local", duration, dist.avg, dist.max};
    }
};

#endif
