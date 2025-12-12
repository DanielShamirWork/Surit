#include "catch.hpp"
#include "huffman/huffman.h"
#include <string>
#include <unordered_map>
#include <tuple>

using namespace std;

// Helper to validate the tree structure and collect leaf frequencies
void validate_tree_structure(HuffmanNode* node, unordered_map<symbol, uint64_t>& leaves) {
    if (!node) return;

    if (node->left == nullptr && node->right == nullptr) {
        // Leaf node
        leaves[node->sym] = node->frequency;
    } else {
        // Internal node
        uint64_t left_freq = node->left ? node->left->frequency : 0;
        uint64_t right_freq = node->right ? node->right->frequency : 0;
        
        REQUIRE(node->frequency == left_freq + right_freq);
        
        validate_tree_structure(node->left, leaves);
        validate_tree_structure(node->right, leaves);
    }
}

TEST_CASE("Huffman Tree is built correctly", "[huffman_tree]") {
    using FreqMap = unordered_map<symbol, uint64_t>;

    auto [input, expected_freqs] = GENERATE(table<string, FreqMap>({
        {"aabcbad", {{'a', 3}, {'b', 2}, {'c', 1}, {'d', 1}}},
        {"hello",   {{'h', 1}, {'e', 1}, {'l', 2}, {'o', 1}}},
        {"aaaaaa",  {{'a', 6}}},
        {"abcabc",  {{'a', 2}, {'b', 2}, {'c', 2}}},
        {"",        {}},
        {" 0000 111 22 3 ", {{' ', 5}, {'0', 4}, {'1', 3}, {'2', 2}, {'3', 1}}},
        {"\1\2\3\4\5", {{'\1', 1}, {'\2', 1}, {'\3', 1}, {'\4', 1}, {'\5', 1}}},
        {"abab\0", {{'a', 2}, {'b', 2}}}
    }));

    CAPTURE(input);

    HuffmanNode* root = build_tree((const symbol*)input.c_str());

    if (expected_freqs.empty()) {
        REQUIRE(root == nullptr);
    } else {
        REQUIRE(root != nullptr);
        REQUIRE(root->frequency == input.length());

        unordered_map<symbol, uint64_t> leaves_found;
        validate_tree_structure(root, leaves_found);

        REQUIRE(leaves_found == expected_freqs);
    }
}
