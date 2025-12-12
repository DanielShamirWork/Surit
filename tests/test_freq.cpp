#include "catch.hpp"
#include "freq/freq.h"
#include <unordered_map>
#include <string>
#include <tuple>

TEST_CASE("Frequencies are computed", "[frequencies]") {
    using FreqMap = std::unordered_map<symbol, uint64_t>;

    auto [input, expected] = GENERATE(table<std::string, FreqMap>({
        {"aabcbad", {{'a', 3}, {'b', 2}, {'c', 1}, {'d', 1}}},
        {"hello",   {{'h', 1}, {'e', 1}, {'l', 2}, {'o', 1}}},
        {"aaaaaa",  {{'a', 6}}},
        {"abcabc",  {{'a', 2}, {'b', 2}, {'c', 2}}},
        {"",        {}},
        {" 0000 111 22 3 ", {{' ', 5}, {'0', 4}, {'1', 3}, {'2', 2}, {'3', 1}}}, // spaces are counted
        {"\1\2\3\4\5", {{'\1', 1}, {'\2', 1}, {'\3', 1}, {'\4', 1}, {'\5', 1}}}, // non-printable chars are counted
        {"abab\0", {{'a', 2}, {'b', 2}}}, // null terminator should not be counted
    }));

    CAPTURE(input);
    std::unordered_map<symbol, uint64_t> freqs = frequencies((const symbol*)input.c_str());

    REQUIRE(freqs.size() == expected.size());

    for (const auto& [sym, count] : expected) {
        INFO("Checking symbol: " << sym);
        REQUIRE(freqs[sym] == count);
    }
}