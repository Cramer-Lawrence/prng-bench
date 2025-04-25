#ifndef LCG_HPP
#define LCG_HPP

#include "prng_base.hpp"

class LCG : public PRNG<LCG> {

public:  
    using PRNG<LCG>::PRNG;
    void seedImpl(uint64_t inSeed);
    uint64_t nextImpl();

private:
    const uint64_t m {static_cast<uint64_t>(1) << 63};
    const uint64_t a {6364136223846793005};
    const uint64_t c {1};
};

#endif
