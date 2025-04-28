#ifndef PRNG_BASE_HPP
#define PRNG_BASE_HPP

#include <cstdint>
#include <utility>

template <typename Derived>
class PRNG {    

public:
    PRNG() = default;
    
    PRNG(uint64_t inSeed)
        : m_seed{inSeed} {}

	inline void seed(uint64_t inSeed) {
		static_cast<Derived*>(this)->seedImpl(inSeed);
	}

	inline uint64_t next() {
		return static_cast<Derived*>(this)->nextImpl();
	}

    uint64_t next(uint64_t min, uint64_t max) {
        if (min > max) std::swap(min, max);
        if (min == max) return min;

        uint64_t range {max - min + 1};
        uint64_t limit {UINT64_MAX - (UINT64_MAX % range)};

        while (true) {
            uint64_t r {next()};
            if (r < limit)
                return min + (r % range);
        }
    }

protected:
    uint64_t m_seed;
};

#endif
