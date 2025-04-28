#include "lcg.hpp"

void LCG::seedImpl(uint64_t inSeed) {

    m_seed = inSeed;
}

uint64_t LCG::nextImpl() {

    m_seed = (((m_seed * a) + c) % m);
    return m_seed;
}
