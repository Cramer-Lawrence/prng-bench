#ifndef SPLIT_MIX64_HPP
#define SPLIT_MIX64_HPP

#include "prng_base.hpp"

class SplitMix64 : public PRNG<SplitMix64> {

    public: 
        using PRNG<SplitMix64>::PRNG;
        void seedImpl(uint64_t inSeed);
        uint64_t nextImpl();
    
    private:
        const uint64_t goldenConstant {0x9E3779B97F4A7C15ull};
};

#endif
