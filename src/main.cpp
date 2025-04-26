#include "lcg.hpp"
#include "mt19937.hpp"
#include "pcg32.hpp"
#include "split_mix64.hpp"
#include "xor_shift.hpp"

#include <thread>

#include "benchmark_runner.hpp"

int main() {

    const size_t iterationsPerThread = 1000000;
    const size_t numThreads = std::thread::hardware_concurrency();
    const uint64_t min {0};
    const uint64_t max {1000};
    
    BenchmarkRunner runner {iterationsPerThread, numThreads, min, max};

    runner.runBenchmark<LCG>("LCG");
    runner.runBenchmark<MT19937>("MT19937");
    runner.runBenchmark<PCG32>("PCG32");
    runner.runBenchmark<SplitMix64>("Split Mix 64");
    runner.runBenchmark<XORShift>("XOR Shift");

    runner.reportResults();

    return 0;
}
