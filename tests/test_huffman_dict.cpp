#include "catch.hpp"
#include "huffman/huffman_dict.h"
#include "huffman/huffman.h"
#include <vector>
#include <algorithm>
#include <string>
#include <functional>

using namespace std;

TEST_CASE("HuffmanDict stores and retrieves codes", "[huffman_dict]") {
    HuffmanDict dict;

    vector<uint8_t> code_a = {1, 2, 1, 0};
    vector<uint8_t> code_b = {2, 2, 0};
    vector<uint8_t> code_c = {1, 0};

    // Populate the dictionary manually
    dict.allocate_symbol('a', code_a);
    dict.allocate_symbol('b', code_b);
    dict.allocate_symbol('c', code_c);

    SECTION("All inserted symbols are present") {
        vector<symbol> symbols = dict.get_symbols();
        REQUIRE(symbols.size() == 3);
        
        // Sort to ensure deterministic check
        sort(symbols.begin(), symbols.end());
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

        auto check_code = [](const uint8_t* actual, const vector<uint8_t>& expected) {
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

TEST_CASE("generate_huffman_dict produces correct dictionary from string", "[huffman_dict]") {
    struct TestCase {
        string name;
        string input;
        function<vector<uint8_t>(symbol)> expected_code;
    };
    using get_symbol_code_fn = function<vector<uint8_t>(symbol)>;

    // note that when two nodes are at the same depth, the left/right assignment may vary
    // so the codes may differ then what is found on the internet, but the lengths should be the same
    auto [input, expected_code_func] = GENERATE(table<string, get_symbol_code_fn>({
        {"aab", [](symbol s) {
            if (s == 'a') return vector<uint8_t>{1};
            if (s == 'b') return vector<uint8_t>{0};
            return vector<uint8_t>{};
        }},
        {"aaabbc", [](symbol s) {
            if (s == 'a') return vector<uint8_t>{0};
            if (s == 'b') return vector<uint8_t>{1, 1};
            if (s == 'c') return vector<uint8_t>{1, 0};
            return vector<uint8_t>{};
        }},
        {"aaaabbbccd", [](symbol s) {
            if (s == 'a') return vector<uint8_t>{0};
            if (s == 'b') return vector<uint8_t>{1, 0};
            if (s == 'c') return vector<uint8_t>{1, 1, 1};
            if (s == 'd') return vector<uint8_t>{1, 1, 0};
            return vector<uint8_t>{};
        }},
        {"aaaabccddd", [](symbol s) {
            if (s == 'a') return vector<uint8_t>{0};
            if (s == 'b') return vector<uint8_t>{1, 1, 0};
            if (s == 'c') return vector<uint8_t>{1, 1, 1};
            if (s == 'd') return vector<uint8_t>{1, 0};
            return vector<uint8_t>{};
        }},
        {"aaaaaa", [](symbol s) { // single symbol
            if (s == 'a') return vector<uint8_t>{0};
            return vector<uint8_t>{};
        }},
        {"", [](symbol s) { // empty string means empty dict, so it doesn't matter what we return
            return vector<uint8_t>{};
        }},
        {" 0 11 222 3333 4444 ", [](symbol s) {
            if (s == ' ') return vector<uint8_t>{1, 1};
            if (s == '0') return vector<uint8_t>{1, 0, 1, 0};
            if (s == '1') return vector<uint8_t>{1, 0, 1, 1};
            if (s == '2') return vector<uint8_t>{1, 0, 0};
            if (s == '3') return vector<uint8_t>{0, 1};
            if (s == '4') return vector<uint8_t>{0, 0};

            return vector<uint8_t>{};
        }},
        {"mississippi", [](symbol s) {
            if (s == 'm') return vector<uint8_t>{1, 0, 0};
            if (s == 'i') return vector<uint8_t>{1, 1};
            if (s == 's') return vector<uint8_t>{0};
            if (s == 'p') return vector<uint8_t>{1, 0, 1};

            return vector<uint8_t>{};
        }},
    }));
    
    CAPTURE(input);

    HuffmanDict dict = generate_huffman_dict((const symbol*)input.c_str());
    
    for (symbol sym : dict.get_symbols()) {
        const uint8_t* code = dict.get_code(sym);
        vector<uint8_t> expected_code = expected_code_func(sym);

        for(int i = 0; i < expected_code.size(); i++) {
            REQUIRE(CODE_TO_BIT(code[i]) == expected_code[i]);
        }

        // REQUIRE(code[expected_code.size()] == 0); // null-terminator
    }
}
