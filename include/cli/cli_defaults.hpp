#ifndef CLI_DEFAULTS_HPP
#define CLI_DEFAULTS_HPP

#include <cstdint>
#include <cstddef>

namespace cli {

    // How many random draws per thread by default
    constexpr std::size_t iterations {1'000'000};

    // Number of worker threads
    constexpr std::size_t numThreads {2};

    // Default random range [0 - 1000]
    constexpr uint64_t minRange {0};
    constexpr uint64_t maxRange {1000};

    // Defaults filename for the CSV or text export
    constexpr const char* fileName {"prng-bench.txt"};

    // Default should export csv
    constexpr bool exportCSV {false};

} // namespace cli

#endif // CLI_DEFAULTS_HPP
