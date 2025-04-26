#include "lcg.hpp"
#include "mt19937.hpp"
#include "pcg32.hpp"
#include "split_mix64.hpp"
#include "xor_shift.hpp"

#include "benchmark.hpp"

int main() {

    const size_t iterationsPerThread = 10000000;
    const size_t numThreads = std::thread::hardware_concurrency();
    const uint64_t min {0};
    const uint64_t max {1000};

    std::cout << "Running: " << iterationsPerThread * numThreads << " total iterations"
          << " (" << iterationsPerThread << " iterations per thread with " << numThreads << " threads)\n\n";

    Benchmark::benchmarkPRNG<LCG>("LCG", iterationsPerThread, numThreads, min, max);
    std::cout << std::endl;
    
    Benchmark::benchmarkPRNG<MT19937>("MT19937", iterationsPerThread, numThreads, min, max);
    std::cout << std::endl;
    
    Benchmark::benchmarkPRNG<PCG32>("PCG32", iterationsPerThread, numThreads, min, max);
    std::cout << std::endl;
    
    Benchmark::benchmarkPRNG<SplitMix64>("Split Mix 64", iterationsPerThread, numThreads, min, max);
    std::cout << std::endl;
    
    Benchmark::benchmarkPRNG<XORShift>("XOR Shift", iterationsPerThread, numThreads, min, max);

    return 0;
}
