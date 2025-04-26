#include "benchmark.hpp"

void Benchmark::runMultiThreadBenchmark(
        const std::string& label,
        std::function<void(size_t, const uint64_t&, const uint64_t&)> benchmarkFunc,
        size_t iterationsPerThread,
        size_t numThreads,
        const uint64_t& min,
        const uint64_t& max) {

    std::vector<std::thread> threads;
    auto start {Time::now()};

    for (size_t t = 0; t < numThreads; ++t) {
        threads.emplace_back(benchmarkFunc, iterationsPerThread, min, max);
    }

    for (auto& th : threads) {
        th.join();
    }

    auto end {Time::now()};
    auto duration {DDuration(end - start).count()};

    std::cout << label << ": " << duration << " seconds\n";
}

void Benchmark::runSingleThreadBenchmark(
        const std::string& label,
        std::function<void(size_t, const uint64_t&, const uint64_t&)> benchmarkFunc, 
        size_t totalIterations,
        const uint64_t& min,
        const uint64_t& max) {

    auto start {Time::now()};

    benchmarkFunc(totalIterations, min, max);

    auto end {Time::now()};
    auto duration {DDuration(end - start).count()};
    
    std::cout << label << ": " << duration << " seconds\n";
}
