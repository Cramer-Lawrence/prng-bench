#ifndef MT19937_HPP
#define MT19937_HPP

#include "prng_base.hpp"

class MT19937 : public PRNG<MT19937> {
    public:
        using PRNG<MT19937>::PRNG;

        void seedImpl(uint64_t inSeed);

        uint64_t nextImpl();

        uint32_t next32();

    private:
	    static constexpr int m_wordSize {32};
    	static constexpr int m_stateArraySize {624};
    	static constexpr int m_recurrenceOffset {397};
    	static constexpr int m_lowerTwistBitsNum {31};
    	static constexpr uint32_t m_randomImprovementConst {0x990880DF};

    	// Tempering bitwise shift constants
    	static constexpr uint32_t u {11};
    	static constexpr uint32_t d {0xFFFFFFFF};
    	static constexpr uint32_t s {7};
    	static constexpr uint32_t b {0x9D2C5680};
    	static constexpr uint32_t t {15};
    	static constexpr uint32_t c {0xEFC60000};
    	static constexpr uint32_t l {18};

    	static constexpr uint32_t m_magicMultiplier {1812433253};

    	uint32_t m_MT[m_stateArraySize];
    	int m_index = m_stateArraySize + 1;
	
    private:
    	void twist();

};

#endif
