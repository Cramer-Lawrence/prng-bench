#include "mt19937.hpp"

void MT19937::seedImpl(uint64_t inSeed) {

    m_index = m_stateArraySize;
    m_MT[0] = m_seed;

    for (int i = 1; i < m_stateArraySize; i++) {
        m_MT[i] = m_magicMultiplier * (m_MT[i - 1] ^ (m_MT[i - 1] >> (m_wordSize - 2))) + i;
    }
}

uint32_t MT19937::next32() {
    
    if (m_index >= m_stateArraySize) {
        if (m_index > m_stateArraySize) seed(5489); // default seed
        twist();
    }

    uint64_t y = m_MT[m_index++];

    y ^= (y >> u) & d;
    y ^= (y << s) & b;
    y ^= (y << t) & c;
    y ^= (y >> l);

    return y;
}

uint64_t MT19937::nextImpl() {

    return (static_cast<uint64_t>(next32()) << 32) | static_cast<uint64_t>(next32());
}

void MT19937::twist() {

    for (int i = 0; i < m_stateArraySize; i++) {
        uint32_t x {(m_MT[i] & 0x80000000) + (m_MT[(i + 1) % m_stateArraySize] & 0x7fffffff)};
        uint32_t xA {x >> 1};
        if (x % 2 != 0) xA ^= m_randomImprovementConst;
        m_MT[i] = m_MT[(i + m_recurrenceOffset) % m_stateArraySize] ^ xA;
    }
    m_index = 0;
}
