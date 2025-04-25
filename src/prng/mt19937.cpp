#include "mt19937.hpp"

void MT19937::seedImpl(uint64_t inSeed) {

    index = stateArraySize;
    MT[0] = m_seed.load(std::memory_order_relaxed);

    for (int i = 1; i < stateArraySize; i++) {
        MT[i] = magicMultiplier * (MT[i - 1] ^ (MT[i - 1] >> (wordSize - 2))) + i;
    }
}

uint32_t MT19937::next32() {
    
    if (index >= stateArraySize) {
        if (index > stateArraySize) seed(5489); // default seed
        twist();
    }

    uint64_t y = MT[index++];

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

    for (int i = 0; i < stateArraySize; i++) {
        uint32_t x {(MT[i] & 0x80000000) + (MT[(i + 1) % stateArraySize] & 0x7fffffff)};
        uint32_t xA {x >> 1};
        if (x % 2 != 0) xA ^= randomImprovementConst;
        MT[i] = MT[(i + recurrenceOffset) % stateArraySize] ^ xA;
    }
    index = 0;
}
