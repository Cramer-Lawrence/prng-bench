#ifndef CLI_DEFAULTS_HPP
#define CLI_DEFAULTS_HPP

#include <cstdint>

namespace cli_defaults {

    constexpr uint64_t iterations {1'000'000};
    constexpr uint64_t numThreads {2};
    constexpr uint64_t min {0};
    constexpr uint64_t max {1000};
    constexpr const char* defaultFileName {"prng-bench.txt"};
}

#endif
