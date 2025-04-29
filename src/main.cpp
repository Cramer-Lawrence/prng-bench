#include "lcg.hpp"
#include "mt19937.hpp"
#include "pcg32.hpp"
#include "split_mix64.hpp"
#include "xor_shift.hpp"

#include <thread>

#include "benchmark_runner.hpp"
#include "cli_parser.hpp"

int main(int argc, char** argv) {

    // Boot up the cli parser
    cli::CLIParser cP {};

    // Execute the parse
    if (!cP.cliParse(argc, argv)) return 0;

    auto const& opts = cP.getArgs();

    // Ensure threads has a good value
    uint64_t threads = opts.numThreads > std::thread::hardware_concurrency() ?
        std::thread::hardware_concurrency() : opts.numThreads;

    // Translate the cli parse into the benchmark runner
    BenchmarkRunner runner {
        opts.lowIteration,
        opts.highIteration,
        opts.iterationSpread,
        threads,
        opts.minRange,
        opts.maxRange
    };

    // Run the series of benchmarks
    runner.runBenchmark<LCG>("LCG");
    runner.runBenchmark<MT19937>("MT19937");
    runner.runBenchmark<PCG32>("PCG32");
    runner.runBenchmark<SplitMix64>("Split Mix 64");
    runner.runBenchmark<XORShift>("XOR Shift");

    // Print out the results to the console
    runner.reportResults();

    if (opts.exportCSV) {
        runner.exportCSV(opts.fileName);
        std::cout << "Results exported to: " << opts.fileName << "\n";
    }

    return 0;
}
