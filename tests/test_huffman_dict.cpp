#include "catch.hpp"
#include "huffman/huffman_dict.h"
#include <vector>
#include <algorithm>

TEST_CASE("HuffmanDict stores and retrieves codes", "[huffman_dict]") {
    HuffmanDict dict;

    std::vector<uint8_t> code_a = {1, 2, 1, 0};
    std::vector<uint8_t> code_b = {2, 2, 0};
    std::vector<uint8_t> code_c = {1, 0};

    // Populate the dictionary manually
    dict.allocate_symbol('a', code_a);
    dict.allocate_symbol('b', code_b);
    dict.allocate_symbol('c', code_c);

    SECTION("All inserted symbols are present") {
        std::vector<symbol> symbols = dict.get_symbols();
        REQUIRE(symbols.size() == 3);
        
        // Sort to ensure deterministic check
        std::sort(symbols.begin(), symbols.end());
        REQUIRE(symbols[0] == 'a');
        REQUIRE(symbols[1] == 'b');
        REQUIRE(symbols[2] == 'c');
    }

    SECTION("Codes match inserted values") {
        const uint8_t* ret_a = dict.get_code('a');
        const uint8_t* ret_b = dict.get_code('b');
        const uint8_t* ret_c = dict.get_code('c');

        REQUIRE(ret_a != nullptr);
        REQUIRE(ret_b != nullptr);
        REQUIRE(ret_c != nullptr);

        auto check_code = [](const uint8_t* actual, const std::vector<uint8_t>& expected) {
            size_t i = 0;
            for (; expected[i] != 0; ++i) {
                REQUIRE(actual[i] == expected[i]);
            }
            REQUIRE(actual[i] == 0);
        };

        check_code(ret_a, code_a);
        check_code(ret_b, code_b);
        check_code(ret_c, code_c);
    }
}
