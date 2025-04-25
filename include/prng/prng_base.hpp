#ifndef PRNG_BASE_HPP
#define PRNG_BASE_HPP

template <typename Derived>
struct PRNG {
	void seed(uint64_t) {
		static_cast<Derived*>(this)->seedImpl();
	}

	uint64_t next() {
		return statics_cast<Derived*>(this)->nextImpl();
	}
};

#endif
