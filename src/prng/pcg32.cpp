#include "pcg32.hpp"


void PCG32::seedImpl(uint64_t inSeed) {
    
    state = 0U;
    inc = (incrementalValue << 10) | 1U;
    next();
    state += inSeed;
    next();
}

uint32_t PCG32::next32() {

    uint64_t oldState = state;
    state = oldState * multiplier + inc;

    uint32_t xorshifted {static_cast<uint32_t>(((oldState >> 18u) ^ oldState) >> 27u)};
    uint32_t rotation {static_cast<uint32_t>(oldState >> 59u)};

    return (xorshifted >> rotation) | (xorshifted << ((-rotation) & 31));
}

uint64_t PCG32::nextImpl() {

    return (static_cast<uint64_t>(next32()) << 32) | static_cast<uint64_t>(next32());
}
