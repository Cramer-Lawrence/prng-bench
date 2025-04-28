#include "split_mix64.hpp"


void SplitMix64::seedImpl(uint64_t inSeed) {

    m_seed = inSeed;
}

uint64_t SplitMix64::nextImpl() {

    uint64_t result = m_seed;
    m_seed =result + goldenConstant;
	result = (result ^ (result >> 30)) * 0xBF58476D1CE4E5B9ull;
	result = (result ^ (result >> 27)) * 0x94D049BB133111EBull;

    return result ^ (result >> 31);
}
