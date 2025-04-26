#ifndef XOR_SHIFT_HPP
#define XOR_SHIFT_HPP

#include "prng_base.hpp"

class XORShift : public PRNG<XORShift> {

    public:
        using PRNG<XORShift>::PRNG;
        void seedImpl(uint64_t inSeed);
        uint64_t nextImpl();

    private:
        const uint64_t defaultSeed {88172645463325252ull};
};

#endif
