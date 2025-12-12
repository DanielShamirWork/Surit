#include "freq.h"

// popoulates freqs by the frequency of each symbol in syms, based on str
// OPTIMIZATION: go over all symbols in parallel/SIMD, also try loop unrolling
const unordered_map<symbol, uint64_t> frequencies(const symbol * const str) {
    unordered_map<symbol, uint64_t> freqs;
    for (const symbol * s = str; *s != '\0'; s++) {
        freqs[*s]++;
    }

    return freqs;
}