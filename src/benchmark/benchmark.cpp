#include "benchmark.hpp"

DistributionResult Benchmark::calculateDistribution(const std::vector<uint64_t>& values, uint64_t rangeMin, uint64_t rangeMax) {

    size_t range = rangeMax - rangeMin + 1;
    std::vector<size_t> counts(range, 0);

    for (auto v : values) {
        size_t index = static_cast<size_t>((v - rangeMin) % range);
        counts[index]++;
    }

    double expected {static_cast<double>(values.size()) / range};
    double sumDeviation {0.0};
    double maxDeviation {0.0};

    for (auto c : counts) {
        double deviation {std::abs(c - expected) / expected};
        sumDeviation += deviation;
        if(deviation > maxDeviation) {
            maxDeviation = deviation;
        }
    }

    return {sumDeviation / range, maxDeviation};
}
