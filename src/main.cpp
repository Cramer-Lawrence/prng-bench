#include "lcg.hpp"
#include "benchmark.hpp"

int main() {

    const size_t iterations = 10000000;
    LCG lcg {12345};

    auto duration = Benchmark::run([&](){
            lcg.next();
    }, iterations);

    Benchmark::report("LCG PRNG", duration, iterations); 
}
