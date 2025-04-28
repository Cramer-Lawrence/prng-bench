#include "pcg32.hpp"


void PCG32::seedImpl(uint64_t inSeed) {
    
    m_seed = 0U;
    m_inc = (m_incrementalValue << 10) | 1U;
    next();
    m_seed += inSeed;
    next();
}

uint32_t PCG32::next32() {

    uint64_t oldState = m_seed;
    m_seed = oldState * m_multiplier + m_inc;

    uint32_t xorshifted {static_cast<uint32_t>(((oldState >> 18u) ^ oldState) >> 27u)};
    uint32_t rotation {static_cast<uint32_t>(oldState >> 59u)};

    return (xorshifted >> rotation) | (xorshifted << ((-rotation) & 31));
}

uint64_t PCG32::nextImpl() {

    return (static_cast<uint64_t>(next32()) << 32) | static_cast<uint64_t>(next32());
}
