#include "pcg32.hpp"


void PCG32::seedImpl(uint64_t inSeed) {
    
    m_seed.store(0U, std::memory_order_relaxed);
    m_inc.store(((m_incrementalValue << 10) | 1U), std::memory_order_relaxed);
    next();
    m_seed.fetch_add(inSeed, std::memory_order_relaxed);
    next();
}

uint32_t PCG32::next32() {

    uint64_t oldState = m_seed.load(std::memory_order_relaxed);
    uint64_t newState {};

    do {
        newState = oldState * m_multiplier + m_inc.load(std::memory_order_relaxed);
    } while (!m_seed.compare_exchange_weak(oldState, newState, std::memory_order_relaxed));

    uint32_t xorshifted {static_cast<uint32_t>(((oldState >> 18u) ^ oldState) >> 27u)};
    uint32_t rotation {static_cast<uint32_t>(oldState >> 59u)};

    return (xorshifted >> rotation) | (xorshifted << ((-rotation) & 31));
}

uint64_t PCG32::nextImpl() {

    return (static_cast<uint64_t>(next32()) << 32) | static_cast<uint64_t>(next32());
}
