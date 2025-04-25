#include "lcg.hpp"
#include "mt19937.hpp"
#include "benchmark.hpp"

int main() {

    const size_t iterations = 10000000;

    LCG lcg {12345};
    auto lcgDuration = Benchmark::run([&](){lcg.next();}, iterations);
    Benchmark::report("LCG PRNG", lcgDuration, iterations); 

    MT19937 mt {12345};
    auto mtDuration = Benchmark::run([&]() {mt.next();}, iterations);
    Benchmark::report("MT PRNG", mtDuration, iterations);

    return 0;
}
