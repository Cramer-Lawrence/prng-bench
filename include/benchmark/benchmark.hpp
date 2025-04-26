#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <cstdint>
#include <vector>

struct DistributionResult {
    double avg {};
    double max {};
};

class Benchmark {
public:
    static DistributionResult calculateDistribution(const std::vector<uint64_t>& values, uint64_t rangeMin, uint64_t rangeMax);
};

#endif
