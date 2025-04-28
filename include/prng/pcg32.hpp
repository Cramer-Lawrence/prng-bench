#ifndef PCG32_HPP
#define PCG32_HPP

#include "prng_base.hpp"

class PCG32 : public PRNG<PCG32> {

public: 
    using PRNG<PCG32>::PRNG;
    void seedImpl(uint64_t inSeed);
    uint64_t nextImpl();
    uint32_t next32();

private:
    uint64_t m_inc;

    const uint64_t m_multiplier {6364136223846793005ULL}; // from pcg32 research paper
    const uint64_t m_incrementalValue {0xda3e39cb94b95bdbULL};
};

#endif
