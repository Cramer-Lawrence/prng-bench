#ifndef THREAD_SAFE_WRAP_HPP
#define THREAD_SAFE_WRAP_HPP

#include <mutex>

namespace prng {

template <typename PRNG>
class ThreadSafePRNG {

private:
    PRNG m_inner;
    mutable std::mutex m_mtx;

public:
    template<typename... Args>
        ThreadSafePRNG(Args&&... args)
        : m_inner(std::forward<Args>(args)...) {}

    void seed(uint64_t inSeed) {
        std::lock_guard<std::mutex> lk(m_mtx);
        m_inner.seed(inSeed);
    }

    uint64_t next() {
        std::lock_guard<std::mutex> lk(m_mtx);
        return m_inner.next();
    }

    uint64_t next(uint64_t min, uint64_t max) {
        std::lock_guard<std::mutex> lk(m_mtx);
        return m_inner.next(min, max);
    }
};
}

#endif
