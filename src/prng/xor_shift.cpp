#include "xor_shift.hpp"

void XORShift::seedImpl(uint64_t inSeed) {

    inSeed == 0 ? m_seed = defaultSeed : m_seed = inSeed;
}

uint64_t XORShift::nextImpl() {

    uint64_t state {m_seed};
    
    state ^= (state << 13);
    state ^= (state >> 7);
    state ^= (state << 17);

    m_seed = state;
    return state;
}
