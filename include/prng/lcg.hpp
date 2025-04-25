#include "prng_base.hpp"

class LCG : public PRNG<LCG> {

public:  
    using PRNG<LCG>::PRNG;

    void seedImpl(uint64_t inSeed) {
        m_seed.store(inSeed, std::memory_order_relaxed);
    }

    uint64_t nextImpl() {
        m_seed.store(((m_seed.load(std::memory_order_relaxed) * a) + c) % m, std::memory_order_relaxed);
        return m_seed;
    }

private:
    const uint64_t m {static_cast<uint64_t>(1) << 63};
    const uint64_t a {6364136223846793005};
    const uint64_t c {1};
};
