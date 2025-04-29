#include "benchmark_runner.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>


void BenchmarkRunner::reportResults() const noexcept{

    std::cout << "\n=== Benchmark Results ===\n";
    std::cout << "Total Runs: " << m_iterationsPerThread * m_numThreads << "\n";
    std::cout << "Runs/Thread: " << m_iterationsPerThread << " Threads: " << m_numThreads << "\n\n";

    for (const auto& r : m_results) {
        std::cout << r.prngName << " (" << r.version << ")\n";
        std::cout << " Time: " << r.timeSeconds << " seconds\n";
        std::cout << " Avg Deviation: " << r.avgDeviation  << "%\n";
        std::cout << " Max Deviation: " << r.maxDeviation  << "%\n" << std::endl;
    }
}

void BenchmarkRunner::exportCSV(const std::string& filename) const {

    std::ofstream out(filename);
    if(!out) {
        std::cerr << "Failed to open CSV file: " << filename << std::endl;
        return;
    }

    out << "PRNG,Version,Iterations,Threads,TimeSeconds,AvgDeviation,MaxDeviation\n";
    for(const auto& r : m_results) {
        out << r.prngName << ","
            << r.version << ","
            << r.iterations << ","
            << r.threadsUsed << ","
            << std::fixed << std::setprecision(6) << r.timeSeconds << ","
            << std::fixed << std::setprecision(6) << r.avgDeviation << ","
            << std::fixed << std::setprecision(6) << r.maxDeviation << "\n";
    }
}
