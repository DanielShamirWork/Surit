#include "catch.hpp"
#include "freq/freq.h"
#include <unordered_map>

TEST_CASE("Frequencies are computed", "[frequencies]") {
    const symbol *str1 = "aabcbad";
    std::unordered_map<symbol, uint64_t> freqs = frequencies(str1);

    REQUIRE(freqs.size() == 4);

    SECTION("check frequency of a") {
        REQUIRE(freqs['a'] == 3);
    }
    SECTION("check frequency of b") {
        REQUIRE(freqs['b'] == 2);
    }
    SECTION("check frequency of c") {
        REQUIRE(freqs['c'] == 1);
    }
    SECTION("check frequency of d") {
        REQUIRE(freqs['d'] == 1);
    }
}