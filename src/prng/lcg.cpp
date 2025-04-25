#include "lcg.hpp"

void LCG::seedImpl(uint64_t inSeed) {

    m_seed.store(inSeed, std::memory_order_relaxed);
}

uint64_t LCG::nextImpl() {

    m_seed.store(((m_seed.load(std::memory_order_relaxed) * a) + c) % m, std::memory_order_relaxed);
    return m_seed;
}
